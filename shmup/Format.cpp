#include "Format.h"

void Format::CenterText(sf::Text& text, float posx, float posy)
{
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.width / 2, textRect.height / 2);
  text.setPosition(posx, posy);
}
