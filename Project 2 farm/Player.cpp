#include "Player.h"
#include <iostream>

Player::Player()
    : experience(0), water(5), attack(5), defense(5), money(100) {}

void Player::waterCrop(Crop &c)
{
  if (water >= 1)
  {
    c.applyWater(1);
    water--;
    std::cout << " You watered the crop. Water left: " << water << "\n";
  }
  else
  {
    std::cout << " Not enough water to tend the crop!\n";
  }
}

void Player::fertilizeCrop(Crop &c)
{
  if (money >= 5)
  {
    c.applyFertilizer(1);
    money -= 5;
    std::cout << " You fertilized the crop. Money left: $" << money << "\n";
  }
  else
  {
    std::cout << " Not enough money to buy fertilizer!\n";
  }
}

void Player::reward()
{
  int earnedXP = 10 + (rand() % 11);    // 10-20 XP
  int earnedMoney = 20 + (rand() % 31); // $20-50

  experience += earnedXP;
  money += earnedMoney;
  water += 2;

  std::cout << " Crop harvested! You earned " << earnedXP
            << " XP and $" << earnedMoney << ".\n";
  std::cout << " Bonus: +2 water. Current water: " << water << "\n";
}

bool Player::isBroke() const
{
  return money < 5;
}

void Player::showStats() const
{
  std::cout << "\n=== Player Stats ===\n"
            << "XP      : " << experience << "\n"
            << "Water   : " << water << "\n"
            << "Attack  : " << attack << "\n"
            << "Defense : " << defense << "\n"
            << "Money   : $" << money << "\n";
}

void Player::showExtras() const
{
  std::cout << "\n=== Inventory ===\n";
  if (inventory.empty())
    std::cout << "(empty)\n";
  else
    for (const auto &item : inventory)
      std::cout << "• " << item << "\n";

  std::cout << "\n=== Crop History ===\n";
  if (grownCrops.empty())
    std::cout << "(no crops harvested yet)\n";
  else
    for (const auto &crop : grownCrops)
      std::cout << "• " << crop << "\n";
}
