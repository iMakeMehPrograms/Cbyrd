#include "game.hpp"

Screen output("output.txt"); // TANIM output

//char an = '';
std::string ans = "";

void inputLoop() {

    while(!end) {

        //ans = getchar(); // for char inputs
        std::cin >> ans; // for string inputs
        
        //set variables from input here
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(TICKRATE * 2)); // give ticker time to end first (two frames if the ticker is caught at a bad time)
}
