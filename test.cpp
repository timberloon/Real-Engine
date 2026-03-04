#include<iostream>

#define sfy(type) #type

int main(){
    int age = 23;
    std::string s = sfy(23);

    std::cout<< s;
}