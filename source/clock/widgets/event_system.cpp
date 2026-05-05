#include "widgets/event_system.hpp"

void EventSystem::Enqueue(AppEvent event)
{
    m_queue.push_back(std::move(event));
}

void EventSystem::Dispatch()
{
    if (m_queue.empty()) return;

    for (const AppEvent& event : m_queue) {
        const std::size_t idx = event.index();
        if (m_subscribers.contains(idx)) {
            for (auto& handler : m_subscribers[idx]) {
                handler(event);
            }
        }
    }

    m_queue.clear();
}