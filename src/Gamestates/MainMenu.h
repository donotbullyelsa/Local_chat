
#ifndef SFMLGAME_MAINMENU_H
#define SFMLGAME_MAINMENU_H

#include "Transitions.h"
#include "../UI and Layout/Layout.h"

class MainMenu: public Transitions
{
 public:
  MainMenu(sf::RenderWindow& game_window);

  void init() override;
  void update(float dt) override;
  GameStates render() override;

  sf::Packet keyPressed(sf::Event event) override;
  void textEntered(sf::Event event) override;

 private:
  sf::RenderWindow& window;

  std::unique_ptr<sf::Text> title;
  std::unique_ptr<sf::Text> name_text;
  std::string name;
};

#endif // SFMLGAME_MAINMENU_H
