#include<iostream>
#include"nova.h"

int main(){
    nova::log my_logger;
    my_logger.init();
    my_logger.log_to_client();
}