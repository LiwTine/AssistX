#ifndef ASSISTX_ACTIONPARSER_H
#define ASSISTX_ACTIONPARSER_H

#include "parser/IParser.h"
#include "unordered_set"

class ActionParser : public IParser {
public:
    explicit ActionParser();

    std::string parse(const std::string& text, const std::string& result) override;
    ~ActionParser() noexcept override;
private:
    std::unordered_set<std::string> keywords;
};

#endif //ASSISTX_ACTIONPARSER_H
