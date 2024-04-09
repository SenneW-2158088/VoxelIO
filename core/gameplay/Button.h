#pragma once

// A simple button for opengl
class Button {
public:
  virtual void onPress();
  virtual void onHold();
  virtual void onRelease();
};
