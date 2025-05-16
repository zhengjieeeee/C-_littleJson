#include <iostream>
#include "Json.h"

using namespace MyJson;

int main(){
    Json v1 = 1;
    Json v2 = true;
    Json v3 = 1.2;
    Json v4 = "hello";
    Json v5 = v1;

    int i = v1;
    bool b = v2;
    double d = v3;
    std::string s = v4;
    Json j = v5;
    /*
    std::cout << i << std::endl;
    std::cout << b << std::endl;    
    std::cout << d << std::endl;
    std::cout << s << std::endl;
    */

    Json arr;
    arr[0] = 1;
    arr[1] = true;
    arr[2] = 1.2;
    arr[3] = "hello";
    arr.append("world");

    //std:: cout << arr.tostr() << std::endl;

    Json obj;
    obj["bool"] = true;
    obj["int"] = 1;
    obj["double"] = 1.2;
    obj["str"] = "hello";

    std::cout << obj.getKey(0) << std::endl;
    std::cout << obj.getValue(0) << std::endl;
    //std:: cout << obj.tostr() << std::endl;

    return 0;
}