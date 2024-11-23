#include "Game.h"
#include <sstream>
#include <algorithm>
#include <set>
#include "Format.h"

using namespace sf;

Game::Game() :
  m_window(VideoMode(Dimensions::windowWidth, Dimensions::windowHeight), "Pong"),
  m_score(0),
  m_player(Dimensions::windowWidth / 2.0f, Dimensions::windowHeight / 2.0f, 20, 50, sf::Color::Cyan, 0),
  m_pauseText("Game Paused", m_font, 100),
  m_deadText("You died", m_font, 100),
  m_restartText("Press enter to restart", m_font, 40),
  m_currentState(PLAYING)
{
  m_player.SetGracePeriod(0.5f);
  m_font.loadFromFile("DS-DIGIT.ttf");
  m_scoreText.setFont(m_font);
  m_scoreText.setCharacterSize(60);
  m_scoreText.setFillColor(Color::Red);
  Format::CenterText(m_pauseText, Dimensions::windowWidth / 2.0f, Dimensions::windowHeight / 2.0f);
  Format::CenterText(m_deadText, Dimensions::windowWidth / 2.0f, 1 * Dimensions::windowHeight / 3.0f);
  Format::CenterText(m_restartText, Dimensions::windowWidth / 2.0f, 2 * Dimensions::windowHeight / 3.0f);
}

void Game::RestartGame()
{
  m_score = 0;
  m_player.SetPosition(sf::Vector2f(Dimensions::windowWidth / 2.0f, Dimensions::windowHeight / 2.0f));
  m_player.Reset();
  m_enemies.m_storage.clear();
  m_projectiles.m_storage.clear();
  m_currentState = PLAYING;
}


void Game::Draw()
{
  //Update the HUD text
  std::stringstream ss;
  ss << "Score:" << m_score << "    Health:" << m_player.GetHealth();
  m_scoreText.setString(ss.str());

  //Draw
  m_window.clear(Color(0, 0, 50, 255));

  switch (m_currentState)
  {
  case PLAYING:
    m_player.Draw(m_window);
    m_enemies.DrawAll(m_window);
    m_projectiles.DrawAll(m_window);
    break;
  case PAUSED:
    m_window.draw(m_pauseText);
    break;
  case DEAD:
    m_window.draw(m_deadText);
    m_window.draw(m_restartText);
    break;
  }

  // Draw our score
  m_window.draw(m_scoreText);

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
  if (m_player.GetHealth() == 0)
  {
    m_currentState = DEAD;
  }
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
    Character enemy(0, m_enemies.GetSize()*Dimensions::windowHeight / static_cast<float>(m_score + 1), 40, 100, sf::Color::Red, 10);
    enemy.SetSpeed(120.0f);
    enemy.SetAlignment(MovingCircle::Alignment::BAD);
    m_enemies.Add(enemy);
  }
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
        else if (m_currentState == DEAD && event.key.code == sf::Keyboard::Enter)
        {
          RestartGame();
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
