
#ifndef SFMLGAME_UI_H
#define SFMLGAME_UI_H

#include "Chatbox.h"
#include "Layout.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class UI
{
 public:
  UI(sf::RenderWindow& game_window);
  void init(const int coin_num);
  void update(sf::Vector2f cam_centre, std::string chat_input, const int coin_num);
  void render();

  void add_message(const std::string s);
  bool key_collected;

 private:
  sf::RenderWindow& window;
  const float CAM_ZOOM = Layout::WORLD_SCALE;

  sf::Font std_font;
  std::unique_ptr<sf::Text> coins_text;
  std::unique_ptr<sf::Sprite> key;
  std::unique_ptr<sf::Texture> key_texture;

  Chatbox chatbox = Chatbox(CAM_ZOOM, window);
};

#endif // SFMLGAME_UI_H
