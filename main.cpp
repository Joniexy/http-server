#include <atomic>
#include <fmt/core.h>
#include "http_service/http.h"

http_server* g_server;
std::string* http_server::m_data = new std::string {
        "server|127.0.0.1\n"
        "port|17091\n"
        "type|1\n"
        "#maint|Server is under maintenance. We will be back online shortly. Thank you for your patience!"
        "meta|localhost\n"
        "RTENDMARKERBS1001"
};
std::unordered_map<const char*,  utils::clock_c> http_server::m_connections{};

int main() {
    g_server = new http_server("0.0.0.0", "80");
    g_server->m_running.store(true);
    g_server->run();
}
