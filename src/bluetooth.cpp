#include "bluetooth.h"

#include <unistd.h>     // UNIX standard functions
#include <fcntl.h>      // File controle definitions
#include <termios.h>    // Terminal input/ouptut stream
#include <string.h>     // Work with "C" strings
#include <stdlib.h>     // Standard functions (memmory managment)

Bluetooth::Bluetooth(void)
    : m_port(0),
      m_isOpen(false)
{
}

Bluetooth::Bluetooth(const std::string &address)
    : m_port(0),
      m_isOpen(false)
{
    connect(address);
}

Bluetooth::~Bluetooth(void)
{
    disconnect();
}

bool Bluetooth::connect(const std::string &address)
{
    if(m_isOpen)
        disconnect();

    m_port = open(address.c_str(), O_RDWR | O_NOCTTY);
    if(m_port < 0)
        return false;

    //fcntl(m_port, F_SETFL, FNDELAY); // No wait

    struct termios portOptions;
    memset(&portOptions, 0, sizeof(portOptions));
    if(tcgetattr(m_port, &portOptions) < 0)
        return false;

    portOptions.c_cflag |= (CLOCAL | CREAD); // Default parameters (must be set)
    portOptions.c_cflag &= ~(CRTSCTS);
    portOptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    portOptions.c_iflag &= IGNBRK;
    portOptions.c_iflag |=  (INPCK | ISTRIP);
    portOptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    portOptions.c_oflag &= ~(OPOST);
    portOptions.c_cc[VMIN] = 1;     // Block while read
    portOptions.c_cc[VTIME] = 5;    // Timeour for read 0.5s

    // 8 data bits
    portOptions.c_cflag &= ~CSIZE;
    portOptions.c_cflag |= CS8;

    // No parity
    portOptions.c_cflag &= ~PARENB;
    portOptions.c_cflag &= ~PARODD;

    // 1 stop bit
    portOptions.c_cflag &= ~CSTOPB;

    // 9600 baudrate
    cfsetispeed(&portOptions, B9600);
    cfsetospeed(&portOptions, B9600);

    if(tcsetattr(m_port, TCSANOW, &portOptions) < 0)
        return false;

    m_isOpen = true;
    return true;
}

bool Bluetooth::disconnect(void)
{
    if(!isOpen())
        return true;

    fcntl(m_port, F_SETFL, 0);      // Reset default behaviour for port
    if(close(m_port) < 0)
        return false;

    m_isOpen = false;
    return true;
}

bool Bluetooth::send(const std::string &data)
{
    if(write(m_port, data.c_str(), data.size()) < 0)
        return false;

    return true;
}

std::string Bluetooth::readLine(void)
{
    if(!isOpen())
        return "";

    char buffer[100];

    for(int i = 0; i < 100; i++)
    {
        usleep(10000);
        if(read(m_port, buffer + i, 1) < 0)
        {
            i--;
            continue;
        }

        if(buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
    }

    return std::string(buffer);
}
