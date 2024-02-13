
#include "ChatMessages.h"

ChatMessages::ChatMessages(sf::FloatRect fr, float s, sf::RenderWindow& game_window) : window(game_window)
{
  chatbox = fr;
  scale = s;
}

void ChatMessages::init()
{
  // init font
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Failed to load font.";
  }

  // init lines
  for (int i = 0; i < MESSAGES_NUM; i++)
  {
    // create pointers of lines
    lines[i] = std::make_unique<sf::Text>();

    // set lines scale, string and font
    lines[i]->setFont(std_font);
    lines[i]->setString("");
    lines[i]->setScale(scale, scale);
    lines[i]->setCharacterSize(10);
  }

  // create pointers of input text
  text_input = std::make_unique<sf::Text>();

  // set input text scale, string and font
  text_input->setFont(std_font);
  text_input->setString("_");
  text_input->setScale(scale, scale);
  text_input->setCharacterSize(10);
}

void ChatMessages::update(sf::FloatRect fr, std::string chat_input)
{
  chatbox = fr;
  const float LINE_DISTANCE = (chatbox.height - 10 * 2) / (MESSAGES_NUM);
  for (int i = 0; i < MESSAGES_NUM; i++)
  {
    // set lines position
    if (i == 0)
    {
      lines[i]->setPosition(chatbox.left + 10, chatbox.top + 10);
    }
    else
    {
      lines[i]->setPosition(lines[i - 1]->getPosition());
      lines[i]->move(0, LINE_DISTANCE);
    }
  }

  // handle text input
  text_input->setPosition(lines[MESSAGES_NUM - 1]->getPosition());
  text_input->move(0, LINE_DISTANCE);
  chat_input += "_";
  text_input->setString(chat_input);
}

void ChatMessages::render()
{
  for (int i = 0; i < MESSAGES_NUM; i++)
  {
    window.draw(*lines[i]);
    window.draw(*text_input);
  }
}

// push from [MESSAGES_NUM - 1], pop from [0]
void ChatMessages::add_message(const std::string s)
{
  for (int i = 1; i < MESSAGES_NUM; i++)
  {
    lines[i - 1]->setString(lines[i]->getString());
  }
  lines[MESSAGES_NUM - 1]->setString(s);
  std::cout << s << std::endl;
}

