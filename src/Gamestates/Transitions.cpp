
#include "Transitions.h"

Transitions::Transitions(sf::RenderWindow& game_window) : window(game_window)
{

}

void Transitions::init()
{
  GamestatesBase::init();

  // init background
  bg = std::make_unique<sf::Sprite>();
  bg_texture = std::make_unique<sf::Texture>();
  if (!bg_texture->loadFromFile("Data/Map/test_map1.png"))
  {
    std::cout << "Error: Failed to load menu background.";
  }
  bg->setTexture(*bg_texture);
  Layout::setSpriteToCentre(*bg);
}

void Transitions::update(float dt)
{
  GamestatesBase::update(dt);
}

GameStates Transitions::render()
{
  GamestatesBase::render();
  window.draw(*bg);
  return next_state;
}

sf::Packet Transitions::keyPressed(sf::Event event)
{
  return {};
}
