#ifndef CALLBACK_H
#define CALLBACK_H

#include "base_interfaces.h"

class Callback : public ICallback
{
public:
    virtual void BinaryPacket(const char* data, std::size_t size);
    virtual void TextPacket(const char* data, std::size_t size);
};

#endif // CALLBACK_H
