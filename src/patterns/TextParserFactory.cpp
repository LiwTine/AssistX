#include "patterns/TextParserFactory.h"
#include "parser/CommandParser.h"
#include "parser/ActionParser.h"

std::unique_ptr<TextParser> createCommandParser::createParser() {
    return std::make_unique<CommandParser>();
}

std::unique_ptr<TextParser> createActionParser::createParser() {
    return std::unique_ptr<ActionParser>();
}
