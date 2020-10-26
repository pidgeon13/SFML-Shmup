#include "Game.h"
#include <sstream>
#include <algorithm>
#include <set>

using namespace sf;

void Game::Draw()
{
  //Update the HUD text
  std::stringstream ss;
  ss << "Score:" << m_score << "    Health:" << m_player.GetHealth();
  m_hud.setString(ss.str());

  //Draw
  m_window.clear(Color(0, 0, 50, 255));

  m_player.Draw(m_window);
  m_enemies.DrawAll(m_window);
  m_projectiles.DrawAll(m_window);

  if (m_currentState == PAUSED)
  {
    m_window.draw(m_pause);
  }

  // Draw our score
  m_window.draw(m_hud);

  // Show everything we just drew
  m_window.display();
}

void Game::DoGameLogic(float elapsedTime)
{
  //Player and input
  KeyboardInputs currentInputs;
  currentInputs.SetToCurrentInputs();
  m_player.UpdateTimeElapsedForCooldowns(elapsedTime);
  m_player.MoveIfInput(currentInputs, elapsedTime);
  m_player.ShootIfInput(currentInputs, elapsedTime, m_projectiles);
  m_previousInputs = currentInputs;

  //Enemy
  m_enemies.MoveAllTowardsCharacter(elapsedTime, m_player);

  //Projectiles
  m_projectiles.MoveAll(elapsedTime);

  //Collisions
  m_enemies.Hits(m_player, false);
  for (auto itr = m_enemies.m_storage.begin(); itr != m_enemies.m_storage.end(); ++itr)
  {
    Character& enemy = *itr;
    m_projectiles.Hits(enemy);
    if (enemy.GetHealth() == 0)
    {
      ++m_score;
      enemy.SetCanRemove(true);
    }
  }
  m_enemies.RemoveUnecessaryMembers();
  m_projectiles.RemoveUnecessaryMembers();

  while (m_enemies.GetSize() < m_score + 1)
  {
    //Create enemies if needed
    Character enemy(0, m_enemies.GetSize()*Global::windowHeight / static_cast<float>(m_score + 1), 40, 100, sf::Color::Red, 10);
    enemy.SetSpeed(120.0f);
    enemy.SetAlignment(MovingCircle::Alignment::BAD);
    m_enemies.Add(enemy);
  }
}

Game::Game() :
  m_window(VideoMode(Global::windowWidth, Global::windowHeight), "Pong"),
  m_score(0),
  m_player(Global::windowWidth / 2.0f, Global::windowHeight / 2.0f, 20, 50, sf::Color::Cyan, 0),
  m_pause("Game Paused", m_font, 100),
  m_currentState(PLAYING)
{
  m_player.SetGracePeriod(0.5f);
  m_font.loadFromFile("DS-DIGIT.ttf");
  m_hud.setFont(m_font);
  m_hud.setCharacterSize(60);
  m_hud.setFillColor(Color::Red);
  FloatRect pauseRect = m_pause.getLocalBounds();
  m_pause.setOrigin(pauseRect.width / 2, pauseRect.height / 2);
  m_pause.setPosition(Global::windowWidth / 2.0f, Global::windowHeight / 2.0f);
}

void Game::DoLoop()
{
  while (m_window.isOpen())
  {
    float elapsedTime = m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
    Event event;
    while (m_window.pollEvent(event))
    {
      if (event.type == Event::Closed)
      {
        m_window.close();
      }
      if (event.type == Event::KeyReleased)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          switch (m_currentState)
          {
          case PLAYING: 
            m_currentState = PAUSED;
            break;
          case PAUSED: 
            m_currentState = PLAYING;
            break;
          default:
            //Do nothing
            break;
          }
        }
      }
    }
    if (m_currentState == PLAYING)
    {
      DoGameLogic(elapsedTime);
    }

    Draw();
  }
}
