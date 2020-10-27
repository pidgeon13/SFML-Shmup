#include "MovingCircle.h"
#include "Geometry.h"
#include <assert.h>
#include "Global.h"

MovingCircle::MovingCircle()
{
  MovingCircle(0.0f, 0.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0);
}

MovingCircle::MovingCircle(float xPos, float yPos, float radius, float speed, float xComponent, float yComponent,int damage) :
  m_shape(radius),
  m_position(xPos, yPos),
  m_direction(xComponent, yComponent),
  m_speed(speed),
  m_alignment(Alignment::GOOD),
  m_canRemove(false),
  m_damage(damage),
  m_removeWhenHittingWall(true)
{
  m_shape.setOrigin(radius, radius);
  Geometry::Normalise(m_direction);
  Update();
}

sf::FloatRect MovingCircle::GetRect() const
{
  return m_shape.getGlobalBounds();
}

const sf::CircleShape& MovingCircle::GetShape() const
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

void MovingCircle::SetSpeed(float speed)
{
  m_speed = speed;
}

void MovingCircle::SetDirection(sf::Vector2f directionIn)
{
  m_direction = directionIn;
  Geometry::Normalise(m_direction);
}

void MovingCircle::SetAlignment(Alignment alignment)
{
  m_alignment = alignment;
}

void MovingCircle::SetPosition(sf::Vector2f position)
{
  m_position = position;
}

MovingCircle::Alignment MovingCircle::GetAlignment() const
{
  return m_alignment;
}

void MovingCircle::Move(float time)
{
  assert(Geometry::IsEqual(Geometry::Length2(m_direction), 1)
    || Geometry::IsEqual(Geometry::Length2(m_direction), 0));
  float newX = m_position.x + m_direction.x * m_speed * time;
  float newY = m_position.y + m_direction.y * m_speed * time;
  float maxX = Global::windowWidth - m_shape.getRadius();
  float maxY = Global::windowHeight - m_shape.getRadius();
  float minX = m_shape.getRadius();
  float minY = m_shape.getRadius();
  if (newX < minX
    || newX > maxX
    || newY < minY
    || newY > maxY)
  {
    if (m_removeWhenHittingWall)
    {
      m_canRemove = true;
    }
    else
    {
      newX = std::min(std::max(newX, minX), maxX);
      newY = std::min(std::max(newY, minY), maxY);
    }
  }
  m_position.x = newX;
  m_position.y = newY;
  Update();
}

void MovingCircle::Draw(sf::RenderWindow& window) const
{
  window.draw(m_shape);
}

void MovingCircle::SetCanRemove(bool canRemove)
{
  m_canRemove = canRemove;
}

bool MovingCircle::GetCanRemove() const
{
  return m_canRemove;
}

int MovingCircle::GetDamage() const
{
  return m_damage;
}

bool MovingCircle::Hits(const MovingCircle& other)
{
  float radius = m_shape.getRadius();
  float otherRadius = other.GetShape().getRadius();
  float distance2 = Geometry::Length2(m_position - other.GetPosition());
  return distance2 < std::pow(radius + otherRadius, 2);
}

void MovingCircle::Update()
{
  m_shape.setPosition(m_position);
}
