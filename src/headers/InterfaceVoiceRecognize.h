#ifndef ASSISTX_INTERFACEVOICERECOGNIZE_H
#define ASSISTX_INTERFACEVOICERECOGNIZE_H

#include "Core_Interface.h"
#include "vosk_api.h"
#include "defines.h"
#include "core/isRunning.h"
#include "portaudio.h"
#include <mutex>
#include <queue>
#include <iostream>

class InterfaceVoiceRecognize : CoreAssistantInterface{
public:
    void initialize() override = 0;

    void executeProcessing() override = 0;

    ~InterfaceVoiceRecognize() override = default;

protected:
    std::queue<std::vector<int16_t>> audioQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;
};

#endif //ASSISTX_INTERFACEVOICERECOGNIZE_H
