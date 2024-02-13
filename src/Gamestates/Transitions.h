
#ifndef SFMLGAME_TRANSITIONS_H
#define SFMLGAME_TRANSITIONS_H

#include "Gamestates.h"

class Transitions: public GamestatesBase
{
 public:
  Transitions(sf::RenderWindow& game_window);
  void init() override;
  void update(float dt) override;
  GameStates render() override;
  sf::Packet keyPressed(sf::Event event) override;

 protected:
  std::unique_ptr<sf::Sprite> bg;
  std::unique_ptr<sf::Texture> bg_texture;

 private:
  sf::RenderWindow& window;
};

#endif // SFMLGAME_TRANSITIONS_H
