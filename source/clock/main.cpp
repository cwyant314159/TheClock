#include "application/app.hpp"

int main(void)
{
    const int width  = 1280;
    const int height = 720;

    App clockApp{width, height};
    return clockApp.Loop();
}