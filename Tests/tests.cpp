#include "tests.h"

#include "../Common/byte_order.h"
#include "../Receiver/data_markers.h"
#include "../Receiver/receiver.h"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <ostream>

char *Tests::getSimpleBinaryPacket(int packetSize)
{
    packetSize += 5;
    char* packet = new char[packetSize];

    packet[0] = BEGIN_BIN_PACKET; // маркер начала бинарного пакета

    uint32_t size = packetSize - 1 - sizeof(uint32_t);
    uint32_t sizeLittleEndian = Common::fromHostToLittleEndian(size);

    std::memcpy(&packet[1], &sizeLittleEndian, sizeof(uint32_t));
    std::memset(&packet[5], '1', size);

    packet[5] = 2;
    packet[packetSize - 1] = 3;

    return packet;
}

char *Tests::getDoubleBinaryPacket(int packetSize)
{
    char* packet1 = getSimpleBinaryPacket(packetSize);
    char* packet2 = getSimpleBinaryPacket(packetSize);

    packetSize += 5;
    char *array = new char[packetSize * 2];

    std::memcpy(array, packet1, packetSize);
    std::memcpy(array + packetSize, packet2, packetSize);

    delete[] packet1;
    delete[] packet2;

    return array;
}

std::vector<char *> Tests::getDoubleBinaryPacketInTwoBlocks(int packetSize, int blockSize1, int blockSize2)
{
    std::vector<char *> res;
    char *block1 = new char[blockSize1];
    char *block2 = new char[blockSize2];

    char* packet1 = getSimpleBinaryPacket(packetSize);
    char* packet2 = getSimpleBinaryPacket(packetSize);

    packetSize += 5;

    std::memcpy(block1, packet1, packetSize);
    std::memcpy(block1 + packetSize, packet2, blockSize1 - packetSize);
    std::memcpy(block2, packet2 + (blockSize1 - packetSize), packetSize - (blockSize1 - packetSize));

    res.push_back(block1);
    res.push_back(block2);

    delete[] packet1;
    delete[] packet2;

    return res;
}

std::vector<char *> Tests::getBinaryPacketInThreeBlocks(int packetSize, int blockSize1, int blockSize2, int blockSize3)
{
    std::vector<char *> res;
    char *block1 = new char[blockSize1];
    char *block2 = new char[blockSize2];
    char *block3 = new char[blockSize3];

    char* packet = getSimpleBinaryPacket(packetSize);

    std::memcpy(block1, packet, blockSize1);
    std::memcpy(block2, packet + blockSize1, blockSize2);
    std::memcpy(block3, packet + blockSize1 + blockSize2, blockSize3);

    res.push_back(block1);
    res.push_back(block2);
    res.push_back(block3);

    delete[] packet;

    return res;
}

std::vector<char *> Tests::getBinaryPacketInCharactersBlocks(int packetSize)
{
    std::vector<char *> res;
    char* packet = getSimpleBinaryPacket(packetSize);

    for (int i = 0; i < packetSize + 5; i++)
    {
        res.push_back(new char[i]);
        res[i][0] = packet[i];
    }

    return res;
}

char *Tests::getSimpleTextPacket(int packetSize)
{
    char* packet = new char[packetSize + 4];

    packetSize += 4;

    std::memset(packet, '1', packetSize);

    packet[0] = 2;
    packet[packetSize - 5] = 3;

    std::memcpy(packet + packetSize - 4, END_TEXT_PACKET, 4);

    return packet;
}

char *Tests::getDoubleTextPacket(int packetSize)
{
    char* packet1 = getSimpleTextPacket(packetSize);
    char* packet2 = getSimpleTextPacket(packetSize);

    packetSize += 4;

    char *array = new char[packetSize * 2];

    std::memcpy(array, packet1, packetSize);
    std::memcpy(array + packetSize, packet2, packetSize);

    delete[] packet1;
    delete[] packet2;

    return array;
}

std::vector<char *> Tests::getDoubleTextPacketInTwoBlocks(int packetSize, int blockSize1, int blockSize2)
{
    std::vector<char *> res;
    char *block1 = new char[blockSize1];
    char *block2 = new char[blockSize2];

    char* packet1 = getSimpleTextPacket(packetSize);
    char* packet2 = getSimpleTextPacket(packetSize);

    packetSize += 4;

    std::memcpy(block1, packet1, packetSize);
    std::memcpy(block1 + packetSize, packet2, blockSize1 - packetSize);
    std::memcpy(block2, packet2 + (blockSize1 - packetSize), packetSize - (blockSize1 - packetSize));

    res.push_back(block1);
    res.push_back(block2);

    delete[] packet1;
    delete[] packet2;

    return res;
}

std::vector<char *> Tests::getTextPacketInThreeBlocks(int packetSize, int blockSize1, int blockSize2, int blockSize3)
{
    std::vector<char *> res;
    char *block1 = new char[blockSize1];
    char *block2 = new char[blockSize2];
    char *block3 = new char[blockSize3];

    char* packet = getSimpleTextPacket(packetSize);

    std::memcpy(block1, packet, blockSize1);
    std::memcpy(block2, packet + blockSize1, blockSize2);
    std::memcpy(block3, packet + blockSize1 + blockSize2, blockSize3);

    res.push_back(block1);
    res.push_back(block2);
    res.push_back(block3);

    delete[] packet;

    return res;
}

std::vector<char *> Tests::getTextPacketInCharactersBlocks(int packetSize)
{
    std::vector<char *> res;
    char* packet = getSimpleTextPacket(packetSize);

    for (int i = 0; i < packetSize + 4; i++)
    {
        res.push_back(new char[i]);
        res[i][0] = packet[i];
    }

    delete[] packet;

    return res;
}


char *Tests::getBinAndTextPackets(int binPacketSize, int textPacketSize)
{
    char* binPacket = getSimpleBinaryPacket(binPacketSize);
    char* textPacket = getSimpleTextPacket(textPacketSize);

    binPacketSize += 5;
    textPacketSize += 4;

    char *block = new char[binPacketSize + textPacketSize];

    std::memcpy(block, binPacket, binPacketSize);
    std::memcpy(block + binPacketSize, textPacket, textPacketSize);

    delete[] binPacket;
    delete[] textPacket;

    return block;
}

char *Tests::getTextAndBinPackets(int textPacketSize, int binPacketSize)
{
    char* binPacket = getSimpleBinaryPacket(binPacketSize);
    char* textPacket = getSimpleTextPacket(textPacketSize);

    binPacketSize += 5;
    textPacketSize += 4;

    char *block = new char[binPacketSize + textPacketSize];

    std::memcpy(block, textPacket, textPacketSize);
    std::memcpy(block + textPacketSize, binPacket, binPacketSize);

    delete[] binPacket;
    delete[] textPacket;

    return block;
}

std::vector<char *> Tests::getBinAndTextTextPacketInCharactersBlocks(int binPacketSize)
{
    std::vector<char *> res;
    char* binPacket = getSimpleBinaryPacket(binPacketSize);
    const char* textPacket = "\00211111\003\r\n\r\n";

    binPacketSize += 5;

    char *block = new char[binPacketSize + 11];

    std::memcpy(block, binPacket, binPacketSize);
    std::memcpy(block + binPacketSize, textPacket, 11);

    for (int i = 0; i < binPacketSize + 11; i++)
    {
        res.push_back(new char[i]);
        res[i][0] = block[i];
    }

    delete[] binPacket;
    delete[] block;
    return res;
}

std::vector<char *> Tests::getTextAndBinTextPacketInCharactersBlocks(int binPacketSize)
{
    std::vector<char *> res;
    char* binPacket = getSimpleBinaryPacket(binPacketSize);
    const char* textPacket = "\00211111\003\r\n\r\n";

    binPacketSize += 5;

    char *block = new char[binPacketSize + 11];

    std::memcpy(block, textPacket, 11);
    std::memcpy(block + 1, binPacket, binPacketSize);

    for (int i = 0; i < binPacketSize + 11; i++)
    {
        res.push_back(new char[i]);
        res[i][0] = block[i];
    }

    delete[] binPacket;
    delete[] block;
    return res;
}

void Tests::Test::run()
{
    Receiver receiver;

    std::cout << "One binary packet, size 30 in one data block" << std::endl;
    receiver.Receive(getSimpleBinaryPacket(30), 35);

    std::cout << std::endl << "Two binary packets, size 29 in one data block" << std::endl;
    receiver.Receive(getDoubleBinaryPacket(29), 68);

    std::cout << std::endl << "Two binary packets, size 29 in two data block" << std::endl;
    std::vector<char *> temp = getDoubleBinaryPacketInTwoBlocks(29, 40, 28);
    receiver.Receive(temp[0], 40);
    receiver.Receive(temp[1], 28);

    std::cout << std::endl << "One binary packet, size 46 in three data block" << std::endl;
    temp = getBinaryPacketInThreeBlocks(46, 21, 20, 10);
    receiver.Receive(temp[0], 21);
    receiver.Receive(temp[1], 20);
    receiver.Receive(temp[2], 10);

    std::cout << std::endl << "One text packet, size 30 in one data block" << std::endl;
    receiver.Receive(getSimpleTextPacket(30), 34);

    std::cout << std::endl << "Two text packets, size 36 in one data block" << std::endl;
    receiver.Receive(getDoubleTextPacket(36), 76);

    std::cout << std::endl << "Two text packets, size 30 in two data block" << std::endl;
    temp = getDoubleTextPacketInTwoBlocks(30, 40, 28);
    receiver.Receive(temp[0], 40);
    receiver.Receive(temp[1], 28);

    std::cout << std::endl << "One binary packet size 10 and One text packet size 11, in one data block" << std::endl;
    receiver.Receive(getBinAndTextPackets(10, 11), 30);

    std::cout << std::endl << "One text packet size 10 and One binary packet size 11, in one data block" << std::endl;
    receiver.Receive(getTextAndBinPackets(10, 11), 30);

    std::cout << std::endl << "One binary packet, size 7 in three data block (size: 1, 1, 10)" << std::endl;
    temp = getBinaryPacketInThreeBlocks(7, 1, 1, 10);
    receiver.Receive(temp[0], 1);
    receiver.Receive(temp[1], 1);
    receiver.Receive(temp[2], 10);

    std::cout << std::endl << "One text packet, size 10 in three data block (size: 9, 3, 2)" << std::endl;
    temp = getTextPacketInThreeBlocks(10, 9, 3, 2);
    receiver.Receive(temp[0], 9);
    receiver.Receive(temp[1], 3);
    receiver.Receive(temp[2], 2);

    std::cout << std::endl << "One binary packet size 5 in 10 data block" << std::endl;
    temp = getBinaryPacketInCharactersBlocks(5);
    for (int i = 0; i < temp.size(); i++)
        receiver.Receive(temp[i], 1);

    std::cout << std::endl << "One binary packet size 5 in 10 data block" << std::endl;
    temp = getBinaryPacketInCharactersBlocks(5);
    for (int i = 0; i < temp.size(); i++)
        receiver.Receive(temp[i], 1);

    std::cout << std::endl << "binary packet size 5 and text packet size 7 in 21 data block" << std::endl;
    temp = getBinAndTextTextPacketInCharactersBlocks(5);
    for (int i = 0; i < temp.size(); i++)
        receiver.Receive(temp[i], 1);

    std::cout << std::endl << "text packet size 7 and binary packet size 5 in 21 data block" << std::endl;
    temp = getBinAndTextTextPacketInCharactersBlocks(5);
    for (int i = 0; i < temp.size(); i++)
        receiver.Receive(temp[i], 1);

    temp.clear();

    std::cout << std::endl << "Two data blocks: \\00211111\\003\\r\\n and \\r\\n\\00211111\\003\\r\\n\\r\\n" << std::endl;
    temp.push_back(std::string("\00211111\003\r\n").data());
    temp.push_back(std::string("\r\n\00211111\003\r\n\r\n").data());
    receiver.Receive(temp[0], 9);
    receiver.Receive(temp[1], 13);
}
