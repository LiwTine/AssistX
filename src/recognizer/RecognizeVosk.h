#ifndef ASSISTX_RECOGNIZEVOSK_H
#define ASSISTX_RECOGNIZEVOSK_H

#include <core/InterfaceVoiceRecognize.h>

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
