#include "parser/ActionParser.h"
#include <sstream>
#include <algorithm>

ActionParser::ActionParser()
    : IParser( ParserType::ACTION )
{
    keywords = {"блядь", "как дела", "привет", "какая погода"};
}
// CHATGPT быстро склепал функцию, что бы проверить парсера и передачу данных

// Метод для поиска ключевых слов и фраз в тексте
std::string ActionParser::parse(const std::string& text, const std::string& result) {
    std::string lowerText = text;
    std::vector<std::string> foundKeywords;

    // Приводим весь текст к нижнему регистру
    std::transform(lowerText.begin(), lowerText.end(), lowerText.begin(), ::tolower);

    // Проверяем каждое ключевое слово или фразу на наличие в тексте
    for (const auto& keyword : keywords) {
        if (lowerText.find(keyword) != std::string::npos) {
            foundKeywords.push_back(keyword);
        }
    }

    // Формируем результат в строку
    if (foundKeywords.empty()) {
        return "No keywords found";
    } else {
        std::string result_1 = "Found keywords: ";
        for (const auto& keyword : foundKeywords) {
            result_1 += "\"" + keyword + "\" ";
        }
        return result_1;
    }
}

ActionParser::~ActionParser() noexcept = default;