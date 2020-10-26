#pragma once

#include "Character.h"
#include "State.h"
#include "ListContainer.hpp"
#include <SFML/Graphics.hpp>
#include "Inputs.h"

class Game
{
  size_t m_score;
  enum States {
    PLAYING,
    PAUSED,
    DEAD
  };

  States m_currentState;

  Character m_player;
  ListContainer<Character> m_enemies;
  ListContainer<MovingCircle> m_projectiles;

  sf::Clock m_clock;
  sf::Text m_hud;
  sf::Font m_font;
  sf::Text m_pause;
  sf::RenderWindow m_window;

  KeyboardInputs m_previousInputs;

  void Draw();
  void DoGameLogic(float elapsedTime);

public:
  Game();
  void DoLoop();
};

