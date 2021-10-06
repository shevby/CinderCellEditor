#include "Controls.h"


Controls::Controls(sf::Window &w) : window{w}
{

}

void Controls::listenKeys(sf::Keyboard::Key key, std::function<void()> callback)
{
    this->listeners.push_back(Listener{key, callback});
}

void Controls::exec()
{
    sf::Event event;

    if (window.pollEvent(event)) {

        if(event.type == sf::Event::Closed) {
            window.close();
        }


    }

    for(auto listener : listeners) {
        if(sf::Keyboard::isKeyPressed(listener.key)) {
            listener.callback();
        }
    }
}

