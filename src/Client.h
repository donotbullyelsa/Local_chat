
#ifndef SFMLGAME_CLIENT_H
#define SFMLGAME_CLIENT_H

#include "PacketHeader.h"
#include "Gamestates/MainGame.h"
#include "Gamestates/MainMenu.h"
#include "Gamestates/WinState.h"
#include <SFML/Network.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <atomic>
#include <iostream>
#include <thread>

class Client
{
 public:
  Client(sf::RenderWindow& game_window);

  void connect();
  void input(sf::TcpSocket& iSocket) const;
  void run();
  std::atomic<bool> running = false;
  std::atomic<bool> connected = false;

  void init();
  void update(float dt);
  void render();

  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void textEntered(sf::Event event);

 private:
  std::unique_ptr<sf::TcpSocket> socket;
  void listen();

  sf::RenderWindow& window;

  GameStates game_state = GameStates::MainMenu;
  MainMenu main_menu = MainMenu(window);
  MainGame main_game = MainGame(window);
  WinState win_state = WinState(window);
};

#endif // SFMLGAME_CLIENT_H
