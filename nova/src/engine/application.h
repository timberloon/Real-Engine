#pragma once
#include"core.h"
#include"../event/event.h"

namespace nova{
    class NOVA_API application{
    public:
        application(){}
        virtual ~application() = default;

        void run();
    };
}