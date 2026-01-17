#pragma once

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include"core.h"

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
    };
}