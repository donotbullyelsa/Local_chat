
#ifndef SFMLGAME_SERVER_H
#define SFMLGAME_SERVER_H

#include "PacketHeader.h"
#include <SFML/Network.hpp>
#include <thread>
#include <list>
#include <iostream>
#include <mutex>
#include <memory>

class Server
{
 public:
  void init();
  void run();
  void runThreads();
  void listen(sf::TcpSocket& cSocket);
  void send(std::string buffer, const unsigned short sender);

 private:
  std::mutex mutex;

  std::vector<std::thread> workers;
  std::vector<std::unique_ptr<sf::TcpSocket>> connections;

  std::unique_ptr<sf::TcpListener> listener;
  std::unique_ptr<sf::TcpSocket> socket;

  bool running = true;
};

#endif // SFMLGAME_SERVER_H

