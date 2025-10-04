#pragma once
#include "Crop.h"

class Strawberry : public Crop
{
public:
  Strawberry();

  void dailyUpdate() override;
  void handleEvent() override;
};