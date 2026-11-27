#include "TriggerSequence.hpp"

#include <cmath>
#include <utility>

namespace easy_triggers {

TriggerSequence::TriggerSequence(WorkflowMode mode) : m_mode(mode) {}

WorkflowMode TriggerSequence::mode() const noexcept {
    return m_mode;
}

void TriggerSequence::setMode(WorkflowMode mode) noexcept {
    m_mode = mode;
}

const std::vector<TriggerStep>& TriggerSequence::steps() const noexcept {
    return m_steps;
}

void TriggerSequence::add(TriggerStep step) {
    m_steps.push_back(std::move(step));
}

bool TriggerSequence::remove(std::size_t index) {
    if (index >= m_steps.size()) return false;
    m_steps.erase(m_steps.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

bool TriggerSequence::move(std::size_t from, std::size_t to) {
    if (from >= m_steps.size() || to >= m_steps.size()) return false;
    if (from == to) return true;
    auto step = std::move(m_steps[from]);
    m_steps.erase(m_steps.begin() + static_cast<std::ptrdiff_t>(from));
    m_steps.insert(m_steps.begin() + static_cast<std::ptrdiff_t>(to), std::move(step));
    return true;
}

bool TriggerSequence::validate() const noexcept {
    for (const auto& step : m_steps) {
        if (!std::isfinite(step.duration) || step.duration < 0.0f) return false;
    }
    return true;
}

} // namespace easy_triggers
