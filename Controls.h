#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <functional>
#include <vector>

struct Listener{
    sf::Keyboard::Key key;
    std::function<void()> callback;
};

class Controls
{

sf::Window & window;
std::vector<Listener> listeners;

public:

Controls(sf::Window & w);

void listenKeys(sf::Keyboard::Key key, std::function<void()> callback);
void exec();

};

#endif // CONTROLS_H
