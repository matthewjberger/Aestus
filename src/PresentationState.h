#pragma once

#include "CoreGame.h"
#include "LEDPanel.h"

class PresentationState : public GameState
{
    public:
        void Init();
        void Finalize();

        void Pause();
        void Resume();

        void Draw();
        void HandleEvents();
        void Update();

        static PresentationState *GetInstance()
        {
            if (inst == 0)
            {
                inst = new PresentationState();
            }

            return inst;
        }

    private:

        static PresentationState *inst;

        /**************************/
        /* Place State Items here */
        /**************************/

        LEDPanel *ledPanel;

        /**************************/
};


