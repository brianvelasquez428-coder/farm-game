#include "Equipment.h"
#include <iostream>

// ---- Base Constructor ----
Equipment::Equipment(std::string n, int exp, int water, int atk, int def)
    : name(n), expBonus(exp), waterBonus(water), attackBonus(atk), defenseBonus(def) {}

std::string Equipment::getName() const
{
  return name;
}

// ---- Watering Can ----
WateringCan::WateringCan() : Equipment("Watering Can", 0, 3, 0, 0) {}

void WateringCan::apply(Player &player)
{
  std::cout << " Using Watering Can: +3 water.\n";
  player.addWater(waterBonus);
}

// ---- Tarp Shield ----
TarpShield::TarpShield() : Equipment("Tarp Shield", 0, 0, 0, 5) {}

void TarpShield::apply(Player &player)
{
  std::cout << " Tarp Shield activated: +5 defense.\n";
  // Optional: implement defense-based damage mitigation in future
  player.addXP(2); // Optional passive bonus
}

// ---- Golden Pitchfork ----
GoldenPitchfork::GoldenPitchfork() : Equipment("Golden Pitchfork", 5, 0, 3, 0) {}

void GoldenPitchfork::apply(Player &player)
{
  std::cout << " Golden Pitchfork: +3 attack, +5 XP bonus.\n";
  player.addXP(expBonus);
  player.addMoney(5); // bonus yield simulation
}
