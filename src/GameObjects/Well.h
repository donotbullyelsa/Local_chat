
#ifndef SFMLGAME_WELL_H
#define SFMLGAME_WELL_H

#include "GameObject.h"

class Well: public GameObject
{
 public:
  Well();
  void init() override;
  void update() override;
  void render(sf::RenderWindow& window) override;

  sf::Clock clock;
  const std::string speech1 = "[Local] Suspicious well: Collect me all coins in this village and I will offer some help.";
  const std::string speech2 = "[Local] Suspicious well: A secret passage is opened.";
};

#endif // SFMLGAME_WELL_H
