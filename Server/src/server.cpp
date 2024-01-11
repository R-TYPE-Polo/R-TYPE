/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "server.hpp"

#include "entities.hpp"

void Server::startListening(Registry& registry)
{
    auto receiveCallback = [this, &registry](const boost::system::error_code& error, std::size_t bytesReceived) {
        m_registeryMutex.lock();
        handleReceivedData(error, bytesReceived, registry, m_remoteEndpoint);
        m_registeryMutex.unlock();
        startListening(registry);
    };
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_remoteEndpoint, receiveCallback);
    m_ioService.run();
}

void Server::startSending()
{
    TransferData data;
    while (true) {
        data = {.command = EMPTY};
        this->m_MessageMutex.lock();
        if (!m_messages.empty()) {
            data = m_messages.back();
        }
        this->m_MessageMutex.unlock();
        if (!(data.command == EMPTY)) {
            sendMessage(data);
            this->m_MessageMutex.lock();
            m_messages.pop_back();
            this->m_MessageMutex.unlock();
        }
    }
}

void Server::sendMessage(TransferData data)
{
    unsigned char buffer[sizeof(TransferData)];
    std::memcpy(buffer, &data, sizeof(TransferData));

    for (const auto& client : m_clients) {
        m_socket.async_send_to(boost::asio::buffer(buffer), client.getEndpoint(), [](const boost::system::error_code&, std::size_t) {
        });
    }
}

bool Server::isClient(const boost::asio::ip::udp::endpoint& clientEndpoint)
{
    for (const auto& client : m_clients) {
        if (client == clientEndpoint) {
            return true;
        }
    }
    return false;
}

void Server::addClient(const boost::asio::ip::udp::endpoint& clientEndpoint, std::size_t id)
{
    if (find(m_clients.begin(), m_clients.end(), clientEndpoint) == m_clients.end()) {
        Client client(clientEndpoint, id);
        m_clients.push_back(client);
        std::cout << "Client added: " << clientEndpoint.address().to_string() << ":" << clientEndpoint.port() << std::endl;
    }
}

void Server::PlayerLoop(Registry& registry)
{
    while (1) {
        std::vector<Client> clients;
        m_ClientMutex.lock();
        for (auto& client : m_clients) {
            if (registry.hasEntity(client.getId())) {
                clients.push_back(client);
            }
        }
        m_clients = clients;
        m_ClientMutex.unlock();
        if (m_clients.size() == 0 && gameStarted) {
            std::cout << "No more clients, exiting" << std::endl;
            std::vector<std::size_t> ids;
            m_registeryMutex.lock();
            for (Entity& entity : registry.getListEntities()) {
                ids.push_back(registry.getComponent(entity, ID()).getID());
            }
            for (std::size_t id : ids) {
                registry.deleteById(id);
            }
            m_registeryMutex.unlock();
            gameStarted = false;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for (auto& client : m_clients) {
            std::cout << "Client " << client.getEndpoint() << " is alive: " << client.isAlive() << std::endl;
            if (!client.isAlive()) {
                addMessage("DELETE " + std::to_string(client.getId()) + "\n");
                m_registeryMutex.lock();
                registry.deleteById(client.getId());
                m_registeryMutex.unlock();
            }
            m_ClientMutex.lock();
            client.setAlive(false);
            m_ClientMutex.unlock();
        }
    }
}