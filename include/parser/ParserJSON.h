#ifndef ASSISTX_PARSERJSON_H
#define ASSISTX_PARSERJSON_H

#include "IParser.h"

class ParserJSON : public IParser {
public:
    explicit ParserJSON();

    std::string parse(const std::string& data) override;
    ~ParserJSON() noexcept override;
};

#endif //ASSISTX_PARSERJSON_H
