#pragma once
#include "CButton.h"

class Slider
{
    public:
        Slider(int x, int y, int w, int h, int boundOffset = 20);
        ~Slider();

        void Draw();
        void HandleEvents();
        void Update();

        int GetPercentage();

        void ToggleLock()
        {
            mLocked = !mLocked;
        }

        void LockSlider(bool lock)
        {
            mLocked = lock;
        }

        bool IsLocked()
        {
            return mLocked;
        }

    private:
        Button *mButton;
        SDL_Rect mFillRect;
        SDL_Rect mColRect;
        bool mLocked;
        int mIncrement;
};
