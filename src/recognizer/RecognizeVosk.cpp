#include "recognizer/RecognizeVosk.h"

void RecognizeVosk::initialize()
{
    _model = vosk_model_new("D:/work/AssistX/assets/models/model_vosk_small_ru");
    if (!_model) {
        throw std::logic_error("Error on load model");
    }
    _recognizer = vosk_recognizer_new(_model, SAMPLE_RATE);

    pipelineProcessor = std::make_unique<patterns::PipelineProcessor>( patterns::TextProcessingPipeline() );
}

void RecognizeVosk::executeProcessing()  {
    while (_isRunning) {

        std::unique_lock<std::mutex> lock(*queueMutex);

        queueCondition->wait(lock, [this] { return !audioQueue->empty(); });

        if (!audioQueue->empty()) {
            auto buffer = audioQueue->front();
            audioQueue->pop();
            lock.unlock();

            if (vosk_recognizer_accept_waveform(_recognizer,
                                                reinterpret_cast<const char *>(buffer.data()),
                                                static_cast<int>(buffer.size() * sizeof(int16_t))))
            {
                std::string result = vosk_recognizer_result(_recognizer);
                std::cout << "Результат: " << result << std::endl;
                pipelineProcessor->addData(result);
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