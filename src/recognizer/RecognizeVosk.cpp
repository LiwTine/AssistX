#include "recognizer/RecognizeVosk.h"

void RecognizeVosk::initialize() {
    _model = vosk_model_new("C:/Users/ImbaM/Desktop/AssistX/assets/models/model_vosk_small_ru");
    if (!_model) {
        throw std::logic_error("Error on load model");
    }

    _recognizer = vosk_recognizer_new(_model, SAMPLE_RATE);
}

void RecognizeVosk::executeProcessing()  {
    while (_isRunning) {
        std::unique_lock<std::mutex> lock(*queueMutex);
        queueCondition->wait(lock, [this] { return !audioQueue->empty() || !_isRunning; });

        if (!audioQueue->empty()) {
            auto buffer = audioQueue->front();
            audioQueue->pop();
            lock.unlock();

            if (vosk_recognizer_accept_waveform(_recognizer,
                                                (const char*)buffer.data(),
                                                static_cast<int>(buffer.size() * sizeof(int16_t)))) {
                std::cout << "Результат: " << vosk_recognizer_result(_recognizer) << std::endl;
            }
        }
    }
}

RecognizeVosk::~RecognizeVosk() {
    queueCondition->notify_all();
    std::cout << "Очистка Recognize!";

    if (_recognizer) {
        vosk_recognizer_free(_recognizer);
        _recognizer = nullptr;
    }
    if (_model) {
        vosk_model_free(_model);
        _model = nullptr;
    }
}