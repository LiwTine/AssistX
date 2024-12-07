#ifndef ASSISTX_RECOGNIZEVOSK_H
#define ASSISTX_RECOGNIZEVOSK_H

#include "headers/InterfaceVoiceRecognize.h"

class RecognizeVosk : public InterfaceVoiceRecognize, public isRunning{
public:
    void initialize() override;

    void executeProcessing() override;

    ~RecognizeVosk() override;

private:
    VoskModel *_model;
    VoskRecognizer *_recognizer;
};


#endif //ASSISTX_RECOGNIZEVOSK_H
