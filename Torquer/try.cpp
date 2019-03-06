#include "Gpio.hpp"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::string;
using std::chrono::seconds;
using std::cout;
using std::endl;
using std::flush;

int main() {
	auto gpioConn = GPIOClass("4");
	if (!gpioConn.export_gpio()) {
		// getc(stdin);
		sleep_for(milliseconds(500));
		gpioConn.setdir_gpio("out");
		gpioConn.setval_gpio("1");
		string str = "";
		gpioConn.getval_gpio(str);
		cout << str << endl << flush;
		gpioConn.unexport_gpio();
	} 
	return 0;
}
