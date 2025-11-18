#pragma once
#include "../pch.hpp"

enum class TokenType
{
    INT,
    LET,
    VARIABLE,
    EQUAL,
    SEMI,
    MINUS,
    PLUS,
    MULTIPLE,
    DIVIDE,
    MODULO,
    LPAREN,
    RPAREN,
    WILDCARD,
    WS,
    END_OF_FILE,
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