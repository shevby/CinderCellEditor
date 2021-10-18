#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "constants.h"
#include "Controls.h"

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

/*!
 * \brief The Item class
 * pure virtual, base for objects which will be rendered in the main loops
 */
class Item
{
protected:
    /*!
     * \brief window
     * Reference to the main application window
     */
    sf::RenderWindow & window;
    /*!
     * \brief textures
     * Reference to the textures of tiles
     */
    std::vector<sf::Texture> & textures;
public:
    Item(sf::RenderWindow & w, std::vector<sf::Texture> & t) : window{w}, textures{t}{};
    virtual ~Item(){};
    virtual void render() = 0;
};



#endif // RENDERABLE_H
