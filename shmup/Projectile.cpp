#include "Projectile.h"
#include "Character.h"
#include <algorithm>  

Projectile::Projectile(float xPos, float yPos, float radius, float speed, float xComponent, float yComponent, int damage) :
  MovingCircle(xPos, yPos, radius, speed, xComponent, yComponent),
  m_damage(damage),
  m_canRemove(false)
{
}

int Projectile::GetDamage() const
{
  return m_damage;
}

void Projectile::SetCanRemove(bool canRemove)
{
  m_canRemove = canRemove;
}

bool Projectile::GetCanRemove() const
{
  return m_canRemove;
}

void Projectiles::MoveAll(float timeElapsed)
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    itr->Move(timeElapsed);
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

bool Projectiles::Hits(Character& character)
{
  bool someHits = false;
  MovingCircle::Alignment characterAlignment = character.GetAlignment();
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    Projectile& currentProjectile = *itr;
    if (characterAlignment != currentProjectile.GetAlignment() && currentProjectile.Hits(character))
    {
      someHits = true;
      character.TakeDamage(currentProjectile.GetDamage());
      currentProjectile.SetCanRemove(true);
    }
  }
  if (someHits)
  {
    auto it = std::remove_if(m_storage.begin(), m_storage.end(), [](Projectile x) {return x.GetCanRemove(); });
    m_storage.erase(it, m_storage.end());
  }

  return someHits;
}
