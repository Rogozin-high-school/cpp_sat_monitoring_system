#include <iostream>
#include "mgm.hpp"
#include <chrono>
#include <thread>
#include <signal.h>
#include <fstream>

using std::ofstream;
using std::cout;
using std::endl;
using std::cin;
using std::chrono::milliseconds;
using std::this_thread::sleep_for;

void do_shit(int s);
void printWTF();

int main(void) {
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = do_shit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    ofstream file = ofstream("log.csv");

    Magnetometer mgm = Magnetometer();
    if (!mgm.ok) return 1;
    // mgm.calibrateMagnetometer();
    float mx,
        my,
        mz;
    printf("reading\n");
    int thing = 0;
    while (true) {
        sleep_for(milliseconds(10));
        mgm.GetMagnetValues(mx, my, mz);
        file << mx << "," << my << "," << mz << "\n";
	    thing +=1;
        if(thing == 1920)
        {
            break;
        }
    }
    return 0;
}

void do_shit(int s) {
    printWTF();
    exit(1);
}

void printWTF() {
    printf("hi\n");
}
