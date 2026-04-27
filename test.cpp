#include<iostream>

#define sfy(type) #type

void hello(int x){
    if(!x) return;
    static int h = 1;
    std::cout<< h << ' ';
    hello(x-1);
}

int main(){
    int age = 23;
    std::string s = sfy(23);

    hello(5);
}