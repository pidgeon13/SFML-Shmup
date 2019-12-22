#pragma once

#include <SFML/Graphics.hpp>
#include "MovingCircle.h"
#include <list>

using namespace sf;

class Character;

class Projectile : public MovingCircle
{
  int m_damage;
  bool m_canRemove;

public:
  Projectile(float xPos, float yPos, float size, float speed, float xComponent, float yComponent, int damage);
  int GetDamage() const;
  void SetCanRemove(bool canRemove);
  bool GetCanRemove() const;
};

class Projectiles
{
  std::list<Projectile> m_storage;

public:
  void MoveAll(float timeElapsed);
  void Add(const Projectile& newProjectile);
  void DrawAll(sf::RenderWindow& window);
  bool Hits(Character& character);
};