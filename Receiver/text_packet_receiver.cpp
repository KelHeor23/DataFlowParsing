#include "text_packet_receiver.h"

#include "../Common/common_functions.h"
#include "data_markers.h"
#include <algorithm>
#include <cstring>

TextPacketReceiver::TextPacketReceiver(std::shared_ptr<Callback> c)
{
    callback = c;
}

void TextPacketReceiver::receivePacket(const char *data, std::size_t size)
{
    blockSize = size;
    byteProcessed = 0;

    if (size == 0)
        return;

    if (buffer.empty())
        firstReadingAttemptTextPacket(data, size);
    else
        otherReadingAttemptTextPacket(data, size);
}

void TextPacketReceiver::sendPacket(const char *data, std::size_t size)
{
    callback->TextPacket(data, size);
    buffer.clear();
}

void TextPacketReceiver::firstReadingAttemptTextPacket(const char *data, std::size_t size)
{
    const char* found = std::search(data, data + size, END_TEXT_PACKET);
    int   packetSize = 0;

    // Если пакет уместился целиком в блок
    if (found != nullptr) {
        packetSize = found - data;
        sendPacket(data, packetSize);
        byteProcessed += packetSize + 4;
    }
    else
    {
        // Если метка конца не найдена, полностью записываю остаток пакета в буффер
        buffer.append(data, blockSize);
        byteProcessed += blockSize;
    }
}

void TextPacketReceiver::otherReadingAttemptTextPacket(const char *data, std::size_t size)
{
    if (checkEndMark(data))
    {
        // В буффере уже лежит полный пакет - отправляем
        sendPacket(buffer.data(), buffer.size() - 4);
        return;
    }
    else if (byteProcessed < blockSize)
    {
        const char* found = std::search(data, data + size, END_TEXT_PACKET);
        int   packetSize = 0;

        // Если остаток пакета уместился в блок
        if (found != nullptr) {
            packetSize = found - data;
            buffer.append(data, packetSize);
            sendPacket(buffer.data(), buffer.size());
            byteProcessed += packetSize + 4;
        }
        else
        {
            // Если метка конца не найдена, полностью записываю остаток пакета в буффер
            buffer.append(data, blockSize);
            byteProcessed += blockSize;
        }
    }
}

bool TextPacketReceiver::checkEndMark(const char *data)
{
    // Если в буффере что-то есть и его последний символ - один из завершающей последовательности
    if ((*buffer.rbegin() == '\r' && data[0] == '\n') ||
        (*buffer.rbegin() == '\n' && data[0] == '\r'))
    {
        // Перебираем первые три символа нового блока и проверям на конец пакета
        for (int i = 0; i < Common::min(3, blockSize); i++)
        {
            buffer.append(data + i, 1);
            byteProcessed += 1;
            if (buffer.size() >= 4)
            {
                if (strcmp(buffer.data() + buffer.size() - 4, END_TEXT_PACKET) == 0)
                    return true;
            }
        }
    }
    return false;
}

int TextPacketReceiver::getByteProcessed() const
{
    return byteProcessed;
}
