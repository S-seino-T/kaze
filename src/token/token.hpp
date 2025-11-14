#pragma once
#include "../pch.hpp"

enum class TokenType
{
    INT,
    VARIABLE,
    MINUS,
    PLUS,
    LPAREN,
    RPAREN,
    WILDCARD,
    WS,
    UNKNOWN,
};

class Token
{

public:
    std::string value;
    TokenType type;
    Token(std::string, TokenType);
    std::string to_str() const;
};