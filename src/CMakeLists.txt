set(HEADER_FILES
        headers/Core_Interface.h
        recognizer/RecognizeVosk.h
        headers/defines.h
        core/isRunning.h
        headers/InterfaceVoiceRecognize.h
        voice/InputVoice.h
        core/Assistant.h)

set(SOURCE_FILES
        main.cpp
        recognizer/RecognizeVosk.cpp
        voice/InputVoice.cpp
        core/Assistant.cpp
        core/isRunning.cpp)

add_executable(AssistX ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(AssistX PRIVATE ${CMAKE_SOURCE_DIR}/src)

set(VOSK_LIB_PATH "${CMAKE_SOURCE_DIR}/lib/vosk")
set(VOSK_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/lib/vosk")

find_package(portaudio CONFIG REQUIRED)

include_directories(${VOSK_INCLUDE_PATH})
link_directories(${VOSK_LIB_PATH})

target_link_libraries(AssistX PRIVATE portaudio)
target_link_libraries(AssistX PRIVATE "${CMAKE_SOURCE_DIR}/lib/vosk/libvosk.lib")
