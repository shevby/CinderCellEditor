#include "CinderCellEditor.h"



CinderCellEditor::CinderCellEditor() : _input{_window}
{
    for(auto path : TEXTURE_PATHS) {
        _textures.push_back(sf::Texture{});
        _textures[_textures.size() - 1].loadFromFile(path);
    }

}

CinderCellEditor::~CinderCellEditor()
{
    for(auto p : _items) {
        delete p;
    }
}

bool CinderCellEditor::open(std::string filepath)
{

}

bool CinderCellEditor::view(std::string filepath)
{
    _items.push_back(new CinderMap(_window, _textures, filepath));

    _input.listenKeys(sf::Keyboard::W, std::bind(&CinderCellEditor::moveUp, this));
    _input.listenKeys(sf::Keyboard::S, std::bind(&CinderCellEditor::moveDown, this));
    _input.listenKeys(sf::Keyboard::A, std::bind(&CinderCellEditor::moveLeft, this));
    _input.listenKeys(sf::Keyboard::D, std::bind(&CinderCellEditor::moveRight, this));
    _input.listenKeys(sf::Keyboard::R, std::bind(&CinderCellEditor::resetPosition, this));
    _input.listenKeys(sf::Keyboard::E, std::bind(&CinderCellEditor::zoomIn, this));
    _input.listenKeys(sf::Keyboard::Q, std::bind(&CinderCellEditor::zoomOut, this));

}


int CinderCellEditor::exec()
{
    sf::Clock clock;

    while (_window.isOpen()) {
        deltaTime = clock.getElapsedTime().asSeconds();

        clock.restart();
        _input.exec();

        _window.clear();

        for(auto r : _items) {
            r->render();
        }

        _window.setView(_camera);
        _window.display();


//        std::cout << clock.getElapsedTime().asSeconds() << std::endl;

    }



    return 0;
}


void CinderCellEditor::moveUp()
{
    _camera.move(sf::Vector2f(0, -1) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveDown()
{
    _camera.move(sf::Vector2f(0, 1) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveLeft()
{
    _camera.move(sf::Vector2f(-1, 0) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveRight()
{
    _camera.move(sf::Vector2f(1, 0) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::resetPosition()
{
    _camera.setCenter(0, 0);
}

void CinderCellEditor::zoomIn()
{
    if(_zoom < 0.1) {
        return;
    }

    if(_zoom < 0.5) {
        _zoom -= 0.0001;
    }
    else {
        _zoom -= 0.01;
    }

    _camera.setSize(sf::Vector2f(WIDTH, HEIGHT) * _zoom);
}

void CinderCellEditor::zoomOut()
{

    if(_zoom > TILE_HEIGHT) {
        return;
    }

    _zoom += 0.01;
    _camera.setSize(sf::Vector2f(WIDTH, HEIGHT) * _zoom);
}
