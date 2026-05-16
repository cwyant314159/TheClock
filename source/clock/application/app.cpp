#include "application/app.hpp"

#include <string_view>

#include "clocks/compound_clock.hpp"
#include "clocks/simple_clock.hpp"
#include "time_sources/local_time_source.hpp"
#include "time_sources/utc_time_source.hpp"
#include "utils/time_point.hpp"

extern "C" {
    #include <raygui.h>
}

namespace
{
    constexpr int DEFAULT_WIDTH{600};
    constexpr int DEFAULT_HEIGHT{800};
    constexpr int FONT_SIZE{20};
    constexpr const char* APP_NAME{"Clock Application"};

    using DefaultClockType = CompoundClock;
    using DefaultTimeSrcType = LocalTimeSource;
}

App::App()
    : App(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

App::App(int width, int height)
    : m_appShouldClose{false}
    , m_clockSettingStr{"Unset"}
    , m_timeSourceSettingStr{"Unset"}
    , m_pClock{nullptr}
    , m_ptimeSource{nullptr}
    , m_eventSys{}
{
    SetTargetFPS(60);
    InitWindow(width, height, APP_NAME);
    GuiSetStyle(DEFAULT, TEXT_SIZE, FONT_SIZE);

    const Vector2 screenCenter{
        .x = width  / 2.0f,
        .y = height / 2.0f
    };

    const float clockRadius = (height / 2.0f) * 0.9f;

    m_pClock = std::make_unique<DefaultClockType>(screenCenter, clockRadius);
    m_ptimeSource = std::make_unique<DefaultTimeSrcType>();

    // Subscribe to events
    m_eventSys.Subscribe<DialChangeEvent>(
    [this, screenCenter, clockRadius] (const DialChangeEvent&) {
        if (isClockCompound()) {
            TraceLog(LOG_INFO, "Changing to SimpleClock");
            m_pClock = std::make_unique<SimpleClock>(screenCenter, clockRadius);
        } else {
            TraceLog(LOG_INFO, "Changing to CompoundClock");
            m_pClock = std::make_unique<CompoundClock>(screenCenter, clockRadius);
        }
    });

    m_eventSys.Subscribe<TimeSourceChangeEvent>(
    [this] (const TimeSourceChangeEvent&) {
        if (isTimeSourceLocal()) {
            TraceLog(LOG_INFO, "Changing to UTC Time Source");
            m_ptimeSource = std::make_unique<UtcTimeSource>();
        } else {
            TraceLog(LOG_INFO, "Changing to Local Timezone Time Source");
            m_ptimeSource = std::make_unique<LocalTimeSource>();
        }
    });

    m_eventSys.Subscribe<QuitEvent>(
    [this] (const QuitEvent&) {
        TraceLog(LOG_INFO, "--->>> Quitting application <<<---");
        m_appShouldClose = true;
    });
}

int App::Loop()
{
    while (!WindowShouldClose() && !m_appShouldClose) {
        UpdatePhase();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawPhase();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void App::UpdatePhase()
{
    // Drain events
    m_eventSys.Dispatch();

    // Update clock face
    const auto now = m_ptimeSource->Now();
    m_pClock->Update(now);

    // Update the settings label text
    m_clockSettingStr = "Clock Dial: ";
    m_clockSettingStr += (isClockCompound()) ? "Compound" : "Simple";
    
    m_timeSourceSettingStr = "Time Source: ";
    m_timeSourceSettingStr += (isTimeSourceLocal()) ? "Local Time" : "UTC";
}

void App::DrawPhase()
{
    m_pClock->Draw();
    
    // Draw text labels
    const Vector2 labelAnchor{.x = 5, .y = 5};

    DrawFPS(labelAnchor.x, labelAnchor.y);
    DrawText(m_clockSettingStr.data(), labelAnchor.x, labelAnchor.y + FONT_SIZE, FONT_SIZE, LIME);
    DrawText(m_timeSourceSettingStr.data(), labelAnchor.x, labelAnchor.y + (2*FONT_SIZE), FONT_SIZE, LIME);

    // Add a 5px padding to all the other padding in the GUI style
    const float padding = 5.0f + GuiGetStyle(BUTTON, TEXT_PADDING) + GuiGetStyle(BUTTON, BORDER_WIDTH);

    // The buttons are sized to fit the longest button text. It would be better
    // if this is handled more intelligently, but with the limited amount of
    // buttons supported, this should be okay.
    const char * const longestButtonText = "Toggle Source";
    const Vector2 textBounds = ComputeTextBounds(longestButtonText);
    
    Rectangle button{
        .x = GetScreenWidth() - ((2 * padding) + textBounds.x + 100),
        .y = padding,
        .width = (2 * padding) + textBounds.x,
        .height = (2 * padding) + textBounds.y
    };
    
    if (GuiButton(button, "Toggle Dial")) {
        m_eventSys.Enqueue(AppEvent{DialChangeEvent{}});
    }

    button.y += button.height + padding;
    if (GuiButton(button, "Toggle Source")) {
        m_eventSys.Enqueue(AppEvent{TimeSourceChangeEvent{}});
    }

    button.y += button.height + padding;
    if (GuiButton(button, "Quit")) {
        m_eventSys.Enqueue(AppEvent{QuitEvent{}});
    }
}

bool App::isClockCompound() const
{
    return dynamic_cast<CompoundClock*>(m_pClock.get()) != nullptr;
}

bool App::isTimeSourceLocal() const
{
    return dynamic_cast<LocalTimeSource*>(m_ptimeSource.get()) != nullptr;
}

Vector2 App::ComputeTextBounds(const char* text) const
{
    Font guiFont = GetFontDefault();
    const int textSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
    const int spacing  = GuiGetStyle(DEFAULT, TEXT_SPACING);
    return MeasureTextEx(guiFont, text, textSize, spacing);
}