#ifndef ASSISTX_FACTORY_H
#define ASSISTX_FACTORY_H

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <mutex>

#include "parser/ActionParser.h"
#include "parser/CommandParser.h"
#include "parser/ParserJSON.h"
#include "parser/IParser.h"

namespace patterns {
    inline std::shared_ptr<IParser> CreateParser( ParserType type ) {
        switch ( type ) {
            case ParserType::JSON: return std::make_shared<ParserJSON>();
            case ParserType::ACTION: return std::make_shared<ActionParser>();
            case ParserType::COMMAND: return std::make_shared<CommandParser>();
            default: return nullptr;
        }
    }

    /*_____________________________________________________________________________________________*/

    class TextProcessingPipeline {
    public:
        void addParser( ParserType type );

        [[nodiscard]] const std::map<ParserType, std::shared_ptr<IParser>>& getParsers() const { return parsers; } // не совсем понятно зачем этот метод

        std::shared_ptr<IParser> getParser( ParserType type ) {
            if ( parsers.find(type) == parsers.end() )
                return nullptr;

            return parsers[type];
        }

    private:
        std::map<ParserType, std::shared_ptr<IParser>> parsers;
    };

    class PipelineFactory {
    public:
        static TextProcessingPipeline createPipeline();
    };

    class PipelineProcessor {
    public:
        explicit PipelineProcessor(TextProcessingPipeline p)
            : pipeline(std::move(p))
        {
            std::cout << __FUNCSIG__ << " (" << std::this_thread::get_id() << ")" << std::endl;
        }

        ~PipelineProcessor() {
            std::cout << __FUNCSIG__ << " (" << std::this_thread::get_id() << ")" << std::endl;
            std::cout << "ПАДАЕТ" << std::endl;
        }

        void addData(const std::string& data);

        void run();


    private:
        ParserType recognizeType(const std::string& data);

    private:
        int parserIndex = 0;
        TextProcessingPipeline pipeline;
        std::queue<std::string> inputQueue;
        std::mutex queueMutex;
        std::condition_variable queueCondition;

        friend class TextProcessingPipeline;

    };
} // namespace patterns

#endif //ASSISTX_FACTORY_H