#ifndef ASSISTX_PARSERJSON_H
#define ASSISTX_PARSERJSON_H

#include "IParser.h"

class ParserJSON : public TextParser{
public:
    std::string parse(const std::string& text) override;
    ~ParserJSON() noexcept override;
};

#endif //ASSISTX_PARSERJSON_H
