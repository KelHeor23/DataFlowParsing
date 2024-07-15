#ifndef CALLBACKTEST_H
#define CALLBACKTEST_H

#include "../Receiver/callback.h"

class CallbackTest : public Callback
{
public:
    void BinaryPacket(const char* data, std::size_t size);
    void TextPacket(const char* data, std::size_t size);
};

#endif // CALLBACKTEST_H
