#include "Event.h"
#include <iostream>
#include <cstdlib>

// ---- Positive Events ----

void RainEvent::trigger(Player &player, Crop &crop)
{
  std::cout << " Rain event! Your crop is watered for free.\n";
  crop.applyWater(2);
  player.addWater(1); // bonus for the player
}

void FreeToolEvent::trigger(Player &player, Crop &crop)
{
  std::cout << " You found a free tool! (+$10 bonus)\n";
  player.addMoney(10);
}

// ---- Negative Events ----

void PestAttackEvent::trigger(Player &player, Crop &crop)
{
  std::cout << " Pest attack! Crop health takes a hit.\n";
  crop.applyFertilizer(0); // simulate failed defense
  crop.applyWater(0);      // simulate neglect
}

void DroughtEvent::trigger(Player &player, Crop &crop)
{
  std::cout << " Drought! Water supply is reduced.\n";
  player.addWater(-2);
  crop.applyWater(0); // no water means health drops inside crop logic
}
