
#include "UI.h"

UI::UI(sf::RenderWindow& game_window) : window(game_window)
{

}

void UI::init(const int coin_num)
{
  // init font
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Failed to load font.";
  }

  // init chatbox
  chatbox.init();

  // init coins-text
  coins_text = std::make_unique<sf::Text>();
  coins_text->setFont(std_font);
  coins_text->setString("Coins left: " + std::to_string(coin_num));
  coins_text->setCharacterSize(30);
  coins_text->setScale(CAM_ZOOM, CAM_ZOOM);

  // init key sprite
  key_collected = false;
  key = std::make_unique<sf::Sprite>();
  key_texture = std::make_unique<sf::Texture>();
  if (!key_texture->loadFromFile("Data/kenney_tiny-town/Tilemap/tilemap_packed.png"))
  {
    std::cout << "Error: Failed to load ui texture.";
  }
  key->setTexture(*key_texture);
  key->setTextureRect(sf::IntRect(144, 144, 16, 16));
}

void UI::update(sf::Vector2f cam_centre, std::string chat_input, const int coin_num)
{
  // update chatbox pos (relative to camera)
  chatbox.update(cam_centre, chat_input);

  // update coins-text pos (relative to camera) and content
  coins_text->setPosition(cam_centre);
  coins_text->move(window.getSize().x * CAM_ZOOM / 2, window.getSize().y * CAM_ZOOM / -2);
  coins_text->move(-coins_text->getGlobalBounds().width - 10, 10);
  coins_text->setString("Coins left: " + std::to_string(coin_num));

  // update key pos (relative to camera)
  key->setPosition(coins_text->getPosition());
  key->move(coins_text->getGlobalBounds().width - key->getGlobalBounds().width, coins_text->getGlobalBounds().height + 10);
}

void UI::render()
{
  chatbox.render();
  window.draw(*coins_text);
  if (key_collected)
  {
    window.draw(*key);
  }
}

void UI::add_message(const std::string s)
{
  chatbox.add_message(s);
}
