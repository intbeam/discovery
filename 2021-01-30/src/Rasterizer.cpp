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