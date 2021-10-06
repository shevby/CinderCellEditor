#ifndef CINDERCELLEDITOR_H
#define CINDERCELLEDITOR_H

#include <vector>
#include <string>

#include <SFML/Window.hpp>

#include "Item.h"
#include "CinderMap.h"
#include "Controls.h"

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 720;

const std::vector<std::string> TEXTURE_PATHS = {
    "resources/textures/biomes/water.png",
    "resources/textures/biomes/field.png",
    "resources/textures/biomes/forest.png",
    "resources/textures/biomes/rock.png",
    "resources/textures/biomes/highrock.png",
    "resources/textures/biomes/glacier.png",
    "resources/textures/biomes/swamp.png",
    "resources/textures/biomes/desert.png",
    "resources/textures/biomes/savanna.png"
};

const float CAMERA_MOVE_SPEED = 1000;

class CinderCellEditor
{
    sf::RenderWindow _window{sf::VideoMode(WIDTH, HEIGHT), "Cinder Cell Editor"};
    sf::View _camera{sf::FloatRect{0.f, 0.f, WIDTH, HEIGHT}};

    Controls _input;
    std::vector<Item*> _items;
    std::vector<sf::Texture> _textures;

    float _zoom = 1;

public:

    CinderCellEditor();
    ~CinderCellEditor();

    float deltaTime;

    bool open(std::string filepath);
    bool view(std::string filepath);

    int exec();

    //controls
     void moveUp();
     void moveDown();
     void moveLeft();
     void moveRight();
     void resetPosition();
     void zoomIn();
     void zoomOut();
};

#endif // CINDERCELLEDITOR_H
