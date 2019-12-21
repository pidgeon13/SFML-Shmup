#include "Character.h"

Character::Character(float xPos, float yPos, float size) :
  characterShape(size)
{
  position.x = xPos;
  position.y = yPos;
  characterSpeed = 200.0f;
}

FloatRect Character::getRect()
{
  return characterShape.getGlobalBounds();
}

CircleShape Character::getShape()
{
  return characterShape;
}

void Character::moveLeft(float time)
{
  position.x -= characterSpeed*time;
}

void Character::moveRight(float time)
{
  position.x += characterSpeed * time;
}

void Character::moveUp(float time)
{
  position.y -= characterSpeed * time;
}

void Character::moveDown(float time)
{
  position.y += characterSpeed * time;
}

void Character::update()
{
  characterShape.setPosition(position);
}
