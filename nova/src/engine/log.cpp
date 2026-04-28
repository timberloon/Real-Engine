#include"novapch.h"
#include"log.h"

namespace nova{
    std::shared_ptr<spdlog::logger> log::client_logger;
    std::shared_ptr<spdlog::logger> log::core_logger;

    void log::init(){
        spdlog::set_pattern("%^[%T %e] %n: %v%$");

        client_logger = spdlog::stdout_color_mt("Space");
        client_logger->set_level(spdlog::level::trace);

        core_logger = spdlog::stdout_color_mt("Nova");
        core_logger->set_level(spdlog::level::trace);
    }

    void log::log_to_client(){
        client_logger->info("Welcome to Nova\n");
    }

    void log::log_error(std::string msg){
        client_logger->error(msg.c_str());
    }

    void log::log_error(const char* msg){
        client_logger->error(msg);
    }

    void log::log_message(std::string msg){
        client_logger->info(msg.c_str());
    }

    void log::log_message(const char* msg){
        client_logger->info(msg);
    }
}