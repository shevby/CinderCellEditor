#include "CinderMap.h"



CinderMap::CinderMap(sf::RenderWindow &w, std::vector<sf::Texture> &t) : Item{w, t}
{

}

CinderMap::CinderMap(sf::RenderWindow &w, std::vector<sf::Texture> &t, std::string filePath) : CinderMap{w, t}
{
    std::ifstream input{filePath, std::ios::binary};
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});

    Cinder::Map * mapStruct = (Cinder::Map*)&buffer[0];
    width = mapStruct->width;
    height = mapStruct->height;

    uint8_t * mapData = (uint8_t*)&mapStruct->map;

    sf::Image img{};
    img.create(width * TILE_WIDTH, height * TILE_HEIGHT);

    for(int tileIndex = 0; tileIndex < height * width; tileIndex++) {
        uint32_t yCoord = tileIndex / width;
        uint32_t xCoord = tileIndex - (yCoord * width);

        sf::Image tileImage = textures[mapData[tileIndex]].copyToImage();
        int tileY = 0;
        int tileX = 0;
        for(int y = yCoord * TILE_HEIGHT; y < yCoord * TILE_HEIGHT + TILE_HEIGHT; y++) {
            for(int x = xCoord * TILE_WIDTH; x < xCoord * TILE_WIDTH + TILE_WIDTH; x++) {
                img.setPixel(x, y, tileImage.getPixel(tileX, tileY));
                tileX++;
            }
            tileY++;
            tileX = 0;
        }
    }

    texture.loadFromImage(img);

}

CinderMap::~CinderMap()
{

}

void CinderMap::render()
{
    sf::RectangleShape map{sf::Vector2f(width * TILE_WIDTH, height * TILE_HEIGHT)};
    map.setTexture(&texture);

    window.draw(map);
}


