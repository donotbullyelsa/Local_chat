
#include "Coins.h"

Coins::Coins()
{
  texture_link = "Data/kenney_tiny-town/Tilemap/tilemap_packed.png";
  texture_rect = sf::IntRect(144, 112, 16, 16);
  current_tile = {0, 0};
}

void Coins::init(const sf::Vector2i pos)
{
  current_tile = pos;
  GameObject::init();
}

void Coins::update()
{
  GameObject::update();
}
