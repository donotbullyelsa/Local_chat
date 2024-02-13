
#include "Chatbox.h"

Chatbox::Chatbox(float s, sf::RenderWindow& game_window) : window(game_window)
{
  scale = s;
}

void Chatbox::init()
{
  // init background
  sprite = std::make_unique<sf::Sprite>();
  texture = std::make_unique<sf::Texture>();
  if (!texture->loadFromFile("Data/Images/white.jpg"))
  {
    std::cout << "Error: Failed to load chatbox texture.";
  }
  sprite->setTexture(*texture);
  sprite->setColor(sf::Color(0, 0, 0, 127));
  sprite->setScale(scale, scale);

  // init texts
  chat_messages = std::make_unique<ChatMessages>(sprite->getGlobalBounds(), scale, window);
  chat_messages->init();
}

void Chatbox::update(sf::Vector2f cam_centre, std::string chat_input)
{
  sprite->setPosition(cam_centre.x - window.getSize().x * scale / 2 + 20, cam_centre.y - window.getSize().y * scale / 2 + 20);

  chat_messages->update(sprite->getGlobalBounds(), chat_input);
}

void Chatbox::render()
{
  window.draw(*sprite);
  chat_messages->render();
}

sf::Sprite Chatbox::getSprite()
{
  return *sprite;
}

void Chatbox::add_message(const std::string s)
{
  chat_messages->add_message(s);
}
