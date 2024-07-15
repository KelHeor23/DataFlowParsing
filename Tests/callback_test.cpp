#include "callback_test.h"
#include <iostream>
#include <ostream>

void CallbackTest::BinaryPacket(const char *data, std::size_t size)
{
    std::cout << "Processed binary package size:" << size << std::endl;

    if (data[0] == 2)
        std::cout << "First byte +" << std::endl;
    else
        std::cout << "First byte -" << std::endl;

    if (data[size - 1] == 3)
        std::cout << "Last byte +" << std::endl;
    else
        std::cout << "Last byte -" << std::endl;
}

void CallbackTest::TextPacket(const char *data, std::size_t size)
{
    std::cout << "Processed text package size:" << size << std::endl;

    if (data[0] == 2)
        std::cout << "First byte +" << std::endl;
    else
        std::cout << "First byte -" << std::endl;

    if (data[size - 1] == 3)
        std::cout << "Last byte +" << std::endl;
    else
        std::cout << "Last byte -" << std::endl;
}
