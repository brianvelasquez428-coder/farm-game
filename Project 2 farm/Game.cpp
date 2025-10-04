#include "Game.h"
#include "Strawberry.h"
#include "Potato.h"
#include "Lettuce.h"
#include "Corn.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstdio> // for std::remove
#include <limits>

void Game::start()
{
  srand(static_cast<unsigned>(time(0)));

  // Creates the starting screen and options for starting
  char choice;
  std::cout << "\n==== Welcome to Harvest Days ====\n";
  std::cout << "Choose an option:\n";
  std::cout << "  (L) Load saved game\n";
  std::cout << "  (N) New game\n";
  std::cout << "  (D) Delete saved data\n";
  std::cout << "Your choice: ";
  std::cin >> choice;

  if (choice == 'L' || choice == 'l') // Loads a game if found. If not found, starts a new game
  {
    if (!loadGame())
    {
      std::cout << "No saved game found. Starting a new game.\n";
    }
  }
  else if (choice == 'D' || choice == 'd') // Deletes any saved data from previous game if found. If not found, starts a new game
  {
    std::cout << "  Are you sure you want to delete all save data? (y/n): ";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y')
    {
      if (std::remove("savegame.txt") == 0)
      {
        std::cout << "  Save data deleted successfully.\n";
      }
      else
      {
        std::cout << "  No save data found to delete.\n";
      }
    }
    else
    {
      std::cout << " Deletion cancelled. Continuing without deleting.\n";
    }

    std::cout << "Starting a new game...\n";
  }

  while (true)
  {
    player.showStats();
    chooseCrop();
    chooseTool();
    runGrowthCycle();

    if (currentCrop->isDead())
    {
      std::cout << " Your crop has died. Game over.\n";
      break;
    }

    if (player.isBroke())
    {
      std::cout << " You're out of money and can't continue farming.\n";
      break;
    }

    char choice;
    std::cout << "Do you want to continue to the next crop cycle? (y/n/s): ";
    std::cin >> choice;
    if (choice == 's' || choice == 'S')
    {
      saveGame();
      std::cout << " Manual save complete. Continuing...\n";
    }
    else if (choice != 'y' && choice != 'Y')
    {
      std::cout << "\n Exiting the game...\n";
      std::cout << "Thank you for playing Harvest Days!\n";
      std::cout << "Press Enter to close...";
      std::cin.get();
      break;
    }
  }
}

void Game::displayCropOptions()
{
  std::cout << "\nChoose your crop:\n";
  std::cout << "1. Strawberry (fast, fragile)\n";
  std::cout << "2. Potato (slow, hardy)\n";
  std::cout << "3. Lettuce (heals daily)\n";
  std::cout << "4. Corn (bonus yield if healthy)\n";
}

void Game::chooseCrop()
{
  displayCropOptions();
  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    currentCrop = std::make_shared<Strawberry>();
    break;
  case 2:
    currentCrop = std::make_shared<Potato>();
    break;
  case 3:
    currentCrop = std::make_shared<Lettuce>();
    break;
  case 4:
    currentCrop = std::make_shared<Corn>();
    break;
  default:
    std::cout << "Invalid choice. Defaulting to Strawberry.\n";
    currentCrop = std::make_shared<Strawberry>();
  }
}

void Game::chooseTool()
{
  std::cout << "\nChoose a tool to equip this cycle:\n";
  std::cout << "1. Watering Can (+3 water)\n";
  std::cout << "2. Tarp Shield (+5 defense)\n";
  std::cout << "3. Golden Pitchfork (+XP and yield bonus)\n";

  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    equippedTool = std::make_unique<WateringCan>();
    break;
  case 2:
    equippedTool = std::make_unique<TarpShield>();
    break;
  case 3:
    equippedTool = std::make_unique<GoldenPitchfork>();
    break;
  default:
    std::cout << "Invalid choice. No tool equipped.\n";
  }

  if (equippedTool)
  {
    equippedTool->apply(player);
  }
}

void Game::runGrowthCycle()
{
  std::cout << "\n Starting crop growth for " << currentCrop->getName() << "...\n";

  while (!currentCrop->isReadyToHarvest() && !currentCrop->isDead())
  {
    std::cout << "\n Day " << currentCrop->getCurrentDay() + 1 << "\n";
    player.showStats();
    player.showExtras();

    // Player action phase
    player.waterCrop(*currentCrop);
    player.fertilizeCrop(*currentCrop);

    // Crop update
    currentCrop->dailyUpdate();

    // Random event
    triggerRandomEvent();

    std::string input;
    std::cout << "\n--- End of Day " << currentCrop->getCurrentDay() << " ---\n";
    std::cout << "\nOptions:\n";
    std::cout << "  [Enter]  - Next Day\n";
    std::cout << "  save     - Save Game\n";
    std::cout << "  exit     - Quit Game\n";
    std::cout << "> ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    if (input == "save" || input == "SAVE" || input == "Save")
    {
      saveGame();
    }
    else if (input == "exit" || input == "EXIT" || input == "Exit")
    {
      std::cout << "\n Exiting game. Progress will not be saved unless you saved manually.\n";
      std::cout << "Thank you for playing Harvest Days!\n";
      std::cout << "Press Enter to close...";
      std::cin.get(); // Wait for the user to press Enter
      std::exit(0);
    }
  }

  if (currentCrop->isReadyToHarvest())
  {
    std::cout << "\n " << currentCrop->getName() << " is ready to harvest!\n";
    player.reward();
    player.addCropHistory(currentCrop->getName());

    // Example inventory reward
    player.addToInventory("Harvest Crate");
  }
}

void Game::triggerRandomEvent()
{
  if (eventPool.empty())
  {
    eventPool.emplace_back(std::make_unique<RainEvent>());
    eventPool.emplace_back(std::make_unique<FreeToolEvent>());
    eventPool.emplace_back(std::make_unique<PestAttackEvent>());
    eventPool.emplace_back(std::make_unique<DroughtEvent>());
  }

  float chance = static_cast<float>(rand()) / RAND_MAX;
  if (chance < 0.5f)
  { // 50% chance of event
    int index = rand() % eventPool.size();
    std::cout << "\n Event triggered: " << eventPool[index]->getName() << "\n";
    eventPool[index]->trigger(player, *currentCrop);
  }
  else
  {
    std::cout << "\n No event today.\n";
  }
}

void Game::saveGame() const
{
  std::ofstream out("savegame.txt");
  if (!out)
  {
    std::cerr << "Failed to save game.\n";
    return;
  }

  out << player.getXP() << " "
      << player.getWater() << " "
      << player.getAttack() << " "
      << player.getDefense() << " "
      << player.getMoney() << "\n";

  out << (currentCrop ? currentCrop->getName() : "None") << "\n";
  out << (equippedTool ? equippedTool->getName() : "None") << "\n";

  for (const auto &item : player.getInventory())
    out << "INV " << item << "\n";

  for (const auto &crop : player.getGrownCrops())
    out << "HIST " << crop << "\n";

  out.close();
  std::cout << "\n Game saved successfully!\n";
}

bool Game::loadGame()
{
  std::ifstream in("savegame.txt");
  if (!in)
  {
    std::cout << "No saved game found.\n";
    return false;
  }

  int xp, water, atk, def, money;
  std::string cropName, toolName, line;

  in >> xp >> water >> atk >> def >> money;
  in >> cropName >> toolName;
  std::getline(in, line); // consume newline

  // Restore crop
  if (cropName == "Strawberry")
    currentCrop = std::make_shared<Strawberry>();
  else if (cropName == "Potato")
    currentCrop = std::make_shared<Potato>();
  else if (cropName == "Lettuce")
    currentCrop = std::make_shared<Lettuce>();
  else if (cropName == "Corn")
    currentCrop = std::make_shared<Corn>();
  else
    currentCrop = nullptr;

  // Restore tool
  if (toolName == "Watering Can")
    equippedTool = std::make_unique<WateringCan>();
  else if (toolName == "Tarp Shield")
    equippedTool = std::make_unique<TarpShield>();
  else if (toolName == "Golden Pitchfork")
    equippedTool = std::make_unique<GoldenPitchfork>();

  player = Player();
  player.addXP(xp);
  player.addWater(water - 5);   // assuming default is 5
  player.addMoney(money - 100); // assuming default is 100

  // Parse inventory and crop history
  while (std::getline(in, line))
  {
    if (line.rfind("INV ", 0) == 0)
      player.addToInventory(line.substr(4));
    else if (line.rfind("HIST ", 0) == 0)
      player.addCropHistory(line.substr(5));
  }

  std::cout << " Game loaded!\n";
  return true;
}
