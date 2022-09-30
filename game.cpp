#include "game.hpp"

std::vector<void (*)()> tickCalls = {}; // order is first -> last

void (*starter)() = start; // start func

void(* inputer)() = inputLoop; // input func

void(* ender)() = gameover; // game end func

void start()
{
    // set stuff up, display loading animations, etc
    output.Display("Output text file for TANIM. TANIM (Text Animation) is a library that allows you to make classes that represent animations. These can then be run easily.");
    end = true; // not doing anything, so just end it.
}

void gameover()
{
    // clean up vars and display game over screens.
}