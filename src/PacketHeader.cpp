
#include "PacketHeader.h"

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f v2f)
{
  return packet << v2f.x << v2f.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f v2f)
{
  return packet >> v2f.x >> v2f.y;
}