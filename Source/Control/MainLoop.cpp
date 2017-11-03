#include <EventProcessing/EventProcessing.hpp>
#include <Infrastructure/Exception.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    try
    {
        EventProcessing::GetInstance()->Init();
    }
    catch (const Exception& e)
    {
        /**
         * TODO: Output problem in message window.
         */
        return -1;
    }

    try
    {
        for (;;)
        {
            EventProcessing::GetInstance()->Process();
            EventProcessing::GetInstance()->Update();

            if (EventProcessing::GetInstance()->IsQuitRequested()) break;
        }
    }
    catch (const Exception& e)
    {
        /**
         * TODO: Output problem in message window.
         */
        return -1;
    }

    EventProcessing::GetInstance()->Quit();
    return 0;
}
