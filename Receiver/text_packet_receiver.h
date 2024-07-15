#ifndef TEXTPACKETRECEIVER_H
#define TEXTPACKETRECEIVER_H

#include "base_interfaces.h"
#include "callback.h"

#include <memory>
#include <string>

class TextPacketReceiver : public IPacketReceiver
{
public:
    TextPacketReceiver(std::shared_ptr<Callback> c);

    void receivePacket(const char* data, std::size_t size); // Функция обработки текстового пакета

    int getByteProcessed() const;

private:
    void sendPacket(const char* data, std::size_t size);    // Функция отправки текстового пакета
    void firstReadingAttemptTextPacket(const char* data);   // Функция первой обработки бинарного пакета
    void otherReadingAttemptTextPacket(const char* data);   // Функция вторичной обработки бинарного пакета
    bool checkEndMark(const char* data);                    // Проверка, на обрезанный признак конца строки

private:
    std::shared_ptr<Callback> callback;

    int byteProcessed = 0;          // Количство обработанных байт текущего блока
    int blockSize = 0;              // Размер текущего блока
    std::string buffer;             // Буффер, в который записывается весь пакет
};

#endif // TEXTPACKETRECEIVER_H
