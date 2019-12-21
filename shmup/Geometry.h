#pragma once
#include <SFML/Graphics.hpp>
namespace Geometry
{
  bool Normalise(sf::Vector2f& vecIn);
  bool Length2(const sf::Vector2f& vecIn);
  bool IsZero(const sf::Vector2f& vecIn, float epsilon = 0.0000001f);
}