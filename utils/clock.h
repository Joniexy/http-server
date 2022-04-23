#ifndef HTTP_SERVER_CLOCK_H
#define HTTP_SERVER_CLOCK_H

#include <chrono>

namespace utils {
    class clock_c {
    public:
        using steady_clock = std::chrono::steady_clock;
        clock_c();
        clock_c(const int& val);
        clock_c(const std::chrono::seconds& val = std::chrono::seconds(0));
        ~clock_c();

        void update_time();
        void update_duration(const std::chrono::seconds& val);

        steady_clock::time_point get_time();
        std::chrono::seconds get_duration();
        std::chrono::seconds get_passed_time();
    private:
        steady_clock::time_point m_time = steady_clock::now();
        std::chrono::seconds m_duration = {};
    };
}

#endif //HTTP_SERVER_CLOCK_H
