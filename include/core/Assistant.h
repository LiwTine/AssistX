#ifndef ASSISTX_ASSISTANT_H
#define ASSISTX_ASSISTANT_H

#include <vector>
#include "recognizer/InterfaceVoiceRecognize.h"

class Assistant {
public:
    void Run();

    ~Assistant();

private:
    std::vector<std::unique_ptr<InterfaceVoiceRecognize>> components;
    std::vector<std::thread> threads;

    void ComponentInitialize();

    void joinThreads();
};


#endif //ASSISTX_ASSISTANT_H
