
#ifndef SFMLGAME_BUTTON_H
#define SFMLGAME_BUTTON_H

#include "GameObject.h"
#include "Gate.h"

class Button: public GameObject
{
 public:
  Button();
  void init() override;
  void update() override;
  void render(sf::RenderWindow& window) override;

  void press();
  sf::Vector2i getGatePos();
  bool isDown();

 private:
  bool down;

  std::unique_ptr<Gate> gate;
  sf::Vector2i gate_pos;
};

#endif // SFMLGAME_BUTTON_H
