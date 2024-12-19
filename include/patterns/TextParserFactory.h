#ifndef ASSISTX_FACTORY_H
#define ASSISTX_FACTORY_H

#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include "parser/IParser.h"

class TextParserFactory {
public:
    virtual std::unique_ptr<TextParser> createParser() = 0;
    ~TextParserFactory() = default;

private:

};

class createCommandParser : public TextParserFactory {
public:
    std::unique_ptr<TextParser> createParser() override;
};

class createActionParser : public TextParserFactory {
public:
    std::unique_ptr<TextParser> createParser() override;
};

/*_____________________________________________________________________________________________*/

class TextProcessingPipeline {
private:
    std::vector<std::unique_ptr<TextParser>> parsers;

public:
    void addParser(std::unique_ptr<TextParser> parser);
    //std::string execute(const std::string& input);
    [[nodiscard]] const std::vector<std::unique_ptr<TextParser>>& getParsers() const {return parsers;}
};

class PipelineFactory {
public:
    static TextProcessingPipeline createPipeline();
};

class PipelineProcessor {
private:
    TextProcessingPipeline pipeline;
    std::queue<std::string> inputQueue;
    std::mutex queueMutex;
    std::condition_variable queueCondition;

    friend class TextProcessingPipeline;

public:
    explicit PipelineProcessor(TextProcessingPipeline p) : pipeline(std::move(p)) {}

    void addData(const std::string& data);

    void run();
};

#endif //ASSISTX_FACTORY_H