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