#ifndef APP_EVENT_HPP
#define APP_EVENT_HPP

#include <variant>

#include "application/event_system/events/dial_change_event.hpp"
#include "application/event_system/events/quit_event.hpp"
#include "application/event_system/events/time_source_change_event.hpp"

using AppEvent = std::variant<
    std::monostate,
    DialChangeEvent,
    QuitEvent,
    TimeSourceChangeEvent
>;

#endif // APP_EVENT_HPP