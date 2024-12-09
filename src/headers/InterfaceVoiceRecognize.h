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
    InterfaceVoiceRecognize(std::shared_ptr<std::queue<std::vector<int16_t>>> queue,
                            std::shared_ptr<std::mutex> mutex,
                            std::shared_ptr<std::condition_variable> condition)
            : audioQueue(std::move(queue)), queueMutex(std::move(mutex)), queueCondition(std::move(condition)) {}


    void initialize() override = 0;
    void executeProcessing() override = 0;
    ~InterfaceVoiceRecognize() override = default;

protected:
    std::shared_ptr<std::queue<std::vector<int16_t>>> audioQueue;
    std::shared_ptr<std::mutex> queueMutex;
    std::shared_ptr<std::condition_variable> queueCondition;
};

#endif //ASSISTX_INTERFACEVOICERECOGNIZE_H
