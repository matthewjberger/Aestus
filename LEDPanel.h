#pragma once

#include "CButton.h"
#include <string>
#include <vector>

const int NUM_LEDS   = 18;
const int NUM_COLORS = 3;
const int NUM_TYPES  = 3;

using namespace std;

class LEDPanel
{
    public:
        LEDPanel();
        ~LEDPanel();

        void Draw(int x = 0, int y = 0);
        void Update();
        void HandleEvents();

    private:

        Button *mButtons[NUM_LEDS];
        int mMargin;
        int mGap;

};
