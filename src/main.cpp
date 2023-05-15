#include <SFML/Graphics.hpp>
#include "Engine.hpp"
#include "Global.hpp"
#include "InputManager.hpp"
#include "LogManager.hpp"
#include "MouseWheel.hpp"
#include "OsManager.hpp"
#include "PathManager.hpp"
#include "ScreenCapturer.hpp"
#include "Setting.hpp"
#include "SoundManager.hpp"
#include "Window.hpp"
#include <iostream>
#include <istream>

class A
{
public:
    int value()
    {
        return 1;
    }
    int value() const
    {
        return 2;
    }
};

int main(int /*argc*/, char** argv, char** /*options*/)
{
    const A* a = new A();
    int val = a->value();
    std::cout << "val = " << val << std::endl;
    Window::create();
    OsManager::initiateCoreFile();
    PathManager::setPath(argv[0]);
    PathManager::initialize();
    LogManager::clean();
    Setting::initialize();
    Window::getMonitorSize();
    Window::initialize();
    SoundManager::initialize();
    MouseWheel::initialize();
    ScreenCapturer::initialize();
    Input::initialize();
    InputManager::initialize();
    Engine::launch();
    ScreenCapturer::terminate();
    SoundManager::terminate();
    Window::terminate();
    Setting::write();
    return 0;
}
