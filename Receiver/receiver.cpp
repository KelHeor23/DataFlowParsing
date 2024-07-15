#include "receiver.h"

#include "data_markers.h"

#include <cstring>

Receiver::Receiver()
{
#ifdef TEST
    callback = std::make_shared<CallbackTest>(CallbackTest());
#else
    callback = std::make_shared<Callback>(Callback());
#endif

    binPacketReceiver = std::make_unique<BinPacketReceiver>(BinPacketReceiver(callback));
    textPacketReceiver = std::make_unique<TextPacketReceiver>(TextPacketReceiver(callback));
}

void Receiver::Receive(const char *data, std::size_t size)
{   
    if (size == 0)
        return;

    it = 0;

    while (it < size)
    {
        // Обрабатываем бинарный пакет
        if (*(data + it) == BEGIN_BIN_PACKET || isBinPacket)
        {
            if (*(data + it) == BEGIN_BIN_PACKET)
            {
                it += 1;
                isBinPacket = true;
            }

            binPacketReceiver->receivePacket(data + it, size - it);
            it += binPacketReceiver->getByteProcessed();

            if (binPacketReceiver->isComplete())
                isBinPacket = false;
        }
        else
        {
            // Обрабатываем текстовый пакет
            textPacketReceiver->receivePacket(data + it, size - it);
            it += textPacketReceiver->getByteProcessed();
        }
    }
}
