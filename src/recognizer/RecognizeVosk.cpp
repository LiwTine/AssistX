#include "RecognizeVosk.h"

void RecognizeVosk::initialize() {
    _model = vosk_model_new("lib/model_vosk_small_ru");
    if (!_model) {
        throw std::logic_error("Error on load model");
    }

    _recognizer = vosk_recognizer_new(_model, SAMPLE_RATE);
}

void RecognizeVosk::executeProcessing()  {
    while (isRunning || !audioQueue.empty()) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondition.wait(lock, [this] { return !audioQueue.empty() || !isRunning; });

        if (!audioQueue.empty()) {
            auto buffer = audioQueue.front();
            audioQueue.pop();
            lock.unlock();

            if (vosk_recognizer_accept_waveform(_recognizer,
                                                (const char*)buffer.data(),
                                                static_cast<int>(buffer.size() * sizeof(int16_t)))) {
                std::cout << "Результат: " << vosk_recognizer_result(_recognizer) << std::endl;
            }
        }
    }
}

RecognizeVosk::~RecognizeVosk() = default;