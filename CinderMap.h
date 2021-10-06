#ifndef CINDERMAP_H
#define CINDERMAP_H

#include <iostream>
#include <fstream>

#include "Item.h"
#include "constants.h"

class CinderMap: public Item {
    uint32_t height = 0;
    uint32_t width = 0;

    sf::Texture texture;
public:
    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t);
    CinderMap(sf::RenderWindow & w, std::vector<sf::Texture> & t, std::string filePath);
    virtual ~CinderMap();
    virtual void render();

};

#endif // CINDERMAP_H
