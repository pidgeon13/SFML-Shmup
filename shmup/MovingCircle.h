#pragma once

#include <SFML/Graphics.hpp>

class MovingCircle
{
  //This will be normalised by the class when setting it.
  sf::Vector2f m_direction;
  sf::CircleShape m_shape;
protected:
  sf::Vector2f m_position;
  float m_speed;

public:
  MovingCircle();
  MovingCircle(float xPos, float yPos, float size, float speed, float xComponent, float yComponent);
  sf::FloatRect GetRect() const;
  sf::CircleShape GetShape() const;
  sf::Vector2f GetPosition() const;
  void SetColor(const sf::Color& color);
  void SetDirection(const sf::Vector2f& directionIn);
  void Move(float time);
  void Draw(sf::RenderWindow& window);

  void Update();
};