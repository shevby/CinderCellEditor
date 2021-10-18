#pragma once

#include <functional>

#include "Item.h"

class Cursor : public Item
{
    uint8_t currentTexture{0};
    sf::Vector2f startPos{-1, -1};
    sf::Vector2f pos;
    sf::Vector2f size{TILE_WIDTH, TILE_HEIGHT};
    sf::RectangleShape rectangle;
    std::vector<sf::Texture> cursorTextures;
    std::function<void()> onDrawAreaSelectedCallback{nullptr};

public:
    Cursor(sf::RenderWindow &w, std::vector<sf::Texture> &t);
    /*!
     * \brief render
     * Renders the cursor
     */
    virtual void render();
    /*!
     * \brief handleMouse
     * Handles mouse events
     * \param event
     */
    void handleMouse(MouseEvent event);
    /*!
     * \brief reset
     * Resets the state of the cursor
     */
    void reset();

    //Getters
    const sf::Vector2f &getPos() const;
    const sf::Vector2f &getSize() const;
    uint8_t getCurrentTexture() const;

    /*!
     * \brief onDrawAreaSelected
     * Subscribe to DrawAreaSelected event.
     * \param callback
     * Will be called when the user selects the area do draw with some tile
     */
    void onDrawAreaSelected(std::function<void()> callback);
};
