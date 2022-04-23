#include "clock.h"

namespace utils {
    clock_c::clock_c() :
            m_time(steady_clock::now()), m_duration(std::chrono::seconds(0)) {}

    clock_c::clock_c(const int &val) :
            m_time(steady_clock::now()), m_duration(std::chrono::seconds(val)) {}

    clock_c::clock_c(const std::chrono::seconds &val) :
            m_time(steady_clock::now()), m_duration(val) {}

    clock_c::~clock_c() {}

    void clock_c::update_time() {
        m_time = steady_clock::now();
    }

    void clock_c::update_duration(const std::chrono::seconds &val) {
        m_duration = val;
    }

    clock_c::steady_clock::time_point clock_c::get_time() {
        return m_time;
    }

    std::chrono::seconds clock_c::get_duration() {
        return m_duration;
    }

    std::chrono::seconds clock_c::get_passed_time() {
        return std::chrono::duration_cast<std::chrono::seconds>(steady_clock::now() - m_time);
    }
}
