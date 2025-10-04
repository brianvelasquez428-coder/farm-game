#pragma once
#include "Crop.h"

class Potato : public Crop
{
public:
  Potato();
  void dailyUpdate() override;
  void handleEvent() override;
};
