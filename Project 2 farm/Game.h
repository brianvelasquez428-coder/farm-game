#pragma once

#include "Player.h"
#include "Crop.h"
#include "Event.h"
#include "Equipment.h"

#include <memory>
#include <vector>

class Game
{
private:
  Player player;
  // Safely manages memory
  std::shared_ptr<Crop> currentCrop;
  std::unique_ptr<Equipment> equippedTool;
  std::vector<std::unique_ptr<Event>> eventPool;

  void displayCropOptions(); // List of crops to choose every cycle
  void chooseCrop();         // The crop the player chooses
  void chooseTool();         // the tool the player chooses
  void runGrowthCycle();     // goes thoughout every day, checking for events and crop health until crop dies or is harvested
  void triggerRandomEvent(); // has a random chance of occurring every day
  void saveGame() const;
  bool loadGame();

public:
  void start();
};
