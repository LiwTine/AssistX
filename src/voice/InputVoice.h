#ifndef ASSISTX_INPUTVOICE_H
#define ASSISTX_INPUTVOICE_H

#include "headers/InterfaceVoiceRecognize.h"

class InputVoice : public InterfaceVoiceRecognize, public isRunning {
public:
    void initialize() override;

    void executeProcessing() override;

    ~InputVoice() override;

protected:
    PaStream *_stream;
};


#endif //ASSISTX_INPUTVOICE_H
