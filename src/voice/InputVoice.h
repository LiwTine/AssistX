#ifndef ASSISTX_INPUTVOICE_H
#define ASSISTX_INPUTVOICE_H

#include "headers/InterfaceVoiceRecognize.h"

class InputVoice : public InterfaceVoiceRecognize, public isRunning {
public:

    InputVoice(std::shared_ptr<std::queue<std::vector<int16_t>>> queue,
               std::shared_ptr<std::mutex> mutex,
               std::shared_ptr<std::condition_variable> condition)
    : InterfaceVoiceRecognize(std::move(queue), std::move(mutex), std::move(condition)) {}

    void initialize() override;

    void executeProcessing() override;

    ~InputVoice() override;

protected:
    PaStream *_stream{};

};


#endif //ASSISTX_INPUTVOICE_H
