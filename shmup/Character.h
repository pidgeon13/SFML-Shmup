#pragma once

#include <SFML/Graphics.hpp>
#include "Inputs.h"
#include "MovingCircle.h"
#include "ListContainer.h"

class Character : public MovingCircle
{
  float m_weaponCooldown;
  float m_timeSinceLastShot;
  int m_maxHealth;
  int m_health;
  float m_damageGracePeriod;
  float m_timeSinceDamaged;
  sf::Color m_originalColor;

public:
  Character();
  Character(float xPos, float yPos, float size, int health, const sf::Color& color, int damage);
  void UpdateTimeElapsedForCooldowns(float timeElapsed);
  void MoveIfInput(const KeyboardInputs& inputs, float timeElapsed);
  void ShootIfInput(const KeyboardInputs& inputs, float timeElapsed, ListContainer<MovingCircle>& projectiles);
  int GetHealth() const;
  void SetGracePeriod(float gracePeriod);
  bool TakeDamage(int damage);
  void UpdateColor();
};