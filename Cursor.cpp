#include "Cursor.h"

sf::Texture toCursorTexture(sf::Texture & t) {
    sf::Image img = t.copyToImage();
    auto xLen = img.getSize().x;
    auto yLen = img.getSize().y;

    for(int y = 0; y < yLen; y++) {
        for(int x = 0; x < xLen; x++) {

            if(x - 1 < 0 || x + 2 > xLen || y - 1 < 0 || y + 2 > yLen) {
                img.setPixel(x, y, sf::Color::Red);
            }

        }
    }

    sf::Texture texture;

    texture.loadFromImage(img);

    texture.setRepeated(true);

    return texture;
}

const sf::Vector2f &Cursor::getPos() const
{
    return pos;
}

const sf::Vector2f &Cursor::getSize() const
{
    return size;
}

uint8_t Cursor::getCurrentTexture() const
{
    return currentTexture;
}

void Cursor::onDrawAreaSelected(std::function<void ()> callback)
{
    onDrawAreaSelectedCallback = callback;
}

Cursor::Cursor(sf::RenderWindow &w, std::vector<sf::Texture> &t) : Item{w, t}
{
    for(auto texture : textures) {
        cursorTextures.push_back(toCursorTexture(texture));
    }


}


void Cursor::handleMouse(MouseEvent event)
{
    auto position = window.mapPixelToCoords(event.pos);
    position.x = static_cast<int>(position.x - static_cast<int>(position.x) % 16);
    position.y = static_cast<int>(position.y - static_cast<int>(position.y) % 16);

    if(event.left && startPos.x >= 0 && startPos.y >= 0) {
        std::cout << "Create" << std::endl;
        if(onDrawAreaSelectedCallback != nullptr) {
            onDrawAreaSelectedCallback();
        }
        reset();
        return;
    }

    if(startPos.x >= 0 && startPos.y >=0) {
        std::cout << "Start draw" << std::endl;
        size = (position - startPos);
        size += sf::Vector2f{ static_cast<float>(size.x >= 0 ? TILE_WIDTH: 0), static_cast<float>(size.y >= 0 ? TILE_HEIGHT : 0)};
    }
    else {
        pos = position;
    }

    if(event.left) {
        std::cout << "Set start pos" << std::endl;
        startPos = position;
    } else if (event.right) {
        reset();
    }


}

void Cursor::reset()
{
    startPos = {-1, -1};
    size = {TILE_WIDTH, TILE_HEIGHT};
}

void Cursor::render()
{
    rectangle.setPosition(pos);
    rectangle.setSize(size);
    rectangle.setTexture(&cursorTextures[0]);
    rectangle.setTextureRect({0, 0, static_cast<int>(size.x), static_cast<int>(size.y)});


    window.draw(rectangle);
}

