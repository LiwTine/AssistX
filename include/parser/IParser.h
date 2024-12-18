#ifndef ASSISTX_TEXTPARSER_H
#define ASSISTX_TEXTPARSER_H

#include <string>

class TextParser {
public:
    virtual ~TextParser() = default;
    virtual std::string parse(const std::string& text) = 0;
};

#endif //ASSISTX_TEXTPARSER_H
