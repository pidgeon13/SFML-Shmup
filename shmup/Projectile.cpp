#include "Projectile.h"

Projectile::Projectile(float xPos, float yPos, float size, float speed, float xComponent, float yComponent, float damage) :
  MovingCircle(xPos, yPos, size, speed, xComponent, yComponent),
  m_damage(damage)
{
}

void Projectiles::MoveAndUpdateAll(float timeElapsed)
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    itr->Move(timeElapsed);
    itr->Update();
  }
}

void Projectiles::Add(const Projectile& newProjectile)
{
  m_storage.push_back(newProjectile);
}

void Projectiles::DrawAll(sf::RenderWindow & window)
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    itr->Draw(window);
  }
}
