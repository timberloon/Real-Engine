#pragma once
#include<sstream>
#include"core.h"

namespace nova{
    struct NOVA_API vec2{
        float a,b;

        vec2(float x,float y) : a(x), b(y) {}
        vec2(){}

        vec2 operator+(const vec2& other){
            return {
                    this->a+other.a,
                    this->b+other.b
                };
        }
        vec2 operator-(const vec2& other){
            return {
                    this->a-other.a,
                    this->b-other.b
                };
        }
    };

    struct NOVA_API vec3{
        float a,b,c;

        vec3(float x,float y,float z) : a(x), b(y), c(z) {}
        vec3(){}

        vec3 operator+(const vec3& other){
            return {
                    this->a+other.a,
                    this->b+other.b,
                    this->c+other.c
                };
        }
        vec3 operator-(const vec3& other){
            return {
                    this->a-other.a,
                    this->b-other.b,
                    this->c-other.c
                };
        }
    };

    struct NOVA_API vec4{
        float a,b,c,d;

        vec4(float p,float q,float r,float s) : a(p), b(q), c(r), d(s) {}
        vec4(){}

        vec4 operator+(const vec4& other){
            return {
                this->a+other.a,
                this->b+other.b,
                this->c+other.c,
                this->d+other.d
            };
        }
        vec4 operator-(const vec4& other){
            return {
                this->a-other.a,
                this->b-other.b,
                this->c-other.c,
                this->d-other.d
            };
        }

        std::string toString(){
            std::stringstream ss;
            ss << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            return ss.str();
        }
    };
}
