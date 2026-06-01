#pragma once
#include"core.h"

namespace nova{
    struct NOVA_API vec2{
        float x,y;

        vec2(int a,int b) : x(a), y(b) {}
        vec2(){}

        vec2 operator+(vec2& other){
            vec2 temp;
            temp.x = this->x + other.x;
            temp.y = this->y + other.y;

            return temp;
        }

        vec2 operator-(vec2& other){
            vec2 temp;
            temp.x = this->x - other.x;
            temp.y = this->y - other.y;

            return temp;
        }
    };
}

