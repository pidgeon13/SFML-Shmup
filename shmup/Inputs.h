#pragma once
#include <SFML/Graphics.hpp>
#include <set>
class KeyboardInputs
{
  std::set<sf::Keyboard::Key> m_set;
  void InsertKeyIfPressed(sf::Keyboard::Key key);
public:
  void SetToCurrentInputs();
  bool Contains(sf::Keyboard::Key key) const;
  bool IsShooting() const;
};