# DataFlowParsing

There is a data stream consisting of two types of packets:
If the packet starts with 0x24 (one byte), then it is a "binary" packet. 0x24 is followed by the packet data size in bytes (four byte
unsigned integer, little endian byte order), and then the data itself.
Otherwise – a “text” package. The "text" packet ends with the sequence "\r\n\r\n" (four bytes).
Packets of various types can occur in a stream in any quantity and in any combination. The data stream does not contain errors or "garbage".
The data stream is divided into blocks of various sizes. Blocks are not related to packets in any way, they can be several packets in one block,
Likewise, one packet can be divided into several blocks.
