#include "Lettuce.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Lettuce::Lettuce()
    : Crop("Lettuce", 60, 4, 2, 1, 0.4f) // name, health, days to harvest, water/fert, event risk
{
  currentDay = 0;
}

void Lettuce::dailyUpdate()
{
  currentDay++;
  std::cout << "[Day " << currentDay << "] Lettuce continues growing...\n";

  // Apply regeneration if still alive
  if (health > 0 && health < 100)
  {
    health += 2;
    if (health > 100)
      health = 100;
    std::cout << " Strong roots help Lettuce recover 2 health.\n";
  }

  // Apply penalties if underfed
  if (waterNeededPerDay > 2)
  {
    health -= 2;
    std::cout << "Needs more water! Losing health.\n";
  }

  if (fertilizerNeededPerDay > 1)
  {
    health -= 2;
    std::cout << "Needs more fertilizer! Losing health.\n";
  }

  if (health <= 0)
  {
    health = 0;
    std::cout << "Lettuce has died.\n";
  }
}

void Lettuce::handleEvent()
{
  srand(time(0));
  float roll = static_cast<float>(rand()) / RAND_MAX;

  if (roll < eventRisk)
  {
    std::cout << " Fungal infection! Lettuce resists, but takes minor damage.\n";
    health -= 7;
  }
  else
  {
    std::cout << " Sunny day, no events.\n";
  }

  if (health < 0)
    health = 0;
}
