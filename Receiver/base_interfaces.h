#ifndef BASE_INTERFACES_H
#define BASE_INTERFACES_H

#include <cstddef>

struct IReceiver
{
    virtual void Receive(const char* data, std::size_t size) = 0;
};

struct ICallback
{
    virtual void BinaryPacket(const char* data, std::size_t size) = 0;
    virtual void TextPacket(const char* data, std::size_t size) = 0;
};

class IPacketReceiver
{
    virtual void receivePacket(const char* data, std::size_t size) = 0;
    virtual void sendPacket(const char* data, std::size_t size) = 0;
};

#endif // BASE_INTERFACES_H
