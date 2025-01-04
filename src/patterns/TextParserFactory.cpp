#include "patterns/TextParserFactory.h"
//#include "parser/CommandParser.h"
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
    inputQueue.push(data);
    queueCondition.notify_one();
}

void patterns::PipelineProcessor::run() {
    while ( isRunning::_isRunning ) {
        std::string inputData;
        std::string result;
        std::unique_lock lock(queueMutex );

        queueCondition.wait(lock, [this] {
            return !inputQueue.empty();
        });

        if (!inputQueue.empty()) {
            inputData = inputQueue.front();
            inputQueue.pop();
        }

        if ( !inputData.empty( ) ) {
            const auto type = recognizeType( inputData );
            if ( const auto parser = pipeline.getParser( type ); parser ) {
                result = parser->parse( inputData, result );
                std::cout << "Parser: " << parser << ", Result: " << result << std::endl;

                if (type == ParserType::JSON) {
                    inputData = result;
                }
                if (type != ParserType::STOP_PARSE) {
                    inputQueue.push(inputData);
                    queueCondition.notify_one();
                }
            }
        }
    }
}

ParserType patterns::PipelineProcessor::recognizeType(const std::string &data) {
    //return ParserType::JSON; // тут нужно понять что именно прилетело, возможно тут будет фильтр

    // Пока так, я не придумал, как реализовать фильтр
    switch (parserIndex) {
        case 0: parserIndex = 1; return ParserType::JSON;
        case 1: parserIndex = 2; return ParserType::ACTION;
        case 2: parserIndex = 3; return ParserType::COMMAND;
        case 3: parserIndex = 0; return ParserType::STOP_PARSE;
        default: parserIndex = 0; return ParserType::UNDEFINED;
    }
}
