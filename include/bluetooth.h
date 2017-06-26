#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <string>

class Bluetooth
{
public:
    explicit Bluetooth(void);
    explicit Bluetooth(const std::string &address);
    virtual ~Bluetooth(void);

    bool connect(const std::string &address);
    bool disconnect(void);

    bool send(const std::string &data);
    std::string readLine(void);

    bool isOpen(void) { return m_isOpen; };

private:
    int m_port;
    bool m_isOpen;
};

#endif // _BLUETOOTH_H_
