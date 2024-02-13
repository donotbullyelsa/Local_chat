
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window, bool server) : window(game_window), isServer(server)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  if (isServer)
  {
    server = std::make_unique<Server>();
    server->init();
    server->run();
  }
  else
  {
    client = std::make_unique<Client>(window);
    client->init();
  }
  return true;
}

void Game::update(float dt)
{
  if (!isServer)
  {
    client->update(dt);
  }
}

void Game::render()
{
  if (!isServer)
  {
    client->render();
  }
  else
  {
    window.clear(sf::Color::Black);
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  if (!isServer)
  {
    client->keyPressed(event);
  }
}

void Game::keyReleased(sf::Event event)
{
  if (!isServer)
  {
    client->keyReleased(event);
  }
}

void Game::textEntered(sf::Event event)
{
  if (!isServer)
  {
    client->textEntered(event);
  }
}
