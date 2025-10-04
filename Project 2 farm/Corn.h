#pragma once
#include "Crop.h"

class Corn : public Crop
{
public:
  Corn();
  void dailyUpdate() override;
  void handleEvent() override;
  bool isHighYield() const; // Bonus feature
};
