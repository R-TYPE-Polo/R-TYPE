/*
** EPITECH PROJECT, 2024
** R-TYPE
** File description:
** inLoopGame
*/

#include "menu/inLoopGame.hpp"

void InLoopGame::refreshRegistry(Registry& registry, CommandsToServer& commandsToServer, IpAdress& ipAdress)
{
    if (m_clock.getElapsedTime().asMilliseconds() < 1000)
        return;
    m_clock.restart();
    for (auto& entity : registry.getListEntities()) {
        commandsToServer.sendToServerAsync("REFRESH " + std::to_string(registry.getComponent(entity, ID()).getID()), ipAdress);
    }
}

void InLoopGame::pingServer(CommandsToServer& commandsToServer, IpAdress& ipAdress)
{
    if (m_clock2.getElapsedTime().asMilliseconds() < 1000)
        return;
    m_clock2.restart();
    commandsToServer.sendToServerAsync("ALIVE", ipAdress);
}

void InLoopGame::gameInLoop(
    sf::Event& event,
    WindowManager& windowManager,
    Game& game,
    Music& music,
    CommandsToServer& commandsToServer,
    Sprite& sprite,
    sf::Clock& onGameClock,
    Registry& registry,
    ButtonManager& buttonManager,
    ChoiceMenu& choiceMenu,
    IpAdress& ipAdress)
{
    game.setCursorPosition(windowManager.getWindow());
    buttonManager.getResumeButton().checkHover(game.getCursorPosX(), game.getCursorPosY());
    buttonManager.getToMenuButton().checkHover(game.getCursorPosX(), game.getCursorPosY());
    if (buttonManager.getResumeButton().checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onPause = false;
    }
    if (buttonManager.getToMenuButton().checkClick(game.getCursorPosX(), game.getCursorPosY())) {
        game.onGame = false;
        choiceMenu.onChoice = true;
    }
    sf::Time renderElapsed = onGameClock.getElapsedTime();
    game.hasFocus = windowManager.getWindow().hasFocus();
    commandsToServer.mutex.lock();
    refreshRegistry(registry, commandsToServer, ipAdress);
    pingServer(commandsToServer, ipAdress);
    try {
        game.displayHealth(std::ref(registry), music, windowManager);
        game.movePlayer(
            std::ref(registry),
            windowManager.getMovementSpeed(),
            windowManager.getWindow().getSize().x,
            windowManager.getWindow().getSize().y,
            commandsToServer,
            sprite,
            ipAdress);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::F) {
            game.shooting(commandsToServer, registry, ipAdress);
            music.shootSound.play();
        }
        if (event.key.code == sf::Keyboard::K) {
            game.damageToPlayer(commandsToServer, registry, ipAdress);
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Escape) {
            game.isPaused();
        }
    }
    if (event.type == sf::Event::JoystickButtonReleased && game.onGame) {
        if (event.joystickButton.button == sf::Joystick::Y) {
            game.shooting(commandsToServer, registry, ipAdress);
        }
    }
    commandsToServer.mutex.unlock();
    if (renderElapsed.asMilliseconds() > windowManager.getMillisecondsPerFrame()) {
        game.moveParallax();
        game.repeatParallax();
        onGameClock.restart();
    }
    windowManager.getWindow().draw(game);
    windowManager.getWindow().draw(game.getHealPointText());
    commandsToServer.mutex.lock();
    try {
        registry.systemsManager(windowManager.getWindow());
        game.displayArrow(registry, windowManager);
        if (game.onPause) {
            buttonManager.getResumeButton().draw(windowManager.getWindow());
            buttonManager.getToMenuButton().draw(windowManager.getWindow());
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    commandsToServer.mutex.unlock();
}