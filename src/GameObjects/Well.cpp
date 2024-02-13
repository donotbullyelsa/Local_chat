
#include "Well.h"

Well::Well()
{
  texture_link = "Data/kenney_tiny-town/Tilemap/tilemap_packed.png";
  texture_rect = sf::IntRect(128, 128, 16, 16);
  current_tile = {25, 13};
}

void Well::init()
{
  GameObject::init();
}

void Well::update()
{
  GameObject::update();
}

void Well::render(sf::RenderWindow& window)
{
  // Is drawn in tile map, so no need to render

  //window.draw(*sprite);
}
