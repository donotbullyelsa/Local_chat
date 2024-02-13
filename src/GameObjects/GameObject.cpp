
#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const std::string l, const sf::Vector2i pos)
{
  texture_link = l;
  texture_rect = sf::IntRect(0, 0, 0, 0);
  current_tile = pos;
}

GameObject::GameObject(const std::string l, const sf::IntRect r, const sf::Vector2i pos)
{
  texture_link = l;
  texture_rect = r;
  current_tile = pos;
}

void GameObject::init()
{
  sprite = std::make_unique<sf::Sprite>();
  texture = std::make_unique<sf::Texture>();

  // init texture
  if (!texture->loadFromFile(texture_link))
  {
    std::cout << "Error: Failed to load game object texture.";
  }

  sprite->setTexture(*texture);
  if (texture_rect != sf::IntRect(0, 0, 0, 0))
  {
    sprite->setTextureRect(texture_rect);
  }
  else
  {
    texture_rect = static_cast<sf::IntRect>(sprite->getGlobalBounds());
  }

  // init sprite
  sf::Vector2i initPos = Layout::getTilePos(current_tile.x, current_tile.y);
  sprite->setPosition(initPos.x,initPos.y);

  // init std_font
  if (!std_font.loadFromFile(STD_FONT_LINK))
  {
    std::cout << "Error: Failed to load font of game object.";
  }
}

void GameObject::update()
{

}

void GameObject::render(sf::RenderWindow& window)
{
  window.draw(*sprite);
}

sf::Sprite GameObject::getSprite()
{
  return *sprite;
}

void GameObject::moveSprite(float x, float y)
{
  sprite->move(x, y);
}
