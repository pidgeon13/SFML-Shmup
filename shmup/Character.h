#pragma once

#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "MovingCircle.h"
#include "Projectile.h"

class Character : public MovingCircle
{
  float m_weaponCooldown;
  float m_timeSinceLastShot;
  Projectiles m_projectiles;
public:
  Character(float xPos, float yPos, float size);
  void MoveIfInput(const KeyboardInputs& inputs, float timeElapsed);
  void ShootIfInput(const KeyboardInputs& inputs, float timeElapsed);
  void DrawAll(sf::RenderWindow& window);
};