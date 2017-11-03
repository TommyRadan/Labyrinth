#include <EventProcessing/EventProcessing.hpp>

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;

    EventProcessing::GetInstance()->Init();

    for (;;)
    {
        EventProcessing::GetInstance()->Process();
        EventProcessing::GetInstance()->Update();

        if (EventProcessing::GetInstance()->IsQuitRequested()) break;
    }

    EventProcessing::GetInstance()->Quit();
    return 0;
}
