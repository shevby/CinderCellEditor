#include "Overlay.h"

Overlay::Overlay(sf::RenderWindow &w, std::vector<sf::Texture> &t) : Item{w, t}
{

}

Overlay::Overlay(Cursor &c) : Item{c}
{
    pos = c.getPos();
    size = c.getSize();
    currentTexture = c.getCurrentTexture();


    rectangle.setPosition(pos);
    rectangle.setSize(size);
    rectangle.setTexture(&textures[currentTexture]);
    rectangle.setTextureRect({0, 0, static_cast<int>(size.x), static_cast<int>(size.y)});
}

void Overlay::render()
{
    window.draw(rectangle);
}
