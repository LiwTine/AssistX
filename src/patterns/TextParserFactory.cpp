    #include "patterns/TextParserFactory.h"
    #include "parser/CommandParser.h"
    #include "parser/ActionParser.h"
    #include "core/isRunning.h"

    std::unique_ptr<TextParser> createCommandParser::createParser() {
        return std::make_unique<CommandParser>();
    }

    std::unique_ptr<TextParser> createActionParser::createParser() {
        return std::unique_ptr<ActionParser>();
    }

    // Логика изменилась,но оставлю на всякий
    /*std::string TextProcessingPipeline::execute(const std::string &input) {
        std::string data = input;
        for (auto& parser : parsers) {
            data = parser->parse(data);
        }
        return data;
    }*/

    void TextProcessingPipeline::addParser(std::unique_ptr<TextParser> parser) {
        parsers.push_back(std::move(parser));
    }

    TextProcessingPipeline PipelineFactory::createPipeline() {
        TextProcessingPipeline pipeline;

        createCommandParser commandFactory;
        createActionParser actionFactory;

        pipeline.addParser(commandFactory.createParser());
        pipeline.addParser(actionFactory.createParser());

        return pipeline;
    }

    void PipelineProcessor::addData(const std::string &data) {
        std::lock_guard<std::mutex> lock(queueMutex);
        inputQueue.push(data);
        queueCondition.notify_one();
    }

    void PipelineProcessor::run() {
        for (auto& parser : pipeline.getParsers()) {
            std::thread([this, &parser]() {
                while (isRunning::_isRunning) {
                    std::string data;

                    {
                        std::unique_lock<std::mutex> lock(queueMutex);
                        queueCondition.wait(lock, [this] { return !inputQueue.empty();});

                        if (!inputQueue.empty()) {
                            data = inputQueue.front();
                            inputQueue.pop();
                        }
                    }

                    if (!data.empty()) {
                        std::string result = parser->parse(data);

                        {
                            std::lock_guard<std::mutex> lock(queueMutex);
                            inputQueue.push(result);
                        }

                        queueCondition.notify_one();
                    }
                }
            }).detach();
        }
    }
