#include "parser/ParserJSON.h"
#include <nlohmann/json.hpp>

ParserJSON::ParserJSON()
    : IParser( ParserType::JSON )
{
}

std::string ParserJSON::parse(const std::string& text, const std::string& result) {
    nlohmann::json jsonData = nlohmann::json::parse(text);
    std::string data;

    if (jsonData.contains("text")) {
        data = jsonData["text"];
    }
    return data;
}

ParserJSON::~ParserJSON() noexcept = default;
