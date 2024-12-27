#include "patterns/TextParserFactory.h"
#include "parser/CommandParser.h"
#include "parser/ActionParser.h"
#include "core/isRunning.h"

void patterns::TextProcessingPipeline::addParser(ParserType type) {
    parsers.insert( std::make_pair(type, CreateParser( type ) ) );
}

patterns::TextProcessingPipeline patterns::PipelineFactory::createPipeline() {
    TextProcessingPipeline pipeline;


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
        std::string data;
        std::unique_lock lock(queueMutex );

        queueCondition.wait(lock, [this] {
            return !inputQueue.empty();
        });

        if (!inputQueue.empty()) {
            data = inputQueue.front();
            inputQueue.pop();
        }

        if ( !data.empty( ) ) {
            const auto type = recognizeType( data );
            if ( const auto parser = pipeline.getParser( type ); parser ) {
                auto result = parser->parse( data );
                inputQueue.push( result );
                queueCondition.notify_one();
            }
        }
    }
}

ParserType patterns::PipelineProcessor::recognizeType(const std::string &data) {
    return ParserType::ACTION; // тут нужно понять что именно прилетело, возможно тут будет фильтр
}
