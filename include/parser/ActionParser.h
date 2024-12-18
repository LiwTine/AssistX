#ifndef ASSISTX_ACTIONPARSER_H
#define ASSISTX_ACTIONPARSER_H

#include "parser/IParser.h"

class ActionParser : public TextParser {
public:
    std::string parse(const std::string& text) override;
    ~ActionParser() noexcept override;
};

#endif //ASSISTX_ACTIONPARSER_H
