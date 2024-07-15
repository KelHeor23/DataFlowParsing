cmake_minimum_required(VERSION 3.5)

project(ParsingTheDataStream LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ParsingTheDataStream main.cpp
    Receiver/base_interfaces.h
    Receiver/receiver.h Receiver/receiver.cpp
    Receiver/callback.h Receiver/callback.cpp
    Tests/tests.h Tests/tests.cpp
    Common/byte_order.h
    Receiver/data_markers.h

    Tests/callback_test.h Tests/callback_test.cpp
    Receiver/bin_packet_receiver.h Receiver/bin_packet_receiver.cpp
    Receiver/text_packet_receiver.h Receiver/text_packet_receiver.cpp
    Common/common_functions.h
)

include(GNUInstallDirs)
install(TARGETS ParsingTheDataStream
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_compile_definitions(TEST)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    add_compile_definitions(BIG_ENDIAN)
else()
    add_compile_definitions(LITTLE_ENDIAN)
endif()
