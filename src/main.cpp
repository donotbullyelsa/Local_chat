#include "Game.h"
#include "UI and Layout/Layout.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  std::cout << "You should see a window that opens as well as this writing to "
               "console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode(Layout::WINX, Layout::WINY), "SFML Base Game");
  window.setFramerateLimit(60);

  // initialise an instance of the game class
  bool x = *std::getenv("doServer") == '1';
  Game game(window, x);

  // run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;

    // calculate delta time
    sf::Time time = clock.restart();
    float dt      = time.asSeconds();

    //'process inputs' element of the game loop
    while (window.pollEvent(event))
    {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::KeyPressed)
        game.keyPressed(event);

      if (event.type == sf::Event::KeyReleased)
        game.keyReleased(event);

      if (event.type == sf::Event::TextEntered)
      {
        game.textEntered(event);
      }
    }

    //'update' element of the game loop
    game.update(dt);

    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}
