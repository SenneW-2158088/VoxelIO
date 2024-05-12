#pragma once

#include "graphics/Lighting.h"
class Lightable {
private:
  lighting::Light* light;

public:
  void setLight(lighting::Light* light) {
    this->light = light;
  }
}
