
#include "Server.h"

void Server::init()
{
  if (listener == nullptr)
  {
    listener = std::make_unique<sf::TcpListener>();
  }
  if (listener->listen(53000) != sf::Socket::Done)
  {

  }
}

void Server::run()
{
  std::thread run_threads(([&] { runThreads(); }));
  run_threads.detach();
}

void Server::runThreads()
{
  while (running)
  {
    sf::TcpSocket& cSock =
      connections.emplace_back(std::make_unique<sf::TcpSocket>()).operator*();
    if (listener->accept(cSock) != sf::Socket::Done)
    {
      connections.pop_back();
      return;
    }
    std::cout << "Client connected @" << cSock.getRemotePort() << std::endl;
    workers.emplace_back([&]{
                           listen(cSock);
                         });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //std::cout << "detected disconnect\n";
    std::lock_guard<std::mutex>lck(mutex);

    for (int i = 0; i < connections.size(); ++i)
    {
      if (connections[i]->getLocalPort() == cSock.getLocalPort())
      {
        continue;
      }
      connections.erase(std::next(connections.begin(), i));
      break;
    }
  }
}

void Server::listen(sf::TcpSocket& cSocket)
{
  bool continue_receiving = true;

  while (continue_receiving)
  {
    char data[1028] = "";
    sf::Packet packet = sf::Packet();

    // receive packet
    auto status = cSocket.receive(packet);

    std::string sender_port = std::to_string(cSocket.getRemotePort());
    std::string buffer;
    std::string sender_name;
    PacketHeader packet_type;
    int temp;

    // confirm packet type
    packet >> temp;
    packet_type = static_cast<PacketHeader>(temp);

    // collect packet content
    packet >> data;
    packet >> sender_name;

    if (status == sf::Socket::Status::Disconnected)
    {
      continue_receiving = false;
      buffer = sender_name + " disconnected.";
      std::cout << buffer << std::endl;
    }
    else
    {
      buffer = sender_name + ": " + reinterpret_cast<char*>(data);
    }

    if (buffer != sender_name + ": ")
    {
      buffer = "[Global] " + buffer;
      send(buffer, cSocket.getRemotePort());
    }

    std::cout << buffer << '\n';
  }
  cSocket.disconnect();
}

void Server::send(std::string buffer, const unsigned short sender)
{
  auto message = reinterpret_cast<char*>(buffer.data());

  std::lock_guard<std::mutex>lck(mutex);

  sf::Packet packet;
  packet << static_cast<int>(PacketHeader::Message);
  packet << message;

  for (auto & connection: connections)
  {
    // send to every client except for the sender
    //if (sender != connection->getRemotePort())
    {
      connection->send(packet);
    }
  }
}