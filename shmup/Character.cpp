#include "Character.h"
#include "Geometry.h"

Character::Character(float xPos, float yPos, float size) :
  MovingCircle(xPos, yPos, size, 200.0f, 0.0f, 0.0f),
  m_weaponCooldown(0.25f)
{
  m_timeSinceLastShot = m_weaponCooldown;
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

void Character::ShootIfInput(const KeyboardInputs& inputs, float timeElapsed)
{
  m_timeSinceLastShot += timeElapsed;
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
      Projectile newProjectile(m_position.x, m_position.y, 5.0f, 600.0f, weaponDirection.x, weaponDirection.y, 5.0f);
      m_projectiles.Add(newProjectile);
      m_timeSinceLastShot = 0.0f;
    }
  }
  m_projectiles.MoveAll(timeElapsed);
}

void Character::DrawAll(sf::RenderWindow& window)
{
  Draw(window);
  m_projectiles.DrawAll(window);
}