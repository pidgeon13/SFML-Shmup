#pragma once

#include <SFML/Graphics.hpp>
#include "MovingCircle.h"
#include <list>

using namespace sf;

class Projectile : public MovingCircle
{
  float m_damage;

public:
  Projectile(float xPos, float yPos, float size, float speed, float xComponent, float yComponent, float damage);
};

class Projectiles
{
  std::list<Projectile> m_storage;

public:
  void MoveAndUpdateAll(float timeElapsed);
  void Add(const Projectile& newProjectile);
  void DrawAll(sf::RenderWindow& window);
};