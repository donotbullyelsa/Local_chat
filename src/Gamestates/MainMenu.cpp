
#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow& game_window) :
  Transitions(game_window), window(game_window)
{

}

void MainMenu::init()
{
  Transitions::init();
  next_state = GameStates::MainMenu;

  // init title text
  title = std::make_unique<sf::Text>();
  title->setFont(std_font);
  title->setCharacterSize(200);
  title->setString("Networked Game");
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
  name = "";
  name_text = std::make_unique<sf::Text>();
  name_text->setString("Please enter your name:");
  name_text->setFont(std_font);
  name_text->setCharacterSize(40);
  name_text->setScale(CAM_ZOOM, CAM_ZOOM);
}

void MainMenu::update(float dt)
{
  Transitions::update(dt);

  name_text->setString("Please enter your name: " + name);
  name_text->setPosition(title->getPosition());
  name_text->move(title->getGlobalBounds().width / 2 - name_text->getGlobalBounds().width / 2, 60);
}

GameStates MainMenu::render()
{
  Transitions::render();

  window.draw(*title);
  window.draw(*name_text);
  return next_state;
}

sf::Packet MainMenu::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Enter)
  {
    next_state = GameStates::MainGame;
    sf::Packet packet;
    packet << name;
    return packet;
  }
  sf::Packet packet;
  packet.clear();
  return packet;
}

void MainMenu::textEntered(sf::Event event)
{
  if (event.text.unicode < 128)
  {
    // get text input to std::string
    if (event.text.unicode == 8)
    {
      if (name.size() > 0)
      {
        name.pop_back();
      }
    }
    else if (event.text.unicode != 27)
    {
      name += static_cast<char>(event.text.unicode);
    }
  }
}
