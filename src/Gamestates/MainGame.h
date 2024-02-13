
#ifndef SFMLGAME_MAINGAME_H
#define SFMLGAME_MAINGAME_H

#include "../GameObjects/Player.h"
#include "../GameObjects/Coins.h"
#include "../GameObjects/Key.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Well.h"
#include "../UI and Layout/Tile.h"
#include "../UI and Layout/UI.h"
#include "../PacketHeader.h"
#include "Gamestates.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class MainGame: public GamestatesBase
{
 public:
  MainGame(sf::RenderWindow& game_window);

  void init() override;
  void init_tmx();

  void update(float dt) override;
  void playerMove(float dt);
  void playerCheckCollide(const std::unique_ptr<sf::Sprite>& nextPos, float dir_x, float dir_y, float dt);
  bool axisCC(const std::unique_ptr<sf::Sprite>& nextPos, float dir_x, float dir_y, float dt, bool isX, int layer); // axis-collision-check

  GameStates render() override;

  sf::Packet keyPressed(sf::Event event) override;
  void keyReleased(sf::Event event) override;
  void textEntered(sf::Event event) override;

  void add_message(std::string buffer);

  void setPlayerName(std::string name);

  std::unique_ptr<sf::Texture> tilemap = std::make_unique<sf::Texture>();
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;

 private:
  sf::RenderWindow& window;

  Player player;
  bool in_chat;
  std::string chat_input;
  UI ui = UI(window);

  std::vector<std::unique_ptr<Coins>> coins;
  std::unique_ptr<Key> key;
  std::unique_ptr<Button> button;
  std::unique_ptr<Well> well;

  void SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile);
  const int SPRITESHEET_X = 12;
  const int SPRITESHEET_Y = 11;
};

#endif // SFMLGAME_MAINGAME_H
