
#ifndef SFMLGAME_PACKETHEADER_H
#define SFMLGAME_PACKETHEADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

enum class PacketHeader
{
  Message = 0,
  Movement = 1,
  PlayerPos = 2,
  AllPos = 3
};

enum class MyMovementType
{
  Left = 0,
  Right = 1,
  Up = 2,
  Down = 3,
  StopX = 4,
  StopY = 5
};

sf::Packet& operator <<(sf::Packet& packet, sf::Vector2f v2f);
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f v2f);

#endif // SFMLGAME_PACKETHEADER_H
