#include "parser/ActionParser.h"

ActionParser::ActionParser()
    : IParser( ParserType::ACTION )
{
}


std::string ActionParser::parse(const std::string& text) {
    return {};
}

ActionParser::~ActionParser() noexcept = default;