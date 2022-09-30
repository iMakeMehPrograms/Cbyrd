#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <fstream>

/// The ticks per second. Default is 10
#define TICKRATE 10

/// The amount of ticks until the game stops. Will be replaced on the next update. (at a TICKRATE of 10 ticks per second, this means it will timeout at 1 hour.)
#define TIMEOUT 36000

/// The functions that will run every tick. These will be your render, physics, and math functions. The function at index 0 runs first, then 1, etc...
extern std::vector<void (*)()> tickCalls;

/// Starting func. Runs before the first tickCall and before the input thread starts. You may want to have the input thread start before this.
extern void (*starter)();

/// Input function. Use it to set variables when given input, but don't use it to render or do logic.
extern void (* inputer)();

/// Ender function. Runs when end = true.
extern void (* ender)();

/// Debug ofstream. 
extern std::ofstream debugout;

/// Set to true to softly close the script (calls the ender func)
extern bool end;

/// Log data to the output file (usually named debug.txt)
template <typename T> extern void log(T data);

/// Getter func for the current tick so that there are no accidental settings of the tick count.
int getTick();

/// WARING - Don't use this unless there is a BAD, BAD issue such as a null pointer.
inline void hardQuit(int errCode)
{
    log("Hard quitting...\n");
    exit(errCode);
    
}

/// Don't worry about it, it just turns the tickrate into the time beetween ticks.
inline constexpr int tickrateToTicktime() {
    return (int)1000 / TICKRATE;
}