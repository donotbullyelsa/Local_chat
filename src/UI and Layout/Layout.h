
#ifndef SFMLGAME_LAYOUT_H
#define SFMLGAME_LAYOUT_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Layout
{
  sf::Vector2i getTilePos(int x, int y);
  sf::Vector2i getCurrentTile(float x, float y);
  float getCentreX(sf::FloatRect sprite);
  float getCentreY(sf::FloatRect sprite);
  void setSpriteToCentre(sf::Sprite& sprite);
  void setSpriteToCentre(sf::Text& text);
  bool collisionCheck(sf::FloatRect sprite1, sf::FloatRect sprite2);

  const float WORLD_SCALE = 0.2f;
  const float WINX = 1920.0f;
  const float WINY = 1080.0f;
};

#endif // SFMLGAME_LAYOUT_H
