
#ifndef SFMLGAME_GAMESTATES_H
#define SFMLGAME_GAMESTATES_H

#include "../UI and Layout/Layout.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <memory>

enum class GameStates
{
  Null,
  MainGame,
  MainMenu,
  Win
};

class GamestatesBase
{
 public:
  virtual void init();
  virtual void update(float dt);
  virtual GameStates render();

  virtual sf::Packet keyPressed(sf::Event event);
  virtual void keyReleased(sf::Event event);
  virtual void textEntered(sf::Event event);

 protected:
  std::shared_ptr<sf::View> camera;
  const float CAM_ZOOM = Layout::WORLD_SCALE;

  GameStates next_state;
  sf::Font std_font;

 private:

};

#endif // SFMLGAME_GAMESTATES_H
