
#ifndef SFMLGAME_PLAYER_H
#define SFMLGAME_PLAYER_H

#include "../UI and Layout/Vector.h"
#include "../UI and Layout/Layout.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>

class Player: public GameObject
{
 public:
  Player();
  void init() override;
  void update(float dt);
  void render(sf::RenderWindow& window) override;
  sf::Vector2f getSpriteCentre();

  Vector direction = Vector(0, 0);
  const int SPEED = 200;

  std::string name = "Name";

  sf::Clock timer;

 private:
  std::unique_ptr<sf::Text> name_text;
};

#endif // SFMLGAME_PLAYER_H
