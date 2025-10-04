#include "Corn.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Corn::Corn()
    : Crop("Corn", 70, 4, 2, 2, 0.5f) // name, health, days to harvest, water/fert, event risk
{
  currentDay = 0;
}

void Corn::dailyUpdate()
{
  currentDay++;
  std::cout << "[Day " << currentDay << "] Corn is growing tall...\n";

  // Needs both water and fertilizer daily to avoid penalty
  if (waterNeededPerDay < 2)
  {
    health -= 3;
    std::cout << " Corn needs more water! -3 health.\n";
  }

  if (fertilizerNeededPerDay < 2)
  {
    health -= 3;
    std::cout << " Corn needs more fertilizer! -3 health.\n";
  }

  if (health <= 0)
  {
    health = 0;
    std::cout << "Corn has died.\n";
  }
}

void Corn::handleEvent()
{
  srand(time(0));
  float roll = static_cast<float>(rand()) / RAND_MAX;

  if (roll < eventRisk)
  {
    std::cout << " Strong wind flattens part of your Corn!\n";
    health -= 10;
  }
  else
  {
    std::cout << " Mild weather. Corn thrives today.\n";
  }

  if (health < 0)
    health = 0;
}

bool Corn::isHighYield() const
{
  return health >= 90; // Bonus yield condition
}
