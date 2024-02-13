
#ifndef SFMLGAME_CLIENTDATA_H
#define SFMLGAME_CLIENTDATA_H

#include "GameObjects/Player.h"
#include <SFML/Network.hpp>

class ClientData
{
 public:
  ClientData();
  std::unique_ptr<sf::TcpSocket> connection;
  Player player = Player();

  // waiting for connection?
  bool waiting = true;

 private:
};

#endif // SFMLGAME_CLIENTDATA_H
