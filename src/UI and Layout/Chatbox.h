
#ifndef SFMLGAME_CHATBOX_H
#define SFMLGAME_CHATBOX_H

#include "ChatMessages.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Chatbox
{
 public:
  Chatbox(float s, sf::RenderWindow& game_window);
  void init();
  void update(sf::Vector2f cam_centre, std::string chat_input);
  void render();

  sf::Sprite getSprite();
  void add_message(const std::string s);

 private:
  float scale;
  std::unique_ptr<sf::Sprite> sprite;
  std::unique_ptr<sf::Texture> texture;

  std::unique_ptr<ChatMessages> chat_messages;

  sf::RenderWindow& window;
};

#endif // SFMLGAME_CHATBOX_H
