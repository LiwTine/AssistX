#ifndef ASSISTX_COMMANDPARSER_H
#define ASSISTX_COMMANDPARSER_H

#include "IParser.h"


class CommandParser : public IParser {
public:
    explicit CommandParser();
    std::string parse(const std::string& text) override;
    ~CommandParser() noexcept override;
};
#endif //ASSISTX_COMMANDPARSER_H
