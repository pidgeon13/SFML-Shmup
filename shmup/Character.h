#pragma once

#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "MovingCircle.h"
#include "Projectile.h"

class Character : public MovingCircle
{
  float m_weaponCooldown;
  float m_timeSinceLastShot;
  const int m_maxHealth;
  int m_health;
  float m_damageGracePeriod;
  float m_timeSinceDamaged;
  sf::Color m_originalColor;

public:
  Character(float xPos, float yPos, float size, int health, const sf::Color& color);
  void UpdateTimeElapsedForCooldowns(float timeElapsed);
  void MoveIfInput(const KeyboardInputs& inputs, float timeElapsed);
  void ShootIfInput(const KeyboardInputs& inputs, float timeElapsed, Projectiles& projectiles);
  int GetHealth() const;
  void SetGracePeriod(float gracePeriod);
  bool TakeDamage(int damage);
  void UpdateColor();
};