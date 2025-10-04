#include "Potato.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Potato::Potato()
    : Crop("Potato", 80, 5, 1, 1, 0.3f) // name, health, days to harvest, water/fert, event risk
{
  currentDay = 0;
}

void Potato::dailyUpdate()
{
  currentDay++;
  std::cout << "[Day " << currentDay << "] "
            << "Potato grows steadily...\n";

  if (waterNeededPerDay > 1)
  {
    health -= 1;
    std::cout << "Could use more water, but it's still okay.\n";
  }

  if (fertilizerNeededPerDay > 1)
  {
    health -= 1;
    std::cout << "Could use more fertilizer, but it's still okay.\n";
  }

  if (health <= 0)
  {
    health = 0;
    std::cout << "The Potato crop has died.\n";
  }
}

void Potato::handleEvent()
{
  srand(time(0));
  float roll = static_cast<float>(rand()) / RAND_MAX;

  if (roll < eventRisk)
  {
    std::cout << " A storm hits! But Potato resists well.\n";
    health -= 5; // smaller penalty
  }
  else
  {
    std::cout << " Calm day. Potato is unaffected.\n";
  }

  if (health < 0)
    health = 0;
}
