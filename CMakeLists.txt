cmake_minimum_required(VERSION 3.25)

project(AssistX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(MAIN_EXECUTABLE AssistX)

include_directories(include)

set(SOURCES
        src/core/Assistant.cpp
        src/core/isRunning.cpp
        src/recognizer/RecognizeVosk.cpp
        src/voice/InputVoice.cpp
        src/main.cpp
        src/parser/CommandParser.cpp
        src/parser/ActionParser.cpp
        src/patterns/TextParserFactory.cpp
        src/parser/ParserJSON.cpp)

set(HEADERS
        include/core/Assistant.h
        include/core/Core_Interface.h
        include/core/defines.h
        include/core/isRunning.h
        include/handlers/BaseHandlers.h
        include/parser/ActionParser.h
        include/parser/CommandParser.h
        include/parser/IParser.h
        include/parser/ParameterParser.h
        include/core/InterfaceVoiceRecognize.h
        include/recognizer/RecognizeVosk.h
        include/voice/InputVoice.h
        include/patterns/TextParserFactory.h
        include/parser/ParserJSON.h)

add_executable(AssistX ${SOURCES} ${HEADERS})

set(VOSK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/vosk")
set(VOSK_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/lib/vosk")

find_package(portaudio CONFIG REQUIRED)

include_directories(${VOSK_INCLUDE_PATH})
link_directories(${VOSK_LIB_PATH})

target_link_libraries(AssistX PRIVATE portaudio)
target_link_libraries(AssistX PRIVATE "${CMAKE_SOURCE_DIR}/lib/vosk/libvosk.lib")