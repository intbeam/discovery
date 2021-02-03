#include "spritemanager.hpp"

SpriteManager::SpriteManager()
{
    // pixel packets
    this->packet_store = (pixel_packet*)malloc(sizeof(pixel_packet) * 1000);
    this->packet_store_current = this->packet_store;
    
    // raw pixel data for sprites
    this->pixeldata = (char *)malloc(sizeof(1024));
    this->pixeldata_current = this->pixeldata;
}

SpriteManager::~SpriteManager()
{
    // free up allocated memory
    free(this->packet_store);
    free(this->pixeldata);
}

pixel_packet *SpriteManager::alloc_pixel_packet(int count, int value, void *data, int type, int &packet_counter)
{
    pixel_packet *ret = this->packet_store_current++;
    ret->count = count; // number of pixels
    ret->value = value; // color of pixel if it's a single color packet
    ret->type = type; // type of packet
    
    // data should be a null pointer of it's a solid color repeat or a skip packet
    if(type == PACKET_SINGLE_COLOR || type == PACKET_SKIP || type == PACKET_NEXT_LINE)
    {
        ret->data = (void *)0;
    }
    else if(type == PACKET_SOURCE_COPY)
    {
        // set the pointer of the data structure to the current allocation pointer
        ret->data = pixeldata_current;
        // copy from source to pixel data
        memcpy(ret->data, data, count);
        // increase the pixeldata pointer by number of pixels
        this->pixeldata_current += count; 
    }

    // increment the number of packets allocated
    packet_counter++;

    return ret;
    
}

void SpriteManager::load_sprite(char *filename, int sprite_width, int sprite_height, Sprite &sprite)
{
    tga_header header;
    tga_footer footer;
    int totalpixels = 0;
    int maxpixels = 0;
    int nlength = 0;
    int index = 0;
    void *pixel_data;
    int num_pixels = 0;        
    char pixelbuffer[128];
    char rle_packet_header = 0;
    char pixel = 0;
    char palette_color[3];
    FILE *fp;      

    fp = fopen(filename, "rb");    

    if(fp == 0)
    {
        printf("Unable to open file %s", filename);
        return;
    }

    // seek to the end of the file to read tga signature
    fseek(fp, -((long)sizeof(tga_footer)), SEEK_END);

    // read footer
    fread(&footer, sizeof(tga_footer), 1, fp);

    
    // check if signature matches teh predefined
    if(strncmp(footer.signature, TGA_SIGNATURE, 18) != 0)
    {
        printf("Not a tga file : %s", footer.signature);
        fclose(fp);
        return;
    }

    // seek to the beginning of the file
    fseek(fp, 0L, SEEK_SET);

    // read header
    fread(&header, sizeof(tga_header), 1, fp);    

    // hack : set palette
    for(index = 0; index < header.color_map_length; index++)
    {
        fread(&palette_color, sizeof(char), 3, fp);

        outp(0x3c8, index);
        outp(0x3c9, palette_color[2] / 4);
        outp(0x3c9, palette_color[1] / 4);
        outp(0x3c9, palette_color[0] / 4);
    }


    //RLE

    // 8 : 1 bit is whether RLE
    //     7 bits is the number of pixels


    sprite.pixelpackets = this->packet_store_current;
    sprite.packet_count = 0;
    sprite.width = sprite_width;
    sprite.height = sprite_height;

    maxpixels = header.image_width *  header.image_height;

    while(totalpixels < maxpixels)
    {
        fread(&rle_packet_header, sizeof(char), 1, fp);

        if(0x80 & rle_packet_header)
        {
            num_pixels = (0x80 ^ rle_packet_header);
        }
        else
        {
            num_pixels = rle_packet_header;
        }
        
        num_pixels++;



        if(rle_packet_header & 0x80) // this is a run-length encoded packet
        {
            fread(&pixel, sizeof(char), 1, fp);

            this->alloc_pixel_packet(num_pixels, (int)pixel, 0,  pixel == 0 ? PACKET_SKIP : PACKET_SINGLE_COLOR, sprite.packet_count);
        }
        else
        {            
            fread(pixelbuffer, sizeof(char), num_pixels, fp);

            this->alloc_pixel_packet(num_pixels, 0, pixelbuffer, PACKET_SOURCE_COPY, sprite.packet_count);            
        }

        if(nlength >= sprite_width)
        {            
            nlength = 0;
            this->alloc_pixel_packet(0, 0, 0, PACKET_NEXT_LINE, sprite.packet_count);            
        }
        
        nlength += num_pixels;
        


        
        totalpixels += num_pixels;
    }
    

    fclose(fp);

}

