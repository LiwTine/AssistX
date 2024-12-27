#include "parser/CommandParser.h"

CommandParser::CommandParser()
    : IParser{ ParserType::COMMAND }
{
}

std::string CommandParser::parse(const std::string &text) {
    return {};
}

CommandParser::~CommandParser() noexcept = default;
