#pragma once
#include <string>
#include "Player.h"

class Equipment
{
protected:
  std::string name;
  int expBonus;
  int waterBonus;
  int attackBonus;
  int defenseBonus;

public:
  Equipment(std::string n, int exp, int water, int atk, int def);
  virtual void apply(Player &player) = 0;
  std::string getName() const;
  virtual ~Equipment() {}
};

// ---- Derived Tools ----
class WateringCan : public Equipment
{
public:
  WateringCan();
  void apply(Player &player) override;
};

class TarpShield : public Equipment
{
public:
  TarpShield();
  void apply(Player &player) override;
};

class GoldenPitchfork : public Equipment
{
public:
  GoldenPitchfork();
  void apply(Player &player) override;
};
