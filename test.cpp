#include<iostream>
#include<type_traits>
#include<memory>

void func(int&& a){
    a++;
    int y = a;
    std::cout<< y << '\n';
}

int main(){
    std::unique_ptr<int> uptr = std::make_unique<int>(5);
    using rawtype = std::decay<std::unique_ptr<int>>;

}