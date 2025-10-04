#include "Strawberry.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Strawberry::Strawberry()
    : Crop("Strawberry", 50, 3, 2, 1, 0.6f) // name, health, days to harvest, water/fert, event risk
{
  currentDay = 0;
}

void Strawberry::dailyUpdate()
{
  currentDay++;
  std::cout << "[Day " << currentDay << "] "
            << "Strawberry grows a bit...\n";

  // Reduce health slightly if under-watered or under-fertilized
  if (waterNeededPerDay > 2)
  {
    health -= 2;
    std::cout << "Not enough water! Health drops slightly.\n";
  }

  if (fertilizerNeededPerDay > 1)
  {
    health -= 2;
    std::cout << "Lack of fertilizer! Health drops slightly.\n";
  }

  if (health <= 0)
  {
    health = 0;
    std::cout << "Strawberry has died.\n";
  }
}

void Strawberry::handleEvent()
{
  srand(time(0));
  float roll = static_cast<float>(rand()) / RAND_MAX;

  if (roll < eventRisk)
  {
    std::cout << "  Pests have attacked your Strawberry crop!\n";
    health -= 10;

    if (health < 0)
      health = 0;
  }
  else
  {
    std::cout << " No events today. The crop is safe.\n";
  }
}
