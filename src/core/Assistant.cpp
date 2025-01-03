#include "recognizer/RecognizeVosk.h"
#include "voice/InputVoice.h"
#include "core/Assistant.h"
#include "core/isRunning.h"
#include <regex>

void Assistant::ComponentInitialize() {
    auto queue = std::make_shared<std::queue<std::vector<int16_t>>>();
    auto mutex = std::make_shared<std::mutex>();
    auto condition = std::make_shared<std::condition_variable>();

    components.push_back(std::make_unique<RecognizeVosk>(queue, mutex, condition));
    components.push_back(std::make_unique<InputVoice>(queue, mutex, condition));

    pipelineProcessor = std::make_unique< patterns::PipelineProcessor >( patterns::PipelineFactory::createPipeline ( ) );
}


void Assistant::Run( ) {
    ComponentInitialize( );
    isRunning::startRun( );

    std::thread pipelineThread([this]() {
        pipelineProcessor->run();
    });

    for (auto &component : components) {
        threads.emplace_back([component = std::move(component)]() {
            component->initialize();
            component->executeProcessing();
            std::cout << "Поток создан: " << std::this_thread::get_id() << std::endl;
        });
    }

    pipelineThread.join();

}

void Assistant::joinThreads() {
    isRunning::stopRun();

    for (auto &thread : threads) {
        if (thread.joinable()) {
            thread.join();
            std::cout << "Очистка потока: " << thread.get_id();
        }
    }
}


Assistant::~Assistant() {
    joinThreads();
}
