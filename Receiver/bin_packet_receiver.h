#ifndef BINPACKETRECEIVER_H
#define BINPACKETRECEIVER_H

#include "base_interfaces.h"
#include "callback.h"

#include <cstddef>
#include <memory>
#include <string>

class BinPacketReceiver : public IPacketReceiver
{
private:
    void firstReadingAttemptBinPacket(const char* data);    // Функция первой обработки бинарного пакета
    void otherReadingAttemptBinPacket(const char* data);    // Функция вторичной обработки бинарного пакета
    void readBinPacketSize(const char* data);               // Функция считывающая размер бинарного пакета
    void sendPacket(const char* data, std::size_t size);    // Функция отправки бинарного пакета

public:
    BinPacketReceiver(std::shared_ptr<Callback>);

    void receivePacket(const char* data, std::size_t size);

    int getByteProcessed() const;
    bool isComplete() const;

private:
    std::string binPacketSize;      // Буффер, в который записывается размер бинарного пакета
    std::string buffer;             // Буффер, в который записывается весь пакет

    int totalBytesBinPacket = 0;    // Количество байт, которые нужно еще считать как бинарный пакет
    int byteProcessed = 0;          // Количство обработанных байт текущего блока
    int blockSize = 0;              // Размер текущего блока
    bool complete = false;          // Флаг, что обработка пакета завершена

    std::shared_ptr<Callback> callback;
};

#endif // BINPACKETRECEIVER_H
