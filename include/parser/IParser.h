#ifndef ASSISTX_TEXTPARSER_H
#define ASSISTX_TEXTPARSER_H

#include <string>

#include "enums/unmumerations.h"

class IParser {
public:
    explicit IParser( ParserType type )
        : _type { type }
    {
    }

    virtual ~IParser() = default;

    virtual std::string parse(const std::string& text, const std::string& result) = 0;

private:
    ParserType _type = ParserType::UNDEFINED;
};

#endif //ASSISTX_TEXTPARSER_H
