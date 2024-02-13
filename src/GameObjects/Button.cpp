
#include "Button.h"

Button::Button()
{
  texture_link = "Data/kenney_simplified-platformer-pack/Tilesheet/platformPack_tilesheet_small.png";
  texture_rect = sf::IntRect(160, 80, 16, 16);
  current_tile = {1, 27};
}

void Button::init()
{
  GameObject::init();
  gate = std::make_unique<Gate>();
  gate->init();
  gate_pos = gate->current_tile;
  down = false;
}

void Button::update()
{
  GameObject::update();
}

void Button::render(sf::RenderWindow& window)
{
  GameObject::render(window);
  if (gate != nullptr)
  {
    gate->render(window);
  }
}

void Button::press()
{
  down = true;
  texture_rect = sf::IntRect(176, 80, 16, 16);
  sprite->setTextureRect(texture_rect);
  gate.reset();
}

sf::Vector2i Button::getGatePos()
{
  return gate_pos;
}

bool Button::isDown()
{
  return down;
}