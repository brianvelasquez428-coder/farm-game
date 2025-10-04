#pragma once
#include "Crop.h"
#include "Player.h"

class Event
{
public:
  virtual void trigger(Player &player, Crop &crop) = 0;
  virtual std::string getName() const = 0;
  virtual ~Event() {}
};

// ---- Positive Events ----
class RainEvent : public Event
{
public:
  void trigger(Player &player, Crop &crop) override;
  std::string getName() const override { return "Rain Event"; }
};

class FreeToolEvent : public Event
{
public:
  void trigger(Player &player, Crop &crop) override;
  std::string getName() const override { return "Free Tool Event"; }
};

// ---- Negative Events ----
class PestAttackEvent : public Event
{
public:
  void trigger(Player &player, Crop &crop) override;
  std::string getName() const override { return "Pest Attack"; }
};

class DroughtEvent : public Event
{
public:
  void trigger(Player &player, Crop &crop) override;
  std::string getName() const override { return "Drought"; }
};
