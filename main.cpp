#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <fstream>

#include "constants.h"

using namespace Cinder;

//enum class Biomes {
//    WATER = 0,
//    FIELD,
//    FOREST,
//    ROCK,
//    HIGH_ROCK,
//    GLACIER,
//    SWAMP,
//    DESERT,
//    SAVANNA,
//};

sf::Color colors[] = {
    sf::Color::Blue,
    sf::Color{209, 255, 23},
    sf::Color::Green,
    sf::Color{163, 163, 163},
    sf::Color{245, 245, 245},
    sf::Color{214, 252, 255},
    sf::Color{102, 75, 75},
    sf::Color::Yellow,
    sf::Color{255, 152, 92}

};

class MapDrawer {
private:
    uint32_t currentX = 0;
    uint32_t currentY = 0;


public:
    uint32_t height = 512;
    uint32_t width = 512;

    std::vector<Biom> map;

    sf::Texture texture;

    uint32_t tmp = 0;

    MapDrawer(const std::vector<uint8_t> & buffer) {
        texture.create(512, 512);

        for(int b : buffer) {
            map.push_back(Biom{static_cast<Biomes>(b)});
        }
    }

    sf::RectangleShape get() {
        if(currentX + 1 > width) {
            currentY++;
            currentX = 0;
        }

        sf::RectangleShape rect;

        rect.setFillColor(colors[(int)map[currentY * height + currentX].biomType]);
        rect.setSize(sf::Vector2f(1, 1));
        rect.setPosition(currentX * 1, currentY * 1);

        currentX++;
        return rect;
    }


    const sf::Texture & getTexture() {

        sf::Image image = texture.copyToImage();

        for(int i = 0; i < height; i++) {
            for(int j = 0; j < width; j++) {
                image.setPixel(j, i, colors[(int)map[i * height + j].biomType]);
            }
        }

        texture.loadFromImage(image);


        return texture;

    }

    bool done() {
        if(currentY + 1 == height && currentX + 1 > width) {
            currentX = 0;
            currentY = 0;
            return true;
        }

        return false;
    }
};

const float WIDTH = 1280;
const float HEIGHT = 720;

int main()
{


    std::ifstream input{"map.bin", std::ios::binary};
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(input), {});
    MapDrawer md{buffer};

//    return 0;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cinder Cell Editor");

    sf::View view(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));

    float zoom = 1;

    sf::Clock clock;

    sf::RectangleShape rect;

    auto texture = md.getTexture();
    rect.setTexture(&texture);
    rect.setSize(sf::Vector2f(512, 512));
    rect.setPosition(0, 512);

    rect.setScale(1, -1);

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        auto deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                view.move(sf::Vector2f{0, -10});
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                view.move(sf::Vector2f{0, 10});
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                view.move(sf::Vector2f{-10, 0});
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                view.move(sf::Vector2f{10, 0});
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                zoom = zoom > 0.01 ? zoom - 0.01 : zoom;
                view.setSize(WIDTH * zoom, HEIGHT * zoom);
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                zoom = zoom < 1 ? zoom + 0.01 : zoom;
                view.setSize(WIDTH * zoom, HEIGHT * zoom);
            }


        }

        window.clear();

        texture = md.getTexture();
        texture.update(window);
        window.setView(view);

        window.draw(rect);


        window.display();

    }
    return 0;
}
