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

#ifndef PIXELWRITER_HPP
#define PIXELWRITER_HPP

#include <stdio.h>

#define PACKET_SINGLE_COLOR     0
#define PACKET_SOURCE_COPY      1
#define PACKET_SKIP             2
#define PACKET_NEXT_LINE        3

#define VGA_SEGMENT 0A000h

typedef struct pixel_packet
{
    int count;
    int value;
    void *data;
    int type;
} pixel_packet;

typedef struct surface_dimension
{
    int width;
    int height;
} surface_dimension;

class PixelWriter
{
public:
    virtual void set_next_line_skip_count(int count);
    virtual void write_pixeldata(int x_origin, int y_origin, const pixel_packet *ops, int packet_count, int loop_count);
    virtual void get_surface_dimensions(surface_dimension& dimension);
};

class VgaPixelWriter : public PixelWriter
{
private:
    int next_line_pixel_skip;
public:
    void set_next_line_skip_count(int count);
    void write_pixeldata(int x_origin, int y_origin, const pixel_packet *ops, int packet_count, int loop_count);
    void get_surface_dimensions(surface_dimension& dimension);
};

#endif
