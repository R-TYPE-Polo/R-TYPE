/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** systems
*/
/*
- ShootingSystem -<Basic>-
- DeathSystem -<Basic>-
- DamagedSystem -<Basic>-
- MovementSystem -<Basic>-
- IASystem -<Basic>-
- RendererSystem -<Basic>-
*/

#pragma once
#include "entities.hpp"

#include <array>

void shootingSystem(Entity entity, Registry& registry);
void deathSystem(Entity entity, Registry& registry);
void damagedSystem(Entity entity, Entity otherEntity, Registry& registry);
void movementSystem(Entity entity, Registry& registry);
void collisionSystem(Entity entity, std::vector<Entity> entities, Registry& registry);
void iaSystem(Entity entity, Registry& registry);
void renderSystem(Entity entity, Registry& registry, sf::RenderWindow& window);

enum COMMAND
{
    NEW,
    LOGIN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NEW_PLAYER,
    NEW_ENEMY,
    DELETE,
    PLAYER_PROJECTILE,
    PLAY_BOOM_ENEMIES,
    REFRESH,
    NEW_POS,
    UPDATE,
    SHOOT,
    UNKNOWN,
    EMPTY,
    ALIVE,
};

COMMAND getCommand(const std::string& commandStr);
EntityType getType(const std::string& typeStr);

struct TransferData
{
    enum COMMAND command;
    std::array<int, 5> args;
};
