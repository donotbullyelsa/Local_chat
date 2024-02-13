
#ifndef SFMLGAME_GAMEOBJECT_H
#define SFMLGAME_GAMEOBJECT_H

#include "../UI and Layout/Layout.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class GameObject
{
 public:
  GameObject();
  GameObject(const std::string l, const sf::Vector2i pos);
  GameObject(const std::string l, const sf::IntRect r, const sf::Vector2i pos);
  virtual void init();
  virtual void update();
  virtual void render(sf::RenderWindow& window);

  sf::Sprite getSprite();
  void moveSprite(float x, float y);
  sf::Vector2i current_tile;

 protected:
  std::unique_ptr<sf::Sprite> sprite;
  std::unique_ptr<sf::Texture> texture;
  std::string texture_link;
  sf::IntRect texture_rect;

  const std::string STD_FONT_LINK = "Data/Fonts/OpenSans-Bold.ttf";
  sf::Font std_font;
};

#endif // SFMLGAME_GAMEOBJECT_H
