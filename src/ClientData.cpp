
#include "ClientData.h"

ClientData::ClientData()
{
  connection = std::make_unique<sf::TcpSocket>();
  player.init();
}

