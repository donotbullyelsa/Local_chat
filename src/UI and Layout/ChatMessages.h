
#ifndef SFMLGAME_CHATMESSAGES_H
#define SFMLGAME_CHATMESSAGES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class ChatMessages
{
 public:
  ChatMessages(sf::FloatRect fr, float s, sf::RenderWindow& game_window);
  void init();
  void update(sf::FloatRect fr, std::string chat_input);
  void render();

  // push from MESSAGES_NUM, pop from [0]
  void add_message(const std::string s);

  const static int MESSAGES_NUM = 10;

 private:
  std::unique_ptr<sf::Text> lines[MESSAGES_NUM];
  std::unique_ptr<sf::Text> text_input;
  sf::Font std_font;
  sf::FloatRect chatbox;
  float scale;

  int n = 0;

  sf::RenderWindow& window;
};

#endif // SFMLGAME_CHATMESSAGES_H
