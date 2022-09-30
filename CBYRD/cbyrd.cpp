#include "cbyrd.hpp"

bool end = false;

/// The time beetween each tick
constexpr int TICKTIME = tickrateToTicktime();

/// The amount of ticks done.
int tickcount = 0;

std::ofstream debugout("debug.txt", std::ofstream::out | std::ofstream:: trunc); // debug file for logging

void ticker(std::vector<void (*)()> funcs) {
    for (int e = 0; e < (int)funcs.size(); e++) { // check for null pointers
        if(funcs[e] == nullptr) {
            log("Null pointer in the tickCalls (locally called funcs) array!\n");
            std::cerr << "\a Null pointer in the tickCalls (locally called funcs) array!\n";
            hardQuit(1);
            return;
        }
    }

    tickcount = 0; // reset to 0

    while(!end && tickcount < TIMEOUT) { // while not timed out or ending
        if ((tickcount % 3000) == 0 && tickcount != 0) {
            log("5 minutes have passed, # of minutes: "); // do occasional log 
            log(tickcount / 600);
            log("\n");
        }

        for (int i = 0; i < (int)funcs.size(); i++) { // runs the funcs
            funcs[i]();
        }

        //std::cout << "Tick\n"; // no 
        std::this_thread::sleep_for(std::chrono::milliseconds(TICKTIME)); // wait
        tickcount++; // increase tick count
    }

    if (not end) {
        end = true;
    }
}

int getTick()
{ // use instead of direct acess so timeout check doesn't get fcked up
    return tickcount;
}

template <typename T> void log(T data) {

    if(debugout.is_open()) {

        debugout << data << std::flush; // good

    } else {

        debugout.open("debug.txt", std::ofstream::out | std::ofstream::trunc); // open again

        if(debugout.is_open()) { // yay

            debugout << "Successfully reopened debugout\n" << std::flush;
            debugout << data << std::flush;

        } else {

            std::cerr << "\a Debug file not opening on log function!"; // err
            return;

        }

    }

}

int main()
{

    if(starter == nullptr) { // nullptr checks
        std::cerr << "\a Starter is a nullptr!\n";
        log("Starter is a nullptr!\n");
        return 1;
    }
    if(inputer == nullptr)
    {
        std::cerr << "\aInputer is a nullptr!\n";
        log("Inputer is a nullptr!\n");
        return 1;
    }

    if(ender == nullptr) {
        std::cerr << "\a Ender is a nullptr\n";
        log("Ender is a nullptr!\n");
        return 1;
    }

    log("Test log to open file.\n"); // read these logs, they explain a lot of these lines

    log("Running starter func...");

    starter();

    log("Starter func ran, starting tickthread.\n");

    std::thread tickthread(ticker, tickCalls);

    log("Tickthread init, waiting for join, will occur in ~1 hour if not ended.\n");

    std::thread iothread(inputer);

    log("Iothread init, waiting for join, will occur after tickthread joins.\n");

    tickthread.join();

    log("Tickthread joined.\n");

    iothread.join();

    log("Iothread joined.\n");

    log("Running ender function...\n");

    ender();

    log("Ender function done, closing program.");

    return 0;
}