#include <chrono>
#include <optional>

extern "C" {
    #include <raylib.h>
}

#include "clocks/compound_clock.hpp"
#include "utils/time_point.hpp"

static Utils::TimePoint GetCurrentTime()
{
    using namespace std::chrono;

    const time_zone* tz = std::chrono::current_zone();

    // Lambda to compute the time duration in milliseconds since midnight
    const auto TimeSinceMidnight = [](auto timePoint) -> auto {
        const auto midnight = floor<days>(timePoint);
        return duration_cast<milliseconds>(timePoint - midnight);
    };

    // Get the current system time point (UTC)
    const auto now_sys = system_clock::now();

    // Compute the local time using the timezone
    const auto localTime = zoned_time{tz, now_sys}.get_local_time();

    // Compute time components as a duration since midnight
    const auto timeComponents = hh_mm_ss{ TimeSinceMidnight(localTime) };

    return Utils::TimePoint{
        timeComponents.hours().count(),
        timeComponents.minutes().count(),
        timeComponents.seconds().count(),
        timeComponents.subseconds().count()
    };
}

int main(void)
{
    const int width  = 1280;
    const int height = 720;

    const Vector2 center{
        .x = width / 2.0f,
        .y = height / 2.0f
    };

    const float radius = (height / 2.0f) * 0.9f;

    CompoundClock cc{ center, radius };

    

    SetTargetFPS(60);
    InitWindow(width, height, "Clock Application");

    while (!WindowShouldClose())
    {
        const auto now = GetCurrentTime();
        cc.Update(now);

        BeginDrawing();
            ClearBackground(BLACK);
            cc.Draw();
            DrawFPS(5, 5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}