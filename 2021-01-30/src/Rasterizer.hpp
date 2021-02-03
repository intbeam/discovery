
#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "pixelwriter.hpp"
#include "spritemanager.hpp"

class Rasterizer
{
    private:
        PixelWriter &writer;
        surface_dimension dimension;
    public:
        Rasterizer(PixelWriter &pixel_writer);
        void draw_rectangle(int x, int y, int width, int height, int color);
        void draw_sprite(int x, int y, Sprite &sprite);

};

#endif
