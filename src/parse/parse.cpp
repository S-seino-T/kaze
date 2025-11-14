#include "parse.hpp"

const Token &Parser::peek() const
{
    if (pos < tokens.size())
    {
        return tokens[pos];
    }
    else
    {
        throw ParseException("Unexpected last token.");
    }
}

const Token &Parser::get_next_token()
{
    if (pos < tokens.size())
    {
        return tokens[pos++];
    }
    else
    {
        throw ParseException("Unexpected last token.");
    }
}

void Parser::expect_token(const TokenType &kind)
{
    if (peek().type != kind)
    {
        throw ParseException("Expected " + Token("", kind).to_str() + ", got " + peek().to_str());
    }
    get_next_token();
}

std::unique_ptr<Expr> Parser::integer_literal()
{
    try
    {
        long long v = std::stoll(get_next_token().value);
        return std::make_unique<Int>(v);
    }
    catch (const std::out_of_range &e)
    {
        throw ParseException("Value out of range for 64-bit Int.");
    }
    catch (const std::exception &ee)
    {
        throw ParseException("Unexpected error in integer_literal.");
    }
}

std::unique_ptr<Expr> Parser::literal()
{
    if (peek().type == TokenType::INT)
        return integer_literal();
    throw ParseException("Unexpected token in literal: " + peek().to_str());
}

std::unique_ptr<Expr> Parser::primary_expression()
{
    if (peek().type == TokenType::LPAREN)
    {
        return paren_expression();
    }
    else
    {
        return literal();
    }
    throw ParseException("Unexpected token in primary_expression: " + peek().to_str());
}

std::unique_ptr<Expr> Parser::paren_expression()
{
    get_next_token();
    auto ex = expression();
    try
    {
        expect_token(TokenType::RPAREN);
    }
    catch (const ParseException &e)
    {
        throw e;
    }

    return std::make_unique<Paren>(std::move(ex));
}

std::unique_ptr<Expr> Parser::call_access_expression()
{
    try
    {
        return primary_expression(); /* code */
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::unary_expression()
{
    try
    {
        if (peek().type == TokenType::MINUS)
        {
            get_next_token();
            auto ex = call_access_expression();
            return std::make_unique<Neg>(std::move(ex));
        }
        else
        {
            return call_access_expression();
        }
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::expression()
{
    try
    {
        return unary_expression();
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::statement()
{
    try
    {
        return expression();
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::program()
{
    try
    {
        return statement();
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::parse(const std::vector<Token> &t)
{
    this->tokens = t;
    this->pos = 0;

    try
    {
        return program();
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}