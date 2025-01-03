#ifndef ASSISTX_RECOGNIZEVOSK_H
#define ASSISTX_RECOGNIZEVOSK_H

#include "core/InterfaceVoiceRecognize.h"
#include "patterns/TextParserFactory.h"
#include <functional>

class RecognizeVosk : public InterfaceVoiceRecognize, public isRunning{
public:
    RecognizeVosk(
        // std::function<std::deque<std::string>&()> q_getter,
        std::shared_ptr<std::queue<std::vector<int16_t>>> queue,
        std::shared_ptr<std::mutex> mutex,
        std::shared_ptr<std::condition_variable> condition)
    : InterfaceVoiceRecognize(std::move(queue), std::move(mutex), std::move(condition))
    // , _shared_queue_getter( q_getter )
    {

    }

    void initialize() override;
    void executeProcessing() override;
    ~RecognizeVosk() override;

private:
    VoskModel *_model{};
    VoskRecognizer *_recognizer{};

    std::unique_ptr<patterns::PipelineProcessor> pipelineProcessor;

    // std::function<std::deque<std::string>&()> _shared_queue_getter;
};


#endif //ASSISTX_RECOGNIZEVOSK_H
