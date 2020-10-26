#pragma once
#include <list>
class Character;

template <class T>
class ListContainer
{
public:
  std::vector<T> m_storage;
  void MoveAll(float timeElapsed);
  void MoveAllTowardsCharacter(float timeElapsed, const Character& character);
  void Add(const T& newT);
  void DrawAll(sf::RenderWindow& window) const;
  bool Hits(Character& character, bool removeThoseHit = true);
  void RemoveUnecessaryMembers();
  bool IsEmpty();
  size_t GetSize();
};