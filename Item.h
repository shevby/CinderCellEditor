#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "constants.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

class Item
{
protected:
    sf::RenderWindow & window;
    std::vector<sf::Texture> & textures;
public:
    Item(sf::RenderWindow & w, std::vector<sf::Texture> & t) : window{w}, textures{t}{};
    virtual ~Item(){};
    virtual void render() = 0;
};



#endif // RENDERABLE_H