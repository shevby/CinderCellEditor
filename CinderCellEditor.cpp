#include "CinderCellEditor.h"



CinderCellEditor::CinderCellEditor() : _input{_window}
{
    for(auto path : TEXTURE_PATHS) {
        _textures.push_back(sf::Texture{});
        _textures[_textures.size() - 1].loadFromFile(path);
        _textures[_textures.size() - 1].setRepeated(true);
    }

}

CinderCellEditor::~CinderCellEditor()
{

}

void CinderCellEditor::edit(std::string filepath)
{
    _mode = Modes::EDIT;

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));
    _cursor = std::make_shared<Cursor>(_window, _textures);
    _cursor->onDrawAreaSelected(std::bind(&CinderCellEditor::addOverlay, this));

    _input.listenKeys(sf::Keyboard::W, std::bind(&CinderCellEditor::moveUp, this));
    _input.listenKeys(sf::Keyboard::S, std::bind(&CinderCellEditor::moveDown, this));
    _input.listenKeys(sf::Keyboard::A, std::bind(&CinderCellEditor::moveLeft, this));
    _input.listenKeys(sf::Keyboard::D, std::bind(&CinderCellEditor::moveRight, this));
    _input.listenKeys(sf::Keyboard::R, std::bind(&CinderCellEditor::resetPosition, this));
    _input.listenKeys(sf::Keyboard::E, std::bind(&CinderCellEditor::zoomIn, this));
    _input.listenKeys(sf::Keyboard::Q, std::bind(&CinderCellEditor::zoomOut, this));
    _input.listenMouse(std::bind(&CinderCellEditor::handleMouse, this, std::placeholders::_1));

}

void CinderCellEditor::view(std::string filepath)
{
    _mode = Modes::VIEW;

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));

    _input.listenKeys(sf::Keyboard::W, std::bind(&CinderCellEditor::moveUp, this));
    _input.listenKeys(sf::Keyboard::S, std::bind(&CinderCellEditor::moveDown, this));
    _input.listenKeys(sf::Keyboard::A, std::bind(&CinderCellEditor::moveLeft, this));
    _input.listenKeys(sf::Keyboard::D, std::bind(&CinderCellEditor::moveRight, this));
    _input.listenKeys(sf::Keyboard::R, std::bind(&CinderCellEditor::resetPosition, this));
    _input.listenKeys(sf::Keyboard::E, std::bind(&CinderCellEditor::zoomIn, this));
    _input.listenKeys(sf::Keyboard::Q, std::bind(&CinderCellEditor::zoomOut, this));

}

void CinderCellEditor::toPng(std::string filepath)
{
    _mode = Modes::TO_PNG;

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));

}


int CinderCellEditor::exec()
{
    sf::Clock clock;

    if(_mode == Modes::TO_PNG) {
        return dynamic_cast<CinderMap*>(_items[0].get())->toPng();
    }

    auto avarageFrameRenderTime = 0.f;

    while (_window.isOpen()) {
        deltaTime = clock.getElapsedTime().asSeconds();

        clock.restart();
        _input.exec();

        _window.clear();

        for(auto r : _items) {
            r->render();
        }

        if(_mode == Modes::EDIT) {
            _cursor->render();
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

void CinderCellEditor::handleMouse(MouseEvent event)
{
    if(event.wheelDelta > 0) {
        this->zoomIn();
    }
    else if(event.wheelDelta < 0) {
        this->zoomOut();
    }
    _cursor->handleMouse(event);
}

void CinderCellEditor::addOverlay()
{
    _items.push_back(std::make_shared<Overlay>(*(_cursor.get())));
}






