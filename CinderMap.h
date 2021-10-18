#ifndef CINDERMAP_H
#define CINDERMAP_H

#include <iostream>
#include <fstream>

#include "Item.h"
#include "constants.h"

/*!
 * \brief The CinderMap class
 * represents the opened map
 */
class CinderMap: public Item {
    std::string filePath;
    uint32_t height = 0;
    uint32_t width = 0;
    sf::Texture texture;
    sf::RectangleShape map;
public:
    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t);
    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t, std::string path);
    virtual ~CinderMap();
    /*!
     * \brief toPng
     * transforms raw map to PNG and saves it with name [filePath].png
     * \return
     */
    int toPng();
    /*!
     * \brief render
     * renders map in the main window
     */
    virtual void render();

};

#endif // CINDERMAP_H
