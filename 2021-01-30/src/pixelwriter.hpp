#ifndef PIXELWRITER_HPP
#define PIXELWRITER_HPP

#include <stdio.h>

#define PACKET_SINGLE_COLOR     0
#define PACKET_SOURCE_COPY      1
#define PACKET_SKIP             2

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
    virtual void write_pixeldata(int x_origin, int y_origin, const pixel_packet *ops, int packet_count, int loop_count);
    virtual void get_surface_dimensions(surface_dimension& dimension);
};

class VgaPixelWriter : public PixelWriter
{
public:
    void write_pixeldata(int x_origin, int y_origin, const pixel_packet *ops, int packet_count, int loop_count);
    void get_surface_dimensions(surface_dimension& dimension);
};

#endif