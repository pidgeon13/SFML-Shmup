#include "Projectile.h"
#include <cmath>

Projectile::Projectile(float xPos, float yPos, float size, float xComponent, float yComponent) :
  shape(size)
{
  position.x = xPos;
  position.y = yPos;
  float divisor = sqrt(std::pow(xComponent, 2) + std::pow(yComponent, 2));
  direction.x = xComponent / divisor;
  direction.y = yComponent / divisor;
}

Projectile::Projectile(float xPos, float yPos, float size, cardinal cardinalIn)
{
  position.x = xPos;
  position.y = yPos;
  switch(cardinalIn)
  {
  case cardinal::E:
    direction.x = 1;
    direction.y = 0;
  case cardinal::W:
    direction.x = -1;
    direction.y = 0;
  case cardinal::N:
    direction.x = 0;
    direction.y = -1;
  case cardinal::S:
    direction.x = 0;
    direction.y = 1;
  }
}

FloatRect Projectile::getRect()
{
  return shape.getGlobalBounds();
}

CircleShape Projectile::getShape()
{
  return shape;
}
