#include "MovingCircle.h"
#include "Geometry.h"
#include <assert.h>

MovingCircle::MovingCircle()
{
  MovingCircle(0.0f, 0.0f, 5.0f, 10.0f, 0.0f, 0.0f);
}

MovingCircle::MovingCircle(float xPos, float yPos, float size, float speed, float xComponent, float yComponent) :
  m_shape(size),
  m_position(xPos, yPos),
  m_direction(xComponent, yComponent),
  m_speed(speed)
{
  m_shape.setOrigin(size, size);
  Geometry::Normalise(m_direction);
}

sf::FloatRect MovingCircle::GetRect() const
{
  return m_shape.getGlobalBounds();
}

sf::CircleShape MovingCircle::GetShape() const
{
  return m_shape;
}

sf::Vector2f MovingCircle::GetPosition() const
{
  return m_position;
}

void MovingCircle::SetColor(const sf::Color& color)
{
  m_shape.setFillColor(color);
}

void MovingCircle::SetDirection(const sf::Vector2f& directionIn)
{
  m_direction = directionIn;
  Geometry::Normalise(m_direction);
}

void MovingCircle::Move(float time)
{
  assert(Geometry::IsEqual(Geometry::Length2(m_direction), 1)
    || Geometry::IsEqual(Geometry::Length2(m_direction), 0));
  m_position.x += m_direction.x * m_speed * time;
  m_position.y += m_direction.y * m_speed * time;
  Update();
}

void MovingCircle::Draw(sf::RenderWindow& window)
{
  window.draw(m_shape);
}

void MovingCircle::Update()
{
  m_shape.setPosition(m_position);
}
