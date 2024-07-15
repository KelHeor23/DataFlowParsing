#ifndef TESTS_H
#define TESTS_H

#include <vector>
namespace Tests
{

// Базовые тесты про идеальные условия
char* getSimpleBinaryPacket(int);   //  Возвращает один бинарный пакет
char* getDoubleBinaryPacket(int);   //  Возвращает два бинарных пакета в одном блоке
std::vector<char*> getDoubleBinaryPacketInTwoBlocks(int, int, int); // Возвращает два бинарных пакета в двух блоках, разного размера
std::vector<char*> getBinaryPacketInThreeBlocks(int, int, int, int); // Возвращает бинарный пакет в трех блоках, разного размера
std::vector<char*> getBinaryPacketInCharactersBlocks(int); // Возвращает бинарный пакет в Количество символов блоках

char* getSimpleTextPacket(int);   //  Возвращает один текстовый пакет
char* getDoubleTextPacket(int);   //  Возвращает два текстовых пакета в одном блоке
std::vector<char*> getDoubleTextPacketInTwoBlocks(int, int, int); // Возвращает два текстовых пакета в двух блоках, разного размера
std::vector<char*> getTextPacketInThreeBlocks(int, int, int, int); // Возвращает текстовый пакет в трех блоках, разного размера
std::vector<char*> getTextPacketInCharactersBlocks(int); // Возвращает текстовый пакет в Количество символов блоках

char* getBinAndTextPackets(int, int);  // Бинарный и текстовый пакет в одном текстовом блоке
char* getTextAndBinPackets(int, int);  // Текстовый и бинарный пакет в одном текстовом блоке
std::vector<char*> getBinAndTextTextPacketInCharactersBlocks(int); // Возвращает бинарный и текстовый пакет в количество символов блоках
std::vector<char*> getTextAndBinTextPacketInCharactersBlocks(int); // Возвращает текстовый и бинарный пакет в количество символов блоках

class Test
{
public:
    void run();
};

}


#endif // TESTS_H
