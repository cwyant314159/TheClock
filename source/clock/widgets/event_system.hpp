#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include <cstdint>
#include <functional>
#include <map>
#include <vector>

#include "widgets/app_event.hpp"

class EventSystem
{
public:
    void Enqueue(AppEvent event);
    void Dispatch();

    template <class T>
    void Subscribe(std::function<void(const T&)> handler)
    {
        const std::size_t idx = index_of<T, AppEvent>;
        m_subscribers[idx].push_back(
            [handler](const AppEvent& event) -> void {
                handler(std::get<T>(event));
            }
        );
    }

private:
    std::vector<AppEvent> m_queue;
    std::map<
        std::size_t, std::vector<std::function<void(const AppEvent&)>>
    > m_subscribers;

    // A helper to get the index of a type within a variant at compile time
    template<typename T, typename Variant>
    static constexpr std::size_t index_of = []() {
        return []<std::size_t... I>(std::index_sequence<I...>) {
            std::size_t found = 0;
            ((std::is_same_v<T, std::variant_alternative_t<I, Variant>> ? found = I : 0), ...);
            return found;
        }(std::make_index_sequence<std::variant_size_v<Variant>>{});
    }();
};

#endif // EVENT_SYSTEM_HPP