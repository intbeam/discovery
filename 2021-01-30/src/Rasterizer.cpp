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

#include "rasterizer.hpp"

Rasterizer::Rasterizer(PixelWriter &pixel_writer) : writer(pixel_writer)
{
    pixel_writer.get_surface_dimensions(dimension);
}

void Rasterizer::draw_rectangle(int x, int y, int width, int height, int color)
{
    pixel_packet packets[2] = { 
        { width, color, 0, PACKET_SINGLE_COLOR },
        { this->dimension.width - width, 0, 0, PACKET_SKIP }
    };
    
    this->writer.write_pixeldata(x, y, packets, 2, height);
}

void Rasterizer::draw_sprite(int x, int y, Sprite &sprite)
{
    // set skip line amount to the dimension of the target surface minus
    // the width of the sprite to go to next origin line on SKIP_NEXT_LINE
    this->writer.set_next_line_skip_count(this->dimension.width - sprite.width);
    // go through the packets and draw pixels accordingly
    this->writer.write_pixeldata(x, y, sprite.pixelpackets, sprite.packet_count, 1);
}