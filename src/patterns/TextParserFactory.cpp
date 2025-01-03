#include "patterns/TextParserFactory.h"
#include "parser/CommandParser.h"
#include "parser/ActionParser.h"
#include "core/isRunning.h"

void patterns::TextProcessingPipeline::addParser(ParserType type) {
    parsers.insert( std::make_pair(type, CreateParser( type ) ) );
}

patterns::TextProcessingPipeline patterns::PipelineFactory::createPipeline() {
    TextProcessingPipeline pipeline;

    pipeline.addParser( ParserType::JSON );
    pipeline.addParser( ParserType::ACTION );
    pipeline.addParser( ParserType::COMMAND );

    return pipeline;
}

void patterns::PipelineProcessor::addData(const std::string &data) {
    std::lock_guard lock(queueMutex);

    std::cout << __FUNCSIG__ << " (" << std::this_thread::get_id() << ")" << std::endl;

    std::cout << "Queue address: " << &inputQueue << std::endl;
    std::cout << "Mutex address: " << &queueMutex << std::endl;
    std::cout << "Condition Variable address: " << &queueCondition << std::endl;

    inputQueue.push(data);
    queueCondition.notify_one();
}

void patterns::PipelineProcessor::run() {
    while ( isRunning::_isRunning ) {
        std::string data;
        std::unique_lock lock(queueMutex );

        std::cout << __FUNCSIG__ << " (" << std::this_thread::get_id() << ")" << std::endl;

        std::cout << "Queue address: " << &inputQueue << std::endl;
        std::cout << "Mutex address: " << &queueMutex << std::endl;
        std::cout << "Condition Variable address: " << &queueCondition << std::endl;

        queueCondition.wait(lock, [this] {
            return !inputQueue.empty();
        });

        if (!inputQueue.empty()) {
            data = inputQueue.front();
            inputQueue.pop();
        }

        if ( !data.empty( ) ) {
            const auto type = recognizeType( data );
            std::cout << data << std::endl;
            if ( const auto parser = pipeline.getParser( type ); parser ) {
                auto result = parser->parse( data );
                std::cout << parser << ": \"" << data << "\""<< std::endl;
                inputQueue.push( result );
                queueCondition.notify_one();
            }
        }
    }
}

ParserType patterns::PipelineProcessor::recognizeType(const std::string &data) {
    return ParserType::JSON; // тут нужно понять что именно прилетело, возможно тут будет фильтр
}
