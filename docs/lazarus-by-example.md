# Lazarus by Example:

## Window creation:
```cpp
#include <lazarus.h>

int main()
{
    Lazarus::WindowManager window = Lazarus::WindowManager(800, 600, "Game Window", nullptr, nullptr);
    window.initialise();

    return 0;
}
```
