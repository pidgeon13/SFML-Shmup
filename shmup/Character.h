#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Character
{
  Vector2f position;
  CircleShape characterShape;
  float characterSpeed;

public:
  Character(float xPos, float yPos, float size);

  FloatRect getRect();

  CircleShape getShape();

  void moveLeft(float time);
  void moveRight(float time);
  void moveUp(float time);
  void moveDown(float time);

  void update();
};