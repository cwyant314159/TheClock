#include <memory>
#include <typeinfo>

extern "C" {
    #include <raygui.h>
    #include <raylib.h>
}

#include "clocks/compound_clock.hpp"
#include "clocks/simple_clock.hpp"
#include "time_sources/local_time_source.hpp"
#include "utils/time_point.hpp"
#include "widgets/dial_change_event.hpp"
#include "widgets/event_system.hpp"

int main(void)
{
    // TODO configuration singleton
    // TODO make button class for easier placement and call back registration
    // TODO make control bar class
    const int width  = 1280;
    const int height = 720;

    SetTargetFPS(60);
    InitWindow(width, height, "Clock Application");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

    const Vector2 center{
        .x = width / 2.0f,
        .y = height / 2.0f
    };

    const float radius = (height / 2.0f) * 0.9f;

    EventSystem eventSys;
    std::unique_ptr<IClock> pClock   = std::make_unique<CompoundClock>(center, radius);
    std::unique_ptr<ISource> pSource = std::make_unique<LocalTimeSource>();

    eventSys.Subscribe<DialChangeEvent>([&pClock, &center, &radius](const DialChangeEvent&) {
        if (typeid(*pClock) == typeid(CompoundClock)) {
            TraceLog(LOG_INFO, "Changing to SimpleClock");
            pClock = std::make_unique<SimpleClock>(center, radius);
        } else {
            TraceLog(LOG_INFO, "Changing to CompoundClock");
            pClock = std::make_unique<CompoundClock>(center, radius);
        }
    });


    const char * const buttonText = "Toggle Dial";

    Font guiFont = GetFontDefault();
    const int textSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    const int spacing  = GuiGetStyle(DEFAULT, TEXT_SPACING);
    const Vector2 textBounds = MeasureTextEx(guiFont, buttonText, textSize, spacing);
    const float padding = 5.0f + GuiGetStyle(BUTTON, TEXT_PADDING) + GuiGetStyle(BUTTON, BORDER_WIDTH);

    Rectangle button{
        .x{width - padding - padding - textBounds.x - 100},
        .y{padding},
        .width{padding * 2 + textBounds.x},
        .height{padding * 2 + textBounds.y}
    };

    while (!WindowShouldClose())
    {
        eventSys.Dispatch();

        const auto now = pSource->Now();
        pClock->Update(now);

        BeginDrawing();
            ClearBackground(BLACK);
            pClock->Draw();

            // Toggle the clock type.
            if (GuiButton(button, buttonText)) {
                eventSys.Enqueue(DialChangeEvent{});
            }

            DrawFPS(5, 5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}