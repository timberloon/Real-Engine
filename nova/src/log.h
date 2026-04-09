#pragma once

#include"core.h"
#include<spdlog/spdlog.h>
#include<spdlog/sinks/sink-inl.h>
#include<memory>

namespace nova{

    class NOVA_API log{
    private:
        static std::shared_ptr<spdlog::logger> client_logger;
        static std::shared_ptr<spdlog::logger> core_logger;

    public:
        static void init();
        static std::shared_ptr<spdlog::logger> get_client_logger(){ return client_logger;};
        static std::shared_ptr<spdlog::logger> get_app_logger(){ return core_logger;};
        static void log_to_client();
        static void log_error(std::string msg);
        static void log_error(const char* msg);
    };
}