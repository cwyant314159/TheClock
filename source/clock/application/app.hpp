#ifndef APP_HPP
#define APP_HPP

#include <memory>
#include <string>

extern "C" {
    #include <raylib.h>
}

#include "application/event_system/event_system.hpp"
#include "clocks/iclock.hpp"
#include "time_sources/isource.hpp"

class App
{
public:
    App();
    App(int width, int height);
    int Loop();

    // This class cannot be moved or copied
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

private:
    bool                     m_appShouldClose;
    std::string              m_clockSettingStr;
    std::string              m_timeSourceSettingStr;
    std::unique_ptr<IClock>  m_pClock;
    std::unique_ptr<ISource> m_ptimeSource;
    EventSystem              m_eventSys;

    void UpdatePhase();
    void DrawPhase();
    bool isClockCompound() const;
    bool isTimeSourceLocal() const;
    Vector2 ComputeTextBounds(const char* text) const;
};

#endif // APP_HPP