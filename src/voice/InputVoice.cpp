#include "InputVoice.h"


void InputVoice::initialize() {
    Pa_Initialize();
    Pa_OpenDefaultStream(&_stream, CHANNELS, 0,
                         paInt16, SAMPLE_RATE,
                         FRAMES_PER_BUFFER, nullptr, nullptr);
    Pa_StartStream(_stream);
}

void InputVoice::executeProcessing() {
    while (_isRunning) {
        std::vector<int16_t> buffer(FRAMES_PER_BUFFER);
        if (Pa_ReadStream(_stream, buffer.data(), FRAMES_PER_BUFFER) == paNoError) {
            std::lock_guard<std::mutex> lock(*queueMutex);
            audioQueue->push(buffer);
            //std::cout << "Добавляю данные в очередь" << std::endl; // В InputVoice
            queueCondition->notify_one();
        }
    }
}

InputVoice::~InputVoice() {
    queueCondition->notify_all();
    std::cout << "Очистка Voice!";

    Pa_StopStream(_stream);
    Pa_CloseStream(_stream);

    Pa_Terminate();
}
