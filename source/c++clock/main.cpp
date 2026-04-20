#include <chrono>
#include <optional>

extern "C" {
    #include <raylib.h>
}

#include "Clock.hpp"

static std::chrono::hh_mm_ss<std::chrono::seconds> GetCurrentTime(std::optional<const std::chrono::time_zone*> timeZone = std::nullopt)
{
    using namespace std::chrono;
    
    // Lambda to compute the time duration in seconds since midnight
    const auto TimeSinceMidnight = [](auto timePoint) -> auto {
        const auto midnight = floor<days>(timePoint);
        return duration_cast<seconds>(timePoint - midnight);
    };

    // Get the current system time point (UTC)
    const auto now_sys = system_clock::now();

    // Compute the local time if a timezone is provided and not null
    if (nullptr != timeZone.value_or(nullptr)) {
        const auto localTime = zoned_time{timeZone.value(), now_sys}.get_local_time();
        return hh_mm_ss{ TimeSinceMidnight(localTime) };
    }

    // Compute the UTC time if the timezone is not provided
    return hh_mm_ss{ TimeSinceMidnight(now_sys) };
}

int main(void)
{
    const int width  = 1280;
    const int height = 720;

    Clock clock{
        Vector2{ .x = width / 2.0f, .y = height / 2.0f },
        (height / 2.0f) * 0.9f
    };

    const std::chrono::time_zone* tz = std::chrono::current_zone();

    SetTargetFPS(60);
    InitWindow(width, height, "Clock Application");

    while (!WindowShouldClose())
    {
        const auto now = GetCurrentTime(tz);
        clock.Update(now);

        BeginDrawing();
            ClearBackground(BLACK);
            clock.Draw();
            DrawFPS(5, 5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}