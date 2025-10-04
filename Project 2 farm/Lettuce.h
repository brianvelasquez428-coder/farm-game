#pragma once
#include "Crop.h"

class Lettuce : public Crop
{
public:
  Lettuce();
  void dailyUpdate() override;
  void handleEvent() override;
};
