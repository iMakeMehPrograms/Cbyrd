#include "canim.hpp"

Animation::Animation(std::vector<std::string> anim, std::chrono::milliseconds tbf, Screen dscreen) // constructor
    : frames{anim}
    , timeBeetweenFrames{tbf}
    , defaultScreen{dscreen.name}
{}

    void Animation::Play() // play no args
    {
        dlay(1, frames, timeBeetweenFrames, defaultScreen);
    }
    void Animation::Play(int repeatTimes) /// play con repeat
    {
        dlay(repeatTimes, frames, timeBeetweenFrames, defaultScreen);
    }
    void Animation::Play(Screen scr) // play different screen
    {
        dlay(1, frames, timeBeetweenFrames, scr);
    }

    void Animation::Play(int repeatTimes, Screen scr) //play con repeat y different screen
    {
        dlay(repeatTimes, frames, timeBeetweenFrames, scr);
    }

    void Animation::dlay(int repeatTimes, std::vector<std::string> frames, std::chrono::milliseconds tbf, Screen ahh)
    {
        int frameIndex = 0;
        int repeat = 0;
        while (repeat < repeatTimes)
        {
            while (frameIndex != (int)frames.size())
            {
                ahh.Display(frames[frameIndex++]);
                std::this_thread::sleep_for(tbf);
            }
            frameIndex = 0;
            repeat++;
        }
    }