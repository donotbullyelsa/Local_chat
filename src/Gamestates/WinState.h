
#ifndef SFMLGAME_WINSTATE_H
#define SFMLGAME_WINSTATE_H

#include "Transitions.h"

class WinState: public Transitions
{
 public:
  WinState(sf::RenderWindow& game_window);
  void init() override;
  void update(float dt) override;
  GameStates render() override;
  sf::Packet keyPressed(sf::Event event) override;

 private:
  sf::RenderWindow& window;

  std::unique_ptr<sf::Text> title;
  std::unique_ptr<sf::Text> continue_text;
};

#endif // SFMLGAME_WINSTATE_H
