#include "Gpio.hpp"
#include <chrono>
#include <exception>
#include <thread>

using std::string;

class hBridge {
public:
    hBridge(string[]);
    ~hBridge(void);
    void setDirection(int);
private:
    GPIOClass* ports[4]; // [0] = directioPort1, [1] = directionPort2, [2] = pwmPort1, [3] = pwmPort2
}