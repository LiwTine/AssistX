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

    [[nodiscard]] ParserType type() const { return _type; }

    virtual std::string parse(const std::string& text) = 0;

private:
    ParserType _type = ParserType::UNDEFINED;
};

#endif //ASSISTX_TEXTPARSER_H
