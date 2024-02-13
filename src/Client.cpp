
#include "Client.h"

Client::Client(sf::RenderWindow& game_window) : window(game_window)
{

}

void Client::connect()
{
  if (socket == nullptr)
  {
    socket = std::make_unique<sf::TcpSocket>();
  }
  if (socket->connect("127.0.0.1", 53000) == sf::Socket::Status::Done)
  {
    std::cout << "You're Connected!" << std::endl;
    connected = true;
  }
  else
  {
    std::cout << "failed to connect";
  }
}

void Client::input(sf::TcpSocket& iSocket) const
{
  while (running)
  {
    std::string str;
    std::getline(std::cin, str);
    std::cin.clear();

    if (connected)
    {
      //iSocket.send(reinterpret_cast<char*>(str.data()), str.length());
    }
  }
}

void Client::run()
{
  running = true;
  //std::thread input_thread([&] { input(*socket); });
  //input_thread.detach();
  std::thread run_threads(([&] { listen(); }));
  run_threads.detach();
}

void Client::listen()
{
  while (running && connected)
  {
    char static_buffer[1028];
    while (connected)
    {
      //std::size_t received;
      //auto status = socket->receive(static_buffer, 1028, received);
      sf::Packet packet;
      PacketHeader packet_type;
      int temp;

      // receive packet
      auto status = socket->receive(packet);

      // confirm packet type
      packet >> temp;
      packet_type = static_cast<PacketHeader>(temp);

      // collect packet content
      packet >> static_buffer;


      if (status == sf::Socket::Status::Disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket->disconnect();
        break;
      }
      else
      {
        main_game.add_message(static_buffer);
      }
    }
  }
}

void Client::init()
{
  connect();
  run();
  main_menu.init();
  main_game.init();
  win_state.init();
}

void Client::update(float dt)
{
  switch (game_state)
  {
    case GameStates::Null:
      break;
    case GameStates::MainMenu:
      main_menu.update(dt);
      break;
    case GameStates::MainGame:
      main_game.update(dt);
      break;
    case GameStates::Win:
      win_state.update(dt);
      break;
  }
}

void Client::render()
{
  switch (game_state)
  {
    case GameStates::Null:
      std::exit(0);
      break;
    case GameStates::MainGame:
      game_state = main_game.render();
      break;
    case GameStates::MainMenu:
      game_state = main_menu.render();
      break;
    case GameStates::Win:
      game_state = win_state.render();
      break;
  }
}

void Client::keyPressed(sf::Event event)
{
  sf::Packet packet;
  switch (game_state)
  {
    case GameStates::Null:
      break;
    case GameStates::MainGame:
      packet = main_game.keyPressed(event);
      if (!packet.endOfPacket())
      {
        socket->send(packet);
      }
      packet.clear();
      break;
    case GameStates::MainMenu:
      packet = main_menu.keyPressed(event);
      if (!packet.endOfPacket())
      {
        std::string s;
        packet >> s;
        main_game.setPlayerName(s);
      }
      break;
    case GameStates::Win:
      win_state.keyPressed(event);
      break;
  }
}

void Client::keyReleased(sf::Event event)
{
  switch (game_state)
  {
    case GameStates::Null:
      break;
    case GameStates::MainGame:
      main_game.keyReleased(event);
      break;
    case GameStates::MainMenu:
      break;
  }
}

void Client::textEntered(sf::Event event)
{
  switch (game_state)
  {
    case GameStates::Null:
      break;
    case GameStates::MainGame:
      main_game.textEntered(event);
      break;
    case GameStates::MainMenu:
      main_menu.textEntered(event);
      break;
  }
}