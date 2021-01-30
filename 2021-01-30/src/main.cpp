/* Copyright 2021 Intbeam

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "main.hpp"
#include "rasterizer.hpp"

// Application entrypoint
int main(int argc, char** argv)
{
    VgaPixelWriter pixelWriter = VgaPixelWriter();    
    Rasterizer rasterizer = Rasterizer(pixelWriter);
    int i;
    
    char testbitmap[] = { 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15, 1, 15 };

    pixel_packet pixelpackets[2] = {
        {
            10,
            1,
            0,
            PACKET_SINGLE_COLOR
        },
        {
            20,
            0,
            testbitmap,
            PACKET_SOURCE_COPY
        }
    };

    __asm {

        mov ax, 13h
        int 10h

    }

    //pixelWriter.write_pixeldata(0, 60, pixelpackets, 2, 1);

    for(i = 0; i < 255; i++)
    {
        rasterizer.draw_rectangle(50, 50, 100, 100, i);
    }

    


    return 0;
}
