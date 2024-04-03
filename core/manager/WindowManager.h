//
// Created by Senne Wertelaers on 03/04/2024.
//

#ifndef VOXELIO_WINDOWMANAGER_H
#define VOXELIO_WINDOWMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void onResize(GLFWwindow *, int width, int height);

void error_callback(int, const char *description);

class WindowManager {
public:
  virtual GLFWwindow *getWindow() const = 0;

  virtual void update() const = 0;

  virtual void clear() const = 0;

  virtual void resize(int width, int height) = 0;

  virtual void setResizeCallback(void (*callback)(int, int)) = 0;

  virtual void setWidth(int width) = 0;

  virtual void setHeight(int height) = 0;

  virtual void setTitle(const char *title) = 0;

  virtual int getWidth() = 0;

  virtual int getHeight() = 0;

  virtual const char *getTitle() = 0;

  virtual bool shouldClose() = 0;
};

class WindowService : public WindowManager {
private:
  GLFWwindow *window;
  int width;
  int height;
  const char *title;

  void (*callback)(int, int);

private:
  void initGLFW(int width, int height, const char *title);

  void initGlad();

public:
  void update() const override;

  void clear() const override;

  void resize(int width, int height) override;

  void setResizeCallback(void (*callback)(int, int)) override;

  inline GLFWwindow *getWindow() const override { return window; };

  inline int getWidth() override { return this->width; };

  inline int getHeight() override { return this->height; };

  inline const char *getTitle() override { return this->title; };

  void setWidth(int width) override { this->width = width; };

  void setHeight(int height) override { this->height = height; };

  void setTitle(const char *title) override { this->title = title; };

  bool shouldClose() override;

public:
  WindowService(int width, int height, const char *title);

  ~WindowService();

  void start();
};

class NullWindowService : public WindowManager {
public:
  NullWindowService() = default;

  ~NullWindowService() = default;

  void update() const override{};

  void clear() const override{};

  inline void resize(int width, int height) override{};

  inline void setResizeCallback(void (*callback)(int, int)) override{};

  inline void setWidth(int width) override{};

  inline void setHeight(int height) override{};

  inline void setTitle(const char *title) override{};

  GLFWwindow * getWindow() const override {};
  inline int getWidth() override { return 0; };

  inline int getHeight() override { return 0; };

  inline const char *getTitle() override { return "NullWindowService"; };

  inline bool shouldClose() override { return true; };
};

class WindowLocator {
private:
  static WindowManager *windowManager;

public:
  WindowLocator() = delete;
  static void provide(WindowManager *windowManager);

  static WindowManager *get();
};

#endif // VOXELIO_WINDOWMANAGER_H
