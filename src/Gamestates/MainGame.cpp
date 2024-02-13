
#include "MainGame.h"

MainGame::MainGame(sf::RenderWindow& game_window) : window(game_window)
{

}

void MainGame::init()
{
  GamestatesBase::init();
  next_state = GameStates::MainGame;

  // init map
  init_tmx();

  // init coins
  for (const auto& tile : TILE_MAP[1])
  {
    // moving the coins information from the tmx to the coin class
    if (tile->getID() != 0)
    {
      sf::Vector2f pos = tile->getSprite()->getPosition();
      coins.emplace_back(std::make_unique<Coins>());
      coins[coins.size() - 1]->init(Layout::getCurrentTile(pos.x, pos.y));
    }
  }

  // init key
  key = std::make_unique<Key>();
  key->init();

  // init button
  button = std::make_unique<Button>();
  button->init();

  // init well
  well = std::make_unique<Well>();
  well->init();

  // init UI
  ui.init(coins.size());
  in_chat = false;

  // init camera
  camera->zoom(CAM_ZOOM);

  // init player
  player.init();
}

void MainGame::init_tmx()
{
  tmx::Map map;
  if (!tilemap->loadFromFile("Data/kenney_tiny-town/Tilemap/tilemap_packed.png"))
  {
    std::cout << "Error: Fail to load spritesheet!" << std::endl;
  }
  if (!map.load("Data/Map/test_map1.tmx"))
  {
    std::cout << "Error: Fail to load map data!" << std::endl;
  }

  const unsigned int MAP_COLUMNS = map.getTileCount().x;
  const unsigned int MAP_ROWS = map.getTileCount().y;

  auto& tile_size = map.getTileSize();
  TILE_MAP.reserve(map.getLayers().size());

  for (const auto& layer : map.getLayers())
  {
    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
    TILE_MAP.back().reserve(tiles.size());
    for (const auto& tile : tiles)
    {
      SetTileWithID(MAP_COLUMNS, tile_size, tile);
    }
  }
}

void MainGame::update(float dt)
{
  // player collision detection must be done in the scope of game
  // as the data of map is stored here
  if (!in_chat)
  {
    playerMove(dt);
  }

  // mostly handling name text of player
  player.update(dt);

  // player collect coins
  for (int i = 0; i < coins.size(); i++)
  {
    sf::FloatRect player_rect = player.getSprite().getGlobalBounds();
    if (coins[i]->getSprite().getGlobalBounds().intersects(player_rect))
    {
      coins[i].reset();
      coins.erase(coins.begin() + i);
    }
  }

  // player collect key
  if (key != nullptr)
  {
    if (key->getSprite().getGlobalBounds().intersects(
          player.getSprite().getGlobalBounds()))
    {
      ui.key_collected = true;
      key.reset();
    }
  }

  // player press button
  if (!button->isDown())
  {
    if (button->getSprite().getGlobalBounds().intersects(
          player.getSprite().getGlobalBounds()))
    {
      button->press();

      // delete the gate in TILE_MAP
      sf::Vector2i gate_pos = button->getGatePos();
      TILE_MAP[2][gate_pos.y * 30 + gate_pos.x]->resetTile();
    }
  }

  // player open exit gate
  if (ui.key_collected)
  {
    bool done = false;
    for (int i = 10; i < 13; i++)
    {
      if ((TILE_MAP[2][8 * 30 + i]->getSprite()->getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) && (!done))
      {
        done = true;
        for (int j = 10; j < 13; j++)
        {
          TILE_MAP[2][8 * 30 + j]->resetTile();
        }
      }
    }
  }

  // player interact with well
  well->update();
  if (player.getSprite().getGlobalBounds().intersects(well->getSprite().getGlobalBounds()))
  {
    // the well speak
    if (well->clock.getElapsedTime().asSeconds() > 2)
    {
      well->clock.restart();
      if (coins.size() > 0)
      {
        ui.add_message(well->speech1);
      }
      else
      {
        ui.add_message(well->speech2);

        // unlock the secret passage
        TILE_MAP[3][8 * 30 + 27]->resetTile();
        TILE_MAP[3][2 * 30 + 13]->resetTile();
      }
    }
  }

  // ui update
  ui.update(player.getSpriteCentre(), chat_input, coins.size());

  // update camera pos (relative to player)
  camera->setCenter(player.getSpriteCentre());
  window.setView(*camera);

  // win check
  if (player.current_tile.y < 1)
  {
    next_state = GameStates::Win;
  }
}

void MainGame::playerMove(float dt)
{
  // update player direction
  std::tuple<float, float> temp = player.direction.getNormalised();
  float dirX = std::get<0>(temp);
  float dirY = std::get<1>(temp);

  // check if it is collided / moving to somewhere that is not allowed
  std::unique_ptr<sf::Sprite> nextPos = std::make_unique<sf::Sprite>();
  playerCheckCollide(nextPos, dirX, dirY, dt);

  //update player current tile
  player.current_tile = Layout::getCurrentTile(Layout::getCentreX(player.getSprite().getGlobalBounds()), Layout::getCentreY(player.getSprite().getGlobalBounds()));
}

void MainGame::playerCheckCollide(const std::unique_ptr<sf::Sprite>& nextPos, float dir_x, float dir_y, float dt)
{
  nextPos->setPosition(player.getSprite().getPosition());
  nextPos->setTextureRect(player.getSprite().getTextureRect());

  bool flag = true;
  for (int i=2; i<4; i++)
  {
    if (axisCC(nextPos, dir_x, dir_y, dt, true, i))
    {
      flag = false;
    }
  }
  if (flag)
  {
    player.moveSprite(dir_x * player.SPEED * dt, 0);
  }

  flag = true;
  for (int i=2; i<4; i++)
  {
    if (axisCC(nextPos, dir_x, dir_y, dt, false, i))
    {
      flag = false;
    }
  }
  if (flag)
  {
    player.moveSprite(0, dir_y * player.SPEED * dt);
  }
}

// axis-collision-check
bool MainGame::axisCC(const std::unique_ptr<sf::Sprite>& nextPos, float dir_x, float dir_y, float dt, bool isX, int layer)
{
  if (isX)
  {
    // project the player's location after moving in x-axis
    nextPos->move(dir_x * player.SPEED * dt, 0);
    sf::Vector2i nextTile = Layout::getCurrentTile(
      Layout::getCentreX(nextPos->getGlobalBounds()),
      Layout::getCentreY(nextPos->getGlobalBounds()));

    if (
      (!Layout::collisionCheck(
        nextPos->getGlobalBounds(),
        TILE_MAP[layer][nextTile.x + 30 * nextTile.y]
          ->getSprite()
          ->getGlobalBounds())) ||
      (TILE_MAP[layer][nextTile.x + 30 * nextTile.y]->getID() == 0))
    {
      return false;
    }
  }
  else
  {
    // project the player's location after moving in y-axis
    nextPos->move(0, dir_y * player.SPEED * dt);
    sf::Vector2i nextTile = Layout::getCurrentTile(
      Layout::getCentreX(nextPos->getGlobalBounds()),
      Layout::getCentreY(nextPos->getGlobalBounds()));

    if (
      (!Layout::collisionCheck(
        nextPos->getGlobalBounds(),
        TILE_MAP[layer][nextTile.x + 30 * nextTile.y]
          ->getSprite()
          ->getGlobalBounds())) ||
      (TILE_MAP[layer][nextTile.x + 30 * nextTile.y]->getID() == 0))
    {
      return false;
    }
  }
  return true;
}

GameStates MainGame::render()
{
  window.clear(sf::Color::Black);

  // render map
  for (int i = 0; i < TILE_MAP.size(); i++)
  {
    const auto& layer = TILE_MAP[i];
    // if not collectable layers or overlayed layer
    if ((i != 1) && (i != 4) && (i != 5))
    {
      for (const auto& tile : layer)
      {
        if ((tile->getID() > 0) && (tile->getID() < 132))
        {
          window.draw(*tile->getSprite());
        }
      }
    }
  }

  // render coins
  for (const auto& coin : coins)
  {
    window.draw(coin->getSprite());
  }

  // render key
  if (key != nullptr)
  {
    window.draw(key->getSprite());
  }

  // render button
  button->render(window);

  // render player
  player.render(window);

  // render the layers over the player (mushroom layer)
  for (const auto& tile : TILE_MAP[4])
  {
    if (tile->getID() > 0)
    {
      window.draw(*tile->getSprite());
    }
  }

  // render UI
  ui.render();

  return next_state;
}

sf::Packet MainGame::keyPressed(sf::Event event)
{
  if (!in_chat)
  {
    // key movement
    if (event.key.code == sf::Keyboard::W)
    {
      player.direction.setY(-1);
    }
    else if (event.key.code == sf::Keyboard::S)
    {
      player.direction.setY(1);
    }
    if (event.key.code == sf::Keyboard::A)
    {
      player.direction.setX(-1);
    }
    else if (event.key.code == sf::Keyboard::D)
    {
      player.direction.setX(1);
    }
  }

  else
  {
    if (event.key.code == sf::Keyboard::Enter)
    {
      sf::Packet packet = sf::Packet();
      packet << static_cast<int>(PacketHeader::Message) << reinterpret_cast<char*>(chat_input.data()) << reinterpret_cast<char*>(player.name.data());
      in_chat = !in_chat;
      chat_input = "";
      return packet;
    }
  }

  sf::Packet packet;
  packet.clear();
  return packet;
}

void MainGame::keyReleased(sf::Event event)
{
  // key movement
  if (event.key.code == sf::Keyboard::W)
  {
    player.direction.setY(0);
  }
  else if (event.key.code == sf::Keyboard::S)
  {
    player.direction.setY(0);
  }
  if (event.key.code == sf::Keyboard::A)
  {
    player.direction.setX(0);
  }
  else if (event.key.code == sf::Keyboard::D)
  {
    player.direction.setX(0);
  }
}

void MainGame::textEntered(sf::Event event)
{
  if (in_chat)
  {
    if (event.text.unicode < 128)
    {
      // get text input to std::string
      if (event.text.unicode == 8)
      {
        if (chat_input.size() > 0)
        {
          chat_input.pop_back();
        }
      }
      else if (event.text.unicode != 27)
      {
        chat_input += static_cast<char>(event.text.unicode);
      }
    }
  }
  // slash key equivalent
  else if (event.key.code == 47)
  {
    in_chat = !in_chat;
    chat_input.clear();
  }
}

void MainGame::add_message(std::string buffer)
{
  ui.add_message(buffer);
}

void MainGame::setPlayerName(std::string name)
{
  player.name = name;
}

void MainGame::SetTileWithID(const unsigned int MAP_COLUMNS, const tmx::Vector2u& tile_size, const tmx::TileLayer::Tile& tile)
{
  auto& current = *TILE_MAP.back().emplace_back(std::make_unique<Tile>(tile.ID, *tilemap));

  int x = current.getID();
  if (x > 0)
  {
    int y = floor((x - 1) / SPRITESHEET_X);
    x = (x - 1) % SPRITESHEET_X;
    current.getSprite()->setTextureRect(sf::IntRect(x * 16, y * 16, 16, 16));
    /**sf::IntRect((current.getID() * tile_size.x) - tile_size.x, 0, tile_size.x, tile_size.y)**/
  }
  current.getSprite()->setPosition(((TILE_MAP.back().size()-1) % MAP_COLUMNS) * tile_size.x, ((TILE_MAP.back().size()-1) / MAP_COLUMNS) * tile_size.y);
}
