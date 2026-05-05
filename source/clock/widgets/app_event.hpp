#ifndef APP_EVENT_HPP
#define APP_EVENT_HPP

#include <variant>

#include "widgets/dial_change_event.hpp"

using AppEvent = std::variant<
    std::monostate,
    DialChangeEvent
>;

#endif // APP_EVENT_HPP