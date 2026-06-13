#include<iostream>

class test{
    std::string name;
public:
    test(const std::string& n) : name(n) {}
    inline std::string getName(){return name;}
};

int main(){
    test("hello");
}
