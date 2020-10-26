#pragma once
#include "ListContainer.h"
#include "Character.h"

template<class T>
inline void ListContainer<T>::MoveAll(float timeElapsed)
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    itr->Move(timeElapsed);
  }
}

template<class T>
inline void ListContainer<T>::MoveAllTowardsCharacter(float timeElapsed, const Character& character)
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    sf::Vector2f enemyMovement = character.GetPosition() - itr->GetPosition();
    itr->SetDirection(enemyMovement);
    itr->Move(timeElapsed);
  }
}

template<class T>
inline void ListContainer<T>::Add(const T& newT)
{
  m_storage.push_back(newT);
}

template<class T>
inline void ListContainer<T>::DrawAll(sf::RenderWindow& window) const
{
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    itr->Draw(window);
  }
}

template<class T>
inline bool ListContainer<T>::Hits(Character& character, bool removeThoseHit)
{
  bool someHits = false;
  MovingCircle::Alignment characterAlignment = character.GetAlignment();
  for (auto itr = m_storage.begin(); itr != m_storage.end(); ++itr)
  {
    MovingCircle& movingCircle = *itr;
    if (characterAlignment != movingCircle.GetAlignment() && movingCircle.Hits(character))
    {
      someHits = true;
      character.TakeDamage(movingCircle.GetDamage());
      if (removeThoseHit)
      {
        movingCircle.SetCanRemove(true);
      }
    }
  }
  if (someHits && removeThoseHit)
  {
    RemoveUnecessaryMembers();
  }

  return someHits;
}

template<class T>
inline void ListContainer<T>::RemoveUnecessaryMembers()
{
  auto it = std::remove_if(m_storage.begin(), m_storage.end(), [](MovingCircle x) {return x.GetCanRemove(); });
  m_storage.erase(it, m_storage.end());
}

template<class T>
inline bool ListContainer<T>::IsEmpty()
{
  return m_storage.empty();
}

template<class T>
inline size_t ListContainer<T>::GetSize()
{
  return m_storage.size();
}
