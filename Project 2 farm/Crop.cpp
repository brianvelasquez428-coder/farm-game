#include "Crop.h"
#include <iostream>

Crop::Crop(std::string n, int h, int dth, int water, int fert, float risk)
    : name(n), health(h), daysToHarvest(dth),
      waterNeededPerDay(water), fertilizerNeededPerDay(fert),
      eventRisk(risk), currentDay(0) {}

void Crop::applyWater(int amount)
{
  if (amount >= waterNeededPerDay)
  {
    std::cout << "Watered successfully.\n";
  }
  else
  {
    std::cout << "Not enough water! Health may decline.\n";
    health -= 2;
  }
}

void Crop::applyFertilizer(int amount)
{
  if (amount >= fertilizerNeededPerDay)
  {
    std::cout << "Fertilized successfully.\n";
  }
  else
  {
    std::cout << "Insufficient fertilizer! Health may decline.\n";
    health -= 2;
  }
}

bool Crop::isReadyToHarvest() const
{
  return currentDay >= daysToHarvest && health > 0;
}

bool Crop::isDead() const
{
  return health <= 0;
}

std::string Crop::getName() const
{
  return name;
}
