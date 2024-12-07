#include "recognizer/RecognizeVosk.h"
#include "voice/InputVoice.h"
#include "Assistant.h"
#include "isRunning.h"


void Assistant::ComponentInitialize() {
    components.push_back(std::make_unique<InputVoice>());
    components.push_back(std::make_unique<RecognizeVosk>());
}


void Assistant::Run() {
    ComponentInitialize();
    isRunning::startRun();

    for (auto &init : components) {
        init->initialize();
    }

    for (auto &component : components) {
        threads.emplace_back([component = std::move(component)]() {
            component->executeProcessing();
        });
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Assistant::joinThreads() {
    isRunning::stopRun();

    for (auto &thread : threads) {
        if (thread.joinable())
            thread.join();
    }
}


Assistant::~Assistant() {
    std::cout << "Очистка потоков!";
    joinThreads();
}
