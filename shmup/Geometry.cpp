#include "Geometry.h"

bool Geometry::Normalise(sf::Vector2f& vecIn)
{
  bool wasNormalised = false;
  float divisor = sqrt(Length2(vecIn));
  if (divisor != 0)
  {
    float scale = 1.0f / divisor;
    vecIn.x *= scale;
    vecIn.y *= scale;
    wasNormalised = true;
  }
  return wasNormalised;
}

bool Geometry::Length2(const sf::Vector2f & vecIn)
{
  return std::pow(vecIn.x, 2) + std::pow(vecIn.y, 2);
}

bool Geometry::IsZero(const sf::Vector2f & vecIn, float epsilon)
{
  return Length2(vecIn) < epsilon;
}
