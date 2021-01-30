#include "pixelwriter.hpp"

void VgaPixelWriter::write_pixeldata(int x_origin, int y_origin, const pixel_packet *pixel_operations, int packet_count, int loop_count)
 {
    int opsCounter;
    int vgaIndex = y_origin * 320 + x_origin;
    int bytesWritten;
    int lc;
    pixel_packet *opsptr;


    for(lc = 0; lc < loop_count; lc++)
    {
        opsptr = (pixel_packet*)pixel_operations;
        for(opsCounter = 0; opsCounter < packet_count; opsCounter++)
        {
            bytesWritten = opsptr->count;

            switch(opsptr->type)
            {
                case PACKET_SINGLE_COLOR:

                //printf("type: %d value:%d count:%d", ops->type, ops->value, ops->count);

                __asm {

                    // initializes ES:DI to vga
                    mov ax, VGA_SEGMENT
                    mov es, ax
                    mov ax, vgaIndex
                    mov di, ax

                    // read from packet pointer
                    mov ax, opsptr
                    mov si, ax

                    // CX = number of pixels to write
                    mov cx, [ds:si]
                    // Read color from opsptr pointer structure
                    mov ax, [ds:si + 2]
                    
                    // set pixel, repeat until CX = 0
                    rep stosb

                }                

                break;
            case PACKET_SOURCE_COPY:
                
                //printf("type: %d value:%d count:%d", ops->type, ops->value, ops->count);

                __asm {

                    // initialize ES:DI to vga
                    mov ax, VGA_SEGMENT
                    mov es, ax
                    mov ax, vgaIndex
                    mov di, ax

                    // read from packet pointer
                    mov ax, opsptr
                    mov si, ax
                    // CX = number of pixels to write
                    mov cx, [ds:si]
                    mov ax, [ds:si + 4]
                    mov si, ax

                    // move pixel from DS:SI to ES:DI repeat until CX = 0
                    rep movsb
                }

                break;
            case PACKET_SKIP:
                
                break;
            }

            vgaIndex += bytesWritten;

            opsptr++;
        }
    }
     
 }

 void VgaPixelWriter::get_surface_dimensions(surface_dimension &dimension)
 {
     dimension.width = 320;
     dimension.height = 200;
 }