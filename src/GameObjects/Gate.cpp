
#include "Gate.h"

Gate::Gate()
{
  texture_link = "Data/kenney_simplified-platformer-pack/Tilesheet/platformPack_tilesheet_small.png";
  texture_rect = sf::IntRect(96, 96, 16, 16);
  current_tile = {17, 32};
}