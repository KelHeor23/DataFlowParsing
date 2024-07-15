#include "bin_packet_receiver.h"

#include "../Common/byte_order.h"

BinPacketReceiver::BinPacketReceiver(std::shared_ptr<Callback> c)
{
    callback = c;
}

void BinPacketReceiver::receivePacket(const char *data, std::size_t size)
{
    complete = false;
    blockSize = size;
    byteProcessed = 0;

    if (size == 0)
        return;

    // Если размер еще не был полностью считан
    if (binPacketSize.size() < 4)
        readBinPacketSize(data);

    if (binPacketSize.size() == 4)
    {
        if (buffer.empty())
        {
            // Учитываю количество байт считанных для размера пакета
            blockSize -= byteProcessed;
            firstReadingAttemptBinPacket(data + byteProcessed);
        }
        else
            otherReadingAttemptBinPacket(data);
    }
}

int BinPacketReceiver::getByteProcessed() const
{
    return byteProcessed;
}

bool BinPacketReceiver::isComplete() const
{
    return complete;
}

void BinPacketReceiver::firstReadingAttemptBinPacket(const char *data)
{
    // Если пакет уместился в блок целиком, то сразу отправляем
    if (totalBytesBinPacket <= blockSize)
    {
        sendPacket(data, totalBytesBinPacket);

        // Смещаем указатель на размер пакета байт
        byteProcessed += totalBytesBinPacket;
    }
    else
    {
        // Если пакет не уместился в блок целиком, то записываем остатки в буффер
        buffer.reserve(totalBytesBinPacket);
        totalBytesBinPacket -= blockSize;
        buffer.append(data, blockSize);
        byteProcessed += blockSize;
    }
}

void BinPacketReceiver::otherReadingAttemptBinPacket(const char *data)
{
    // Если бинарный пакет заканчивается в этом блоке
    if (totalBytesBinPacket <= blockSize)
    {
        buffer.append(data, totalBytesBinPacket);
        sendPacket(buffer.data(), buffer.size());

        byteProcessed += totalBytesBinPacket;
        totalBytesBinPacket = 0;
    }
    else
    {
        // Если весть блок является частью бинарного пакета
        totalBytesBinPacket -= blockSize;
        buffer.append(data, blockSize);
        byteProcessed += blockSize;
    }
}

void BinPacketReceiver::readBinPacketSize(const char *data)
{
    // Сколько байт нужно для полного считывания размера бинарного пакета
    int needByte = 4 - binPacketSize.size();

    if (blockSize >= needByte)
    {
        binPacketSize.append(data, needByte);

        // Поулчаем размер пакета
        uint32_t *packetSize = reinterpret_cast<uint32_t*>(binPacketSize.data());;
        totalBytesBinPacket = Common::fromLittleEndianToHost(*packetSize);

        byteProcessed += needByte;
    }
    else
    {
        // blockSize байт - это все что у нас есть в текущий момент
        binPacketSize.append(data, blockSize);
        byteProcessed += blockSize;
    }
}

void BinPacketReceiver::sendPacket(const char *data, std::size_t size)
{
    callback->BinaryPacket(data, size);
    buffer.clear();
    binPacketSize.clear();
    complete = true;
}
