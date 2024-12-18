#ifndef ASSISTX_RECOGNIZEVOSK_H
#define ASSISTX_RECOGNIZEVOSK_H

#include "InterfaceVoiceRecognize.h"

class RecognizeVosk : public InterfaceVoiceRecognize, public isRunning{
public:
    RecognizeVosk(std::shared_ptr<std::queue<std::vector<int16_t>>> queue,
                  std::shared_ptr<std::mutex> mutex,
                  std::shared_ptr<std::condition_variable> condition)
    : InterfaceVoiceRecognize(std::move(queue), std::move(mutex), std::move(condition)) {}

    void initialize() override;
    void executeProcessing() override;
    ~RecognizeVosk() override;

private:
    VoskModel *_model{};
    VoskRecognizer *_recognizer{};

};


#endif //ASSISTX_RECOGNIZEVOSK_H
