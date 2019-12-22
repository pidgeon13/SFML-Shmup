#include <sstream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <set>
#include "Inputs.h"

using namespace sf;

int main()
{
  int windowWidth = 1024;
  int windowHeight = 768;
  RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

  int score = 0;
  bool isPaused = false;

  Character player(windowWidth / 2.0f, windowHeight / 2.0f, 20, 50, sf::Color::Cyan);
  player.SetGracePeriod(0.5f);

  Character enemy(0, windowHeight / 2.0f, 40, 100, sf::Color::Red);
  enemy.SetSpeed(120.0f);
  enemy.SetAlignment(MovingCircle::Alignment::BAD);

  Projectiles allProjectiles;
  Clock clock;
  Text hud;

  Font font;
  font.loadFromFile("DS-DIGIT.ttf");

  hud.setFont(font);
  hud.setCharacterSize(60);
  hud.setFillColor(Color::Red);

  Text pause("Game Paused", font, 100);
  pause.setFillColor(Color::White);
  FloatRect pauseRect = pause.getLocalBounds();
  pause.setOrigin(pauseRect.width / 2, pauseRect.height / 2);
	pause.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
  KeyboardInputs previousInputs;
  while (window.isOpen())
  {
    float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    Event event;
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
      {
        window.close();
      }
      if (event.type == Event::KeyReleased)
      {
        if (event.key.code == sf::Keyboard::Escape)
        {
          isPaused = !isPaused;
        }
      }
    }
    if (!isPaused)
    {
      //Do actual game stuff

      //player stuff
      KeyboardInputs currentInputs;
      currentInputs.SetToCurrentInputs();
      player.UpdateTimeElapsedForCooldowns(elapsedTime);
      player.MoveIfInput(currentInputs, elapsedTime);
      player.ShootIfInput(currentInputs, elapsedTime, allProjectiles);
      previousInputs = currentInputs;

      //enemy stuff
      Vector2f enemyMovement = player.GetPosition() - enemy.GetPosition();
      enemy.SetDirection(enemyMovement);
      enemy.Move(elapsedTime);

      //Projectiles
      allProjectiles.MoveAll(elapsedTime);

      //Collisions
      if (enemy.Hits(player))
      {
        player.TakeDamage(10);
      }
      allProjectiles.Hits(enemy);
    }
    // Update the HUD text
    std::stringstream ss;
    ss << "Score:" << score << "    Health:" << player.GetHealth();
    hud.setString(ss.str());

    //Draw//
    window.clear(Color(0, 0, 50, 255));

    player.Draw(window);
    enemy.Draw(window);
    allProjectiles.DrawAll(window);

    if (isPaused)
    {
      window.draw(pause);
    }

    // Draw our score
    window.draw(hud);

    // Show everything we just drew
    window.display();
  }
  return 0;
}