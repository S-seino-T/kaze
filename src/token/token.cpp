#include "token.hpp"

Token::Token(std::string v, TokenType t) : value(v), type(t) {}

std::string Token::to_str() const
{
    switch (type)
    {
    case TokenType::INT:
        return "INT(" + value + ")";
    case TokenType::VARIABLE:
        return "VAR(" + value + ")";
    case TokenType::WILDCARD:
        return "WILDCARD";
    case TokenType::LET:
        return "LET";
    default:
        return value;
    }
}