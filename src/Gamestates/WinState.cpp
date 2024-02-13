
#include "WinState.h"

WinState::WinState(sf::RenderWindow& game_window) :
  Transitions(game_window), window(game_window)
{

}

void WinState::init()
{
  Transitions::init();
  next_state = GameStates::Win;

  // init title text
  title = std::make_unique<sf::Text>();
  title->setFont(std_font);
  title->setCharacterSize(200);
  title->setString("You've won!");
  title->setScale(CAM_ZOOM, CAM_ZOOM);

  sf::Vector2f v2f;
  v2f.x = window.getSize().x;
  v2f.y = window.getSize().y;
  Layout::setSpriteToCentre(*title);
  title->move(0, -50);

  // init camera
  camera->setCenter(window.getSize().x / 2, window.getSize().y / 2);
  camera->zoom(CAM_ZOOM);
  window.setView(*camera);

  // init name text
  continue_text = std::make_unique<sf::Text>();
  continue_text->setString("Press <Enter> to continue.");
  continue_text->setFont(std_font);
  continue_text->setCharacterSize(40);
  continue_text->setScale(CAM_ZOOM, CAM_ZOOM);
  continue_text->setPosition(title->getPosition());
  continue_text->move(title->getGlobalBounds().width / 2 - continue_text->getGlobalBounds().width / 2, 60);

}

void WinState::update(float dt)
{
  Transitions::update(dt);

  camera->setCenter(window.getSize().x / 2, window.getSize().y / 2);
  window.setView(*camera);
}

GameStates WinState::render()
{
  Transitions::render();
  window.draw(*title);
  window.draw(*continue_text);
  return next_state;
}

sf::Packet WinState::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    next_state = GameStates::Null;
  }
  return {};
}
