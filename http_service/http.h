#ifndef HTTP_SERVER_HTTP_H
#define HTTP_SERVER_HTTP_H
#include <sandbird/sandbird.h>
#include <fmt/color.h>
#include <fmt/chrono.h>
#include <utils/clock.h>

#include <atomic>
#include <chrono>
#include <unordered_map>

class http_server {
public:
    http_server(const char* host, const char* port) {
        memset(&m_option, 0, sizeof(m_option));
        m_option.host = host;
        m_option.port = port;
        m_option.handler = http_server::handler;

        m_server = sb_new_server(&m_option);
        if (!m_server) {
            fmt::print(stderr, "failed to initialize http server due unavailable port\n");
            exit(EXIT_FAILURE);
        }
        fmt::print("http-service listening to {}:{}\n |-> server ptr: {}\n |-> start time: {}\n",
                   m_option.host, m_option.port, fmt::ptr(m_server), std::chrono::system_clock::now());
    }
    ~http_server() {
        sb_close_server(this->m_server);
        fmt::print("destroyed server handler process.\n");
    }

    void run() {
        while(this->m_running.load()){
            sb_poll_server(this->m_server, 1000);
        }
    }
    static int handler(sb_Event* event) {
        switch(event->type) {
            case SB_EV_CONNECT: {
                auto it = m_connections.find((event->address));
                if (it == m_connections.end())
                    m_connections.insert({event->address, utils::clock_c(5)});
                break;
            }
            case SB_EV_CLOSE: {
                break;
            }
            case SB_EV_REQUEST:{
                auto it = m_connections.find((event->address));
                if(it == m_connections.end())
                    return SB_RES_CLOSE;

                if(strcmp(event->path, "/growtopia/server_data.php") == 0 && strcmp(event->method, "POST") == 0) {
                    sb_send_status(event->stream, 200, "OK");
                    sb_send_header(event->stream, "Content-Type", "text/html");
                    sb_writef(event->stream, m_data->c_str());
                }
                else {
                    if (it->second.get_passed_time() < it->second.get_duration())
                        return SB_RES_CLOSE;
                }
                it->second.update_time();
                return SB_RES_OK;
            }
            default:
                break;
        }
        /*
         *
                    if(it->second.get_passed_time() > it->second.get_duration()) {
                        it->second.update_time();
                        return SB_RES_OK;
                    }
                    return SB_RES_CLOSE;
         *
         */
        return 0;
    }
private:
    sb_Options m_option;
    sb_Server* m_server;
public:
    std::atomic<bool> m_running;

    static std::string* m_data;
    static std::unordered_map<const char*,  utils::clock_c> m_connections;
};

#endif //HTTP_SERVER_HTTP_H
