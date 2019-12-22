#include "Character.h"
#include "Geometry.h"

Character::Character(float xPos, float yPos, float radius, int health, const sf::Color& color) :
  MovingCircle(xPos, yPos, radius, 200.0f, 0.0f, 0.0f),
  m_weaponCooldown(0.25f),
  m_maxHealth(health),
  m_originalColor(color),
  m_damageGracePeriod(0.0f),
  m_timeSinceDamaged(0.0f)
{
  SetColor(color);
  m_health = m_maxHealth;
  m_timeSinceLastShot = m_weaponCooldown;
}

void Character::UpdateTimeElapsedForCooldowns(float timeElapsed)
{
  m_timeSinceLastShot += timeElapsed;
  m_timeSinceDamaged += timeElapsed;
}

void Character::MoveIfInput(const KeyboardInputs& inputs, float timeElapsed)
{
  sf::Vector2f newDirection(0.0f, 0.0f);
  if (inputs.Contains(sf::Keyboard::Up) != inputs.Contains(sf::Keyboard::Down))
  {
    //We must be moving either up or down.
    if (inputs.Contains(sf::Keyboard::Up))
    {
      newDirection.y = -1;
    }
    else
    {
      newDirection.y = 1;
    }
  }
  if (inputs.Contains(sf::Keyboard::Left) != inputs.Contains(sf::Keyboard::Right))
  {
    //We must be either moving left or right.
    if (inputs.Contains(sf::Keyboard::Left))
    {
      newDirection.x = -1;
    }
    else
    {
      newDirection.x = 1;
    }
  }
  SetDirection(newDirection);
  Move(timeElapsed);
}

void Character::ShootIfInput(const KeyboardInputs& inputs, float timeElapsed, Projectiles& projectiles)
{
  
  if (m_timeSinceLastShot >= m_weaponCooldown)
  {
    sf::Vector2f weaponDirection(0.0f, 0.0f);
    //We can shoot.
    if (inputs.Contains(sf::Keyboard::W) != inputs.Contains(sf::Keyboard::S))
    {
      //We must be moving either up or down.
      if (inputs.Contains(sf::Keyboard::W))
      {
        weaponDirection.y = -1;
      }
      else
      {
        weaponDirection.y = 1;
      }
    }
    if (inputs.Contains(sf::Keyboard::A) != inputs.Contains(sf::Keyboard::D))
    {
      //We must be either moving left or right.
      if (inputs.Contains(sf::Keyboard::A))
      {
        weaponDirection.x = -1;
      }
      else
      {
        weaponDirection.x = 1;
      }
    }
    if (!Geometry::IsZero(weaponDirection))
    {
      Geometry::Normalise(weaponDirection);
      Projectile newProjectile(m_position.x, m_position.y, 5.0f, 600.0f, weaponDirection.x, weaponDirection.y, 5);
      projectiles.Add(newProjectile);
      m_timeSinceLastShot = 0.0f;
    }
  }
}

int Character::GetHealth() const
{
  return m_health;
}

void Character::SetGracePeriod(float gracePeriod)
{
  m_damageGracePeriod = gracePeriod;
}

bool Character::TakeDamage(int damage)
{
  if (m_timeSinceDamaged >= m_damageGracePeriod)
  {
    m_timeSinceDamaged = 0.0f;
    m_health -= damage;
    if (m_health < 0)
    {
      m_health = 0;
    }
    UpdateColor();
  }
  return m_health > 0;
}

void Character::UpdateColor()
{
  float fraction = m_health / static_cast<float>(m_maxHealth);
  sf::Color newColor(m_originalColor);
  newColor.a = (m_originalColor.a * m_health)/m_maxHealth;
  SetColor(newColor);
}
