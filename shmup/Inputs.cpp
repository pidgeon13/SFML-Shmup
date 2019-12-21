#include "Inputs.h"
#include <SFML/Graphics.hpp>

void KeyboardInputs::InsertKeyIfPressed(sf::Keyboard::Key key)
{
  if (sf::Keyboard::isKeyPressed(key))
  {
    m_set.insert(key);
  }
}

void KeyboardInputs::SetToCurrentInputs()
{
  InsertKeyIfPressed(sf::Keyboard::Left);
  InsertKeyIfPressed(sf::Keyboard::Right);
  InsertKeyIfPressed(sf::Keyboard::Up);
  InsertKeyIfPressed(sf::Keyboard::Down);
  InsertKeyIfPressed(sf::Keyboard::W);
  InsertKeyIfPressed(sf::Keyboard::A);
  InsertKeyIfPressed(sf::Keyboard::S);
  InsertKeyIfPressed(sf::Keyboard::D);
}

bool KeyboardInputs::Contains(sf::Keyboard::Key key) const
{
  return m_set.count(key) != 0;
}

bool KeyboardInputs::IsShooting() const
{
  return
    Contains(sf::Keyboard::W)
    || Contains(sf::Keyboard::A)
    || Contains(sf::Keyboard::S)
    || Contains(sf::Keyboard::D);
}
