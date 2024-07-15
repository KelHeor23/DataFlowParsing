#ifndef DATA_MARKERS_H
#define DATA_MARKERS_H

enum DataMarkers
{
    BEGIN_BIN_PACKET = 0x24 // маркер начала бинарного пакета
};

constexpr const char* END_TEXT_PACKET = "\r\n\r\n"; // маркер окончания текстового пакета

#endif // DATA_MARKERS_H
