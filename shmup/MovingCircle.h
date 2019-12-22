#pragma once

#include <SFML/Graphics.hpp>

class MovingCircle
{
public:
  enum class Alignment
  {
    GOOD,
    BAD
  };

  MovingCircle();
  MovingCircle(float xPos, float yPos, float size, float speed, float xComponent, float yComponent);
  sf::FloatRect GetRect() const;
  sf::CircleShape GetShape() const;
  sf::Vector2f GetPosition() const;
  void SetColor(const sf::Color& color);
  void SetSpeed(float speed);
  void SetDirection(const sf::Vector2f& directionIn);
  void SetAlignment(Alignment alignment);
  Alignment GetAlignment() const;
  void Move(float time);
  void Draw(sf::RenderWindow& window);

  bool Hits(const MovingCircle& other);

  void Update();

private:
  //This will be normalised by the class when setting it.
  sf::Vector2f m_direction;
  sf::CircleShape m_shape;
  Alignment m_alignment;
protected:
  sf::Vector2f m_position;
  float m_speed;

};