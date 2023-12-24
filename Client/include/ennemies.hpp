/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** ennemies
*/

#pragma once

#include "commandsToServer.hpp"
#include "sprite/sprite.hpp"

#include <iostream>
#include <sstream>

class Ennemies : public sf::Drawable, public sf::Transformable
{
public:
    Ennemies();
    ~Ennemies() override = default;

    void setPath();
    float getPosEnnemyY();
    float getPosEnnemyX();
    void destroyEnnemy(float playerPosX, float ennemyPosX);
    void HandleMovement(
        CommandsToServer& commandsToServer,
        float movementSpeed,
        float deltaX,
        float deltaY,
        float windowLimit,
        float spriteLimit);
    void SendPositionUpdate(CommandsToServer& commandsToServer, float x, float y, float speed);
    void moveEnnemy(float movementSpeed, float winX, float winY, CommandsToServer& commandsToServer);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_ennemyTexture;
    sf::Sprite m_ennemySprite;

    float m_moveSpeed;
};