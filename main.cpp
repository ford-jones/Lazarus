#include "main.h"

int main()
{
    window = new WindowManager(800, 600, "Lazarus::Experimental", NULL, NULL);
    window->Initialise();

    delete window;
    return 0;
};
