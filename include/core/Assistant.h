#ifndef ASSISTX_ASSISTANT_H
#define ASSISTX_ASSISTANT_H

#include <vector>
#include "InterfaceVoiceRecognize.h"
#include "patterns/TextParserFactory.h"

class Assistant {
public:
    Assistant() = default;

    void Run();

    ~Assistant();

private:
    std::vector<std::unique_ptr<InterfaceVoiceRecognize>> components;
    std::vector<std::thread> threads;

    std::unique_ptr<PipelineProcessor> pipelineProcessor;

    void ComponentInitialize();

    void joinThreads();
};


#endif //ASSISTX_ASSISTANT_H
