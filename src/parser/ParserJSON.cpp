#include "parser/ParserJSON.h"
#include <nlohmann/json.hpp>

ParserJSON::ParserJSON()
    : IParser( ParserType::JSON )
{
}

std::string ParserJSON::parse(const std::string &data) {
    nlohmann::json jsonData = nlohmann::json::parse(data);

    // Предположим, что текст находится в ключе "text"
    if (jsonData.contains("text")) {
        std::string text = jsonData["text"];
    }
    return data;
}

ParserJSON::~ParserJSON() noexcept = default;
