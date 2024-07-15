#ifndef RECEIVER_H
#define RECEIVER_H

#include "base_interfaces.h"
#include "bin_packet_receiver.h"
#include "text_packet_receiver.h"

#ifdef TEST
#include "../Tests/callback_test.h"
#else
#include "callback.h"
#endif

#include <memory>

class Receiver : public IReceiver
{
public:
    Receiver();

    void Receive(const char* data, std::size_t size);

private:

#ifdef TEST
    std::shared_ptr<CallbackTest>       callback;
#else
    std::shared_ptr<Callback>           callback;
#endif

    std::unique_ptr<BinPacketReceiver>  binPacketReceiver;
    std::unique_ptr<TextPacketReceiver> textPacketReceiver;

    int it = 0;                 // Итератор смащения по блоку данных
    bool isBinPacket = false;   // Флаг, обозначающий начало обработки бинарного пакета
};

#endif // RECEIVER_H
