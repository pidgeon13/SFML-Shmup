#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile
{
  const enum cardinal{
    N,
    S,
    E,
    W,
  };
  Vector2f position;
  CircleShape shape;
  Vector2f direction;
  float speed;

public:
  Projectile(float xPos, float yPos, float size, float xComponent, float yComponent);
  Projectile(float xPos, float yPos, float size, cardinal direction);
  
  FloatRect getRect();

  CircleShape getShape();
};