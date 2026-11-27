#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace easy_triggers {

enum class WorkflowMode {
    Automatic,
    StepByStep,
    Hybrid
};

enum class TriggerType {
    Move,
    Rotate,
    Scale,
    Fade,
    Toggle,
    Wait
};

struct TriggerStep {
    TriggerType type = TriggerType::Move;
    float duration = 0.0f;
    std::string target;
};

class TriggerSequence {
public:
    explicit TriggerSequence(WorkflowMode mode = WorkflowMode::Hybrid);

    WorkflowMode mode() const noexcept;
    void setMode(WorkflowMode mode) noexcept;

    const std::vector<TriggerStep>& steps() const noexcept;
    void add(TriggerStep step);
    bool remove(std::size_t index);
    bool move(std::size_t from, std::size_t to);
    bool validate() const noexcept;

private:
    WorkflowMode m_mode;
    std::vector<TriggerStep> m_steps;
};

} // namespace easy_triggers
