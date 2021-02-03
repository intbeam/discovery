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


// Application entrypoint
int main(int argc, char** argv)
{
    VgaPixelWriter pixelWriter = VgaPixelWriter();    
    Rasterizer rasterizer = Rasterizer(pixelWriter);
    SpriteManager spriteManager = SpriteManager();
    Sprite testsprite;
    int x = 0;    

    __asm {

        mov ax, 13h
        int 10h

    }  

    // Remember to move zillion.tga to the bin directory
    spriteManager.load_sprite("zillion.tga", 16, 16, testsprite);


    for(x = 0; x < 304; x++)
    {
        //printf("%d", testsprite.packet_count);
        rasterizer.draw_rectangle(x, 70, 16, 16, 0);
        rasterizer.draw_sprite(x, 70, testsprite);
    }

    return 0;
}
