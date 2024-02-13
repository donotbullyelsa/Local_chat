
#include "Key.h"

Key::Key()
{
  texture_link = "Data/kenney_tiny-town/Tilemap/tilemap_packed.png";
  texture_rect = sf::IntRect(144, 144, 16, 16);
  current_tile = {1, 38};
}