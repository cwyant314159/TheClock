#include <memory>

extern "C" {
    #include <raylib.h>
}

#include "clocks/compound_clock.hpp"
#include "time_sources/local_time_source.hpp"
#include "utils/time_point.hpp"

int main(void)
{
    const int width  = 1280;
    const int height = 720;

    const Vector2 center{
        .x = width / 2.0f,
        .y = height / 2.0f
    };

    const float radius = (height / 2.0f) * 0.9f;

    std::unique_ptr<IClock> pClock   = std::make_unique<CompoundClock>(center, radius);
    std::unique_ptr<ISource> pSource = std::make_unique<LocalTimeSource>();

    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "Clock Application");

    while (!WindowShouldClose())
    {
        const auto now = pSource->Now();
        pClock->Update(now);

        BeginDrawing();
            ClearBackground(BLACK);
            pClock->Draw();
            DrawFPS(5, 5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}