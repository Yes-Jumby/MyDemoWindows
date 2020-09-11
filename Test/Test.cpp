#include "Test.h"

#include <iostream>

Test::Test()
{
    s = "hello form dll-MyTest";
}

Test::~Test()
{
    std::cout << "destroy-MyTest";
}

void Test::ShowMsg()
{
    std::cout << s << std::endl;
}
