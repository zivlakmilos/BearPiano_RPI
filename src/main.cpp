#include <iostream>

#include "bluetooth.h"

int main(int argc, const char *argv[])
{
    Bluetooth bt;

    if(!bt.connect("/dev/rfcomm0"))
    {
        std::cerr << "Fail" << std::endl;
        return -1;
    }

    while(1)
    {
        std::string data;
        data = bt.readLine();
        std::cout << data << std::endl;
    }

    return 0;
}
