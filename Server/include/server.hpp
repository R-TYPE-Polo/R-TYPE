/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** server
*/

#pragma once

#include "Systems.hpp"
#include "client.hpp"
#include "entities.hpp"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <deque>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include <cstdlib>

class Server
{
public:
    Server() : m_socket(m_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 7171))
    {
        m_clock = std::clock();
    }

    void startListening(Registry& registry);
    void startSending();
    void sendMessage(TransferData data);
    void sendAllEntites(Registry& registry);
    void spawnBoss(Registry& registry);
    void GameLoop(Registry& registry);
    void Level1_Loop(Registry& registry, std::vector<Entity> enemies);
    void Level2_Loop(Registry& registry, std::vector<Entity> enemies);
    void PlayerLoop(Registry& registry);
    void damageThePlayer(Registry& registry, int damage, int id);
    void gameLoop(Registry& registry);
    bool isClient(const boost::asio::ip::udp::endpoint& clientEndpoint);

private:
    boost::asio::io_service m_ioService;
    boost::asio::ip::udp::socket m_socket;
    boost::asio::ip::udp::endpoint m_remoteEndpoint;
    boost::array<char, 128> m_recvBuf{};
    std::deque<TransferData> m_messages;
    std::mutex m_messageMutex;
    std::mutex m_registeryMutex;
    std::mutex m_clientMutex;
    std::vector<Client> m_clients;
    bool m_gameStarted = false;
    int m_currentLevel = 1;
    std::clock_t m_clock;
    unsigned char m_buffer[sizeof(TransferData)]{};

    void handleReceivedData(
        const boost::system::error_code& error,
        std::size_t bytesReceived,
        Registry& registry,
        boost::asio::ip::udp::endpoint& remoteEndpoint);
    void addMessage(const std::string& message);
    std::size_t createPlayer(Registry& registry);
    void createEnemy(Registry& registry);
    void createBullet(Registry& registry, int posx, int posy);
    void createBullet2(Registry& registry, int posx, int posy);
    void createBoss(Registry& registry);
    void createArrow(Registry& registry);
    void playerMove(Registry& registry, COMMAND direction, std::size_t id);
    void enemyMove(Registry& registry, Entity& entity, std::size_t id);
    void enemyShootAndMove(Registry& registry, Entity& entity, std::size_t id);
    void addClient(const boost::asio::ip::udp::endpoint& clientEndpoint, std::size_t id);
    void refreshClientRegistry(Registry& registry, int id);
    bool startGame(Registry& registry);
    void createWall(Registry& registry, int posx, int posy, int sizex, int sizey);
    void sendMessage(TransferData data, Client& client);
};
