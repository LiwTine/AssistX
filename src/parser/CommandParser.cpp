#include "parser/CommandParser.h"

CommandParser::CommandParser()
    : IParser{ ParserType::COMMAND }
{
}

std::string CommandParser::parse(const std::string& text, const std::string& result) {
    return {"ParserType::COMMAND"};
}

CommandParser::~CommandParser() noexcept = default;
