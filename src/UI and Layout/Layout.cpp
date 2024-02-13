
#include "Layout.h"

// get tile position in the form of world coordinates
// tile --> world
sf::Vector2i Layout::getTilePos(int x, int y)
{
  sf::Vector2i ans;
  ans.x = x * 16;
  ans.y = y * 16;
  return ans;
}

// search for the current tile from world coordinates
// world --> tile
sf::Vector2i Layout::getCurrentTile(float x, float y)
{
  sf::Vector2i ans;
  ans.x = floor(x / 16);
  ans.y = floor(y / 16);
  return ans;
}

// get centre of sprite with their global bounds
float Layout::getCentreX(sf::FloatRect sprite)
{
  return sprite.left + sprite.width / 2;
}
float Layout::getCentreY(sf::FloatRect sprite)
{
  return sprite.top + sprite.height / 2;
}

void Layout::setSpriteToCentre(sf::Sprite& sprite)
{
  sf::Vector2f win = {Layout::WINX / 2, Layout::WINY / 2};
  sprite.setPosition(win);
  sprite.move(-sprite.getGlobalBounds().width / 2, -sprite.getGlobalBounds().height / 2);
}

void Layout::setSpriteToCentre(sf::Text& text)
{
  sf::Vector2f win = {Layout::WINX / 2, Layout::WINY / 2};
  text.setPosition(win);
  text.move(-text.getGlobalBounds().width / 2, -text.getGlobalBounds().height / 2);
}

bool Layout::collisionCheck(sf::FloatRect sprite1, sf::FloatRect sprite2)
{
  return sprite1.intersects(sprite2);
}
