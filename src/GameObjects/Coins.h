
#ifndef SFMLGAME_COINS_H
#define SFMLGAME_COINS_H

#include "GameObject.h"

class Coins: public GameObject
{
 public:
  Coins();
  void init(const sf::Vector2i pos);
  void update() override;

 private:
  std::unique_ptr<sf::Sprite> sprite;
};

#endif // SFMLGAME_COINS_H
