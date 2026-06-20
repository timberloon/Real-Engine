#pragma once
#include"core.h"
#include"vector.h"

namespace nova{
    struct NOVA_API mat2{
        float m[2][2];

        mat2(float a,float b,float c,float d){
            this->m[0][0] = a;
            this->m[0][1] = b;
            this->m[1][0] = c;
            this->m[1][1] = d;
        }
        mat2(){}

        vec2 operator*(const vec2& vec){
            return {
                this->m[0][0]*vec.a + vec.b*this->m[0][1],
                this->m[1][0]*vec.a + vec.b*this->m[1][1],
            };
        }
    
        float* operator[](const int& i){
            return m[i];
        }
        const float* operator[](const int& i)const{
            return m[i];
        }
    };

    struct NOVA_API mat3{
        float m[3][3];

        mat3(){}
        mat3(float a,float b,float c,float d,float e,float f,float g,float h,float i){
            m[0][0] = a;m[0][1] = b;m[0][2] = c;
            m[1][0] = d;m[1][1] = e;m[1][2] = f;
            m[2][0] = g;m[2][1] = h;m[2][2] = i;
        }

        mat3 operator*(const mat3& other){
            nova::mat3 result(
               m[0][0]*other.m[0][0] + m[0][1]*other.m[1][0] + m[0][2]*other.m[2][0], 
               m[0][0]*other.m[0][1] + m[0][1]*other.m[1][1] + m[0][2]*other.m[2][1], 
               m[0][0]*other.m[0][2] + m[0][1]*other.m[1][2] + m[0][2]*other.m[2][2], 
               m[1][0]*other.m[0][0] + m[1][1]*other.m[1][0] + m[1][2]*other.m[2][0], 
               m[1][0]*other.m[0][1] + m[1][1]*other.m[1][1] + m[1][2]*other.m[2][1], 
               m[1][0]*other.m[0][2] + m[1][1]*other.m[1][2] + m[1][2]*other.m[2][2], 
               m[2][0]*other.m[0][0] + m[2][1]*other.m[1][0] + m[2][2]*other.m[2][0], 
               m[2][0]*other.m[0][1] + m[2][1]*other.m[1][1] + m[2][2]*other.m[2][1], 
               m[2][0]*other.m[0][2] + m[2][1]*other.m[1][2] + m[2][2]*other.m[2][2]
           );

            return result;
        }

        vec3 operator*(const vec3& vec){
            return {
                vec.a * this->m[0][0] + vec.b * this->m[0][1] + vec.c * this->m[0][2],
                vec.a * this->m[1][0] + vec.b * this->m[1][1] + vec.c * this->m[1][2],
                vec.a * this->m[2][0] + vec.b * this->m[2][1] + vec.c * this->m[2][2],
            };
        }

        float* operator[](const int& i){
            return m[i];
        }
        const float* operator[](const int& i)const{
            return m[i];
        }
    };

    struct NOVA_API mat4{
        float m[4][4];

        vec4 operator*(const vec4& vec){
            return {
                vec.a * this->m[0][0] + vec.b * this->m[0][1] + vec.c * this->m[0][2] + vec.d * this->m[0][3],
                vec.a * this->m[1][0] + vec.b * this->m[1][1] + vec.c * this->m[1][2] + vec.d * this->m[1][3],
                vec.a * this->m[2][0] + vec.b * this->m[2][1] + vec.c * this->m[2][2] + vec.d * this->m[2][3],
                vec.a * this->m[3][0] + vec.b * this->m[3][1] + vec.c * this->m[3][2] + vec.d * this->m[3][3],
            };
        }

        float* operator[](const int& i){
            return m[i];
        }
        const float* operator[](const int& i)const{
            return m[i];
        }

        std::string toString(){
            std::stringstream ss;
            ss << '\n';
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    ss << m[i][j] << ' ';
                }
                ss << '\n';
            }
            return ss.str();
        }
    };

    struct NOVA_API ortho{
        float left,right;
        float bottom, top;
        float far, near;

        ortho(float a,float b,float c,float d,float e,float f) : left(a), right(b), bottom(c), top(d), far(e), near(f) {}
        ortho(){}

        operator nova::mat4(){
            nova::mat4 matrix;
            matrix[0][0] = 2/(right-left); matrix[0][1] = 0;              matrix[0][2] = 0;             matrix[0][3] = -(left+right)/(right-left);
            matrix[1][0] = 0;              matrix[1][1] = 2/(top-bottom); matrix[1][2] = 0;             matrix[1][3] = -(bottom+top)/(top-bottom);
            matrix[2][0] = 0;              matrix[2][1] = 0;              matrix[2][2] = 2/(near-far);  matrix[2][3] = -(near+far)/(near-far);
            matrix[3][0] = 0;              matrix[3][1] = 0;              matrix[3][2] = 0;             matrix[3][3] = 1;
            
            return matrix;
        }

        
    };
}