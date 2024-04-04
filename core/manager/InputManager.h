//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_INPUTMANAGER_H
#define VOXELIO_INPUTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

struct InputKeymap {
    int up, down, left, right, space;
};

class InputListener {
public:
    virtual void onInput(InputKeymap map) {};
    virtual void onMouseMove(double x, double y){};
};

class InputManager {
private:
    GLFWwindow* window;
    std::vector<InputListener*> listeners;
    double cursor_x{}, cursor_y{};

    void handleMouse();
public:
    explicit InputManager(GLFWwindow* window);
    void handleInput();
    void addInputListener(InputListener* listener);
};


#endif //VOXELIO_INPUTMANAGER_H
