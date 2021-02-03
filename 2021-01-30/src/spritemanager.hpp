#ifndef SPRITEMANAGER_HPP
#define SPRITEMANAGER_HPP

#include "pixelwriter.hpp"
#include <errno.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

#define TGA_SIGNATURE "TRUEVISION-XFILE.\0"

#pragma pack(1)
typedef struct tga_header
{
    char image_id;
    char color_map_type;
    char image_type;

    unsigned int color_map_first_index;
    unsigned int color_map_length;
    
    char color_map_bpp;

    unsigned short origin_x;
    unsigned short origin_y;

    unsigned short image_width;
    unsigned short image_height;

    char image_bpp;

    char image_descriptor;
} tga_header;

typedef struct tga_footer
{
    unsigned long extension_offset;
    unsigned long developer_offset;
    char signature[18];
} tga_footer;

#pragma pack(0)

class Sprite
{

public:
    int width;
    int height;
    int packet_count;
    pixel_packet *pixelpackets;
};







class SpriteManager
{
    char *pixeldata;
    char *pixeldata_current;
    pixel_packet *packet_store;
    pixel_packet *packet_store_current;

    pixel_packet *alloc_pixel_packet(int count, int value, void* data, int type, int &packet_counter);

public:
    SpriteManager();
    ~SpriteManager();
    void load_sprite(char *filename, int sprite_width, int sprite_height, Sprite &sprite);

    void draw_sprite(Sprite &sprite, PixelWriter pixel_writer);

};

#endif
