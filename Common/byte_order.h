#ifndef BYTE_ORDER_H
#define BYTE_ORDER_H

#include <cstddef>

namespace Common
{
    namespace
    {
        template <typename T>
        T swapEndianness(T value) {
            T result = 0;
            for (size_t i = 0; i < sizeof(T); ++i) {
                result = (result << 8) | ((value >> (i * 8)) & 0xFF);
            }
            return result;
        }
    }

    template <typename T>
    T fromHostToLittleEndian(T value)
    {
        #ifdef BIG_ENDIAN
        return swapEndianness(value);
        #endif
        return value;
    }

    template <typename T>
    T fromHostToBigEndian(T value)
    {
        #ifdef LITTLE_ENDIAN
        return swapEndianness(value);
        #endif
        return value;
    }

    template <typename T>
    T fromLittleEndianToHost(T value)
    {
        #ifdef BIG_ENDIAN
        return swapEndianness(value);
        #endif
        return value;
    }

    template <typename T>
    T fromBigEndianToHost(T value)
    {
        #ifdef LITTLE_ENDIAN
        return swapEndianness(value);
        #endif
        return value;
    }
}

#endif // BYTE_ORDER_H
