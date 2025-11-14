#pragma once
#include "../pch.hpp"
#include "../utils/common.hpp"
#include "../token/token.hpp"

class Lexer
{
private:
    const std::vector<std::pair<TokenType, std::string>> token_re_list = {
        {TokenType::WILDCARD, "_"},
        {TokenType::VARIABLE, "[a-zA-Z_][a-zA-Z0-9_]*"},
        {TokenType::INT, "[0-9]+"},
        {TokenType::LPAREN, "\\("},
        {TokenType::RPAREN, "\\)"},
        {TokenType::PLUS, "\\+"},
        {TokenType::MINUS, "-"},
        {TokenType::WS, "\\s+"},
        {TokenType::UNKNOWN, ".+"},
    };

    std::string token_regex;

public:
    Lexer();
    std::vector<Token> tokenize(const std::string &);
};
