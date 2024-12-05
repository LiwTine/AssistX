#include "InputVoice.h"


void InputVoice::initialize() {
    Pa_Initialize();
    Pa_OpenDefaultStream(&_stream, CHANNELS, 0,
                         paInt16, SAMPLE_RATE,
                         FRAMES_PER_BUFFER, nullptr, nullptr);
    Pa_StartStream(_stream);
}

void InputVoice::executeProcessing() {
    while (isRunning) {
        std::vector<int16_t> buffer(FRAMES_PER_BUFFER);
        if (Pa_ReadStream(_stream, buffer.data(), FRAMES_PER_BUFFER) == paNoError) {
            std::lock_guard<std::mutex> lock(queueMutex);
            audioQueue.push(buffer);
            queueCondition.notify_one();
        }
    }
}

InputVoice::~InputVoice() = default;
