#pragma once
#include "Crop.h"
#include <memory>
#include <vector>
#include <string>

class Player
{
private:
  int experience;
  int water;
  int attack;
  int defense;
  int money;
  std::vector<std::string> grownCrops;
  std::vector<std::string> inventory;

public:
  Player();

  void waterCrop(Crop &c);
  void fertilizeCrop(Crop &c);
  void reward();

  bool isBroke() const;
  void showStats() const;

  // Accessors and Mutators
  int getMoney() const { return money; }
  void setMoney(int m) { money = m; }

  int getXP() const { return experience; }
  void setXP(int xp) { experience = xp; }

  int getWater() const { return water; }
  void setWater(int w) { water = w; }

  int getAttack() const { return attack; }
  void setAttack(int atk) { attack = atk; }

  int getDefense() const { return defense; }
  void setDefense(int def) { defense = def; }

  void addMoney(int amount) { money += amount; }
  void addWater(int amount) { water += amount; }
  void addXP(int amount) { experience += amount; }

  void addCropHistory(const std::string &cropName) { grownCrops.push_back(cropName); }
  const std::vector<std::string> &getGrownCrops() const { return grownCrops; }

  void addToInventory(const std::string &itemName) { inventory.push_back(itemName); }
  const std::vector<std::string> &getInventory() const { return inventory; }

  void showExtras() const;
};
