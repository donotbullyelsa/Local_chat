
#include "Gamestates.h"

void GamestatesBase::init()
{
  next_state = GameStates::Null;
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Fail to load font.";
  }

  camera = std::make_shared<sf::View>(sf::FloatRect(0, 0, Layout::WINX, Layout::WINY));
}

void GamestatesBase::update(float dt)
{

}

GameStates GamestatesBase::render()
{
  return next_state;
}

sf::Packet GamestatesBase::keyPressed(sf::Event event)
{
  return {};
}

void GamestatesBase::keyReleased(sf::Event event)
{

}

void GamestatesBase::textEntered(sf::Event event)
{

}
