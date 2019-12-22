#pragma once
#include <SFML/Graphics.hpp>
namespace Geometry
{
  static const float floatEpsilon = 0.00001f;
  bool Normalise(sf::Vector2f& vecIn);
  float Length2(const sf::Vector2f& vecIn);
  bool IsZero(const sf::Vector2f& vecIn, float epsilon = floatEpsilon);
  bool IsEqual(float x, float y, float epsilon = floatEpsilon);
}