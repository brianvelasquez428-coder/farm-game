#pragma once
#include <string>

class Crop
{
protected:
  std::string name;
  int health;
  int daysToHarvest;
  int currentDay;
  int waterNeededPerDay;
  int fertilizerNeededPerDay;
  float eventRisk;

public:
  Crop(std::string n, int h, int dth, int water, int fert, float risk);

  virtual void dailyUpdate() = 0; // the specific updates for every crop as the days pass
  virtual void handleEvent() = 0; // How each crop will handle each event

  virtual void applyWater(int amount);
  virtual void applyFertilizer(int amount);

  virtual bool isReadyToHarvest() const;
  virtual bool isDead() const;

  std::string getName() const;
  int getHealth() const { return health; }
  void setHealth(int h) { health = h; }

  int getCurrentDay() const { return currentDay; }
  void setCurrentDay(int day) { currentDay = day; }

  int getDaysToHarvest() const { return daysToHarvest; }

  virtual ~Crop() {}
};
