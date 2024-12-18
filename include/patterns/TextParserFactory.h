#ifndef ASSISTX_FACTORY_H
#define ASSISTX_FACTORY_H

#include <iostream>
#include "parser/IParser.h"

class TextParserFactory {
public:
    virtual std::unique_ptr<TextParser> createParser() = 0;
    ~TextParserFactory() = default;
};

class createCommandParser : public TextParserFactory {
public:
    std::unique_ptr<TextParser> createParser() override;
};

class createActionParser : public TextParserFactory {
public:
    std::unique_ptr<TextParser> createParser() override;
};

#endif //ASSISTX_FACTORY_H
