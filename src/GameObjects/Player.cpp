
#include "Player.h"

Player::Player()
{
  texture_link = "Data/kenney_tiny-battle/Tilemap/tilemap_packed.png";
  texture_rect = sf::IntRect(256, 96 + (rand() % 4) * 16, 16, 16);
  current_tile = {1, 9};
}

void Player::init()
{
  GameObject::init();
  name_text = std::make_unique<sf::Text>();
  name_text->setFont(std_font);
  name_text->setString(name);
  name_text->setCharacterSize(20);
  name_text->setScale(Layout::WORLD_SCALE, Layout::WORLD_SCALE);
}

void Player::update(float dt)
{
  GameObject::update();

  // update name text;
  name_text->setString(name);
  name_text->setPosition(sprite->getPosition());
  name_text->move(sprite->getGlobalBounds().width / 2 - name_text->getGlobalBounds().width / 2, -name_text->getGlobalBounds().height - 5);
}

void Player::render(sf::RenderWindow& window)
{
  GameObject::render(window);
  window.draw(*name_text);
}

sf::Vector2f Player::getSpriteCentre()
{
  sf::Vector2f v2;
  v2.x = Layout::getCentreX(sprite->getGlobalBounds());
  v2.y = Layout::getCentreY(sprite->getGlobalBounds());
  return v2;
}

