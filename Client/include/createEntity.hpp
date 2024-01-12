/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** createEntity
*/

#pragma once
#include "entities.hpp"

void updatePosition(Registry& registry, int id, int xPos, int yPos);
void updateHealth(Registry& registry, int id, int health);
void createPlayer(Registry& registry, int id, int xPos, int yPos, int healthPoint);
void createEnemy(Registry& registry, int id, int xPos, int yPos);
void createBoss(Registry& registry, int id, int xPos, int yPos);
void createPlayerProjectile(Registry& registry, int id, int xPos, int yPos);
void createHud(Registry& registry, int id, int dataScore);
void createScore(Registry& registry, int dataScore);