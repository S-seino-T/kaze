#include "parse.hpp"

const Token &Parser::peek() const
{
    if (pos < tokens.size())
    {
        return tokens[pos];
    }
    else
    {
        static Token t("EOF", TokenType::END_OF_FILE);
        return t;
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
        static Token t("EOF", TokenType::END_OF_FILE);
        return t;
    }
}

void Parser::expect_token(const Token &token)
{
    if (peek().type != token.type)
    {
        throw ParseException("Expected " + token.to_str() + ", got " + peek().to_str());
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

std::unique_ptr<Expr> Parser::identifier()
{
    std::string str = get_next_token().value;
    return std::make_unique<Var>(str);
}

std::unique_ptr<Expr> Parser::primary_expression()
{
    if (peek().type == TokenType::LPAREN)
    {
        return paren_expression();
    }
    else if (peek().type == TokenType::VARIABLE)
    {
        return identifier();
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
        expect_token(Token(")", TokenType::RPAREN));
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

std::unique_ptr<Expr> Parser::let_block()
{
    if (peek().type == TokenType::VARIABLE)
    {
        return identifier();
    }
    else
    {
        throw ParseException("Unexpected token in let_block: " + peek().to_str());
    }
}

std::unique_ptr<Expr> Parser::additive_expression()
{
    try
    {
        auto lexpr = unary_expression();
        while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS)
        {
            if (peek().type == TokenType::PLUS)
            {
                get_next_token();
                auto rexpr = literal();
                lexpr = std::make_unique<Add>(std::move(lexpr), std::move(rexpr));
            }
            else if (peek().type == TokenType::MINUS)
            {
                get_next_token();
                auto rexpr = literal();
                lexpr = std::make_unique<Sub>(std::move(lexpr), std::move(rexpr));
            }
        }
        return lexpr;
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
        return additive_expression();
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::variable_declaration()
{
    try
    {
        get_next_token();
        auto var = let_block();
        expect_token(Token("=", TokenType::EQUAL));
        auto ret = expression();
        expect_token(Token(";", TokenType::SEMI));
        return std::make_unique<Let>(std::move(var), std::move(ret));
    }
    catch (const ParseException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::expression_statement()
{
    try
    {
        auto ret = expression();
        expect_token(Token(";", TokenType::SEMI));
        return ret;
    }
    catch (const ProjectException &e)
    {
        throw e;
    }
}

std::unique_ptr<Expr> Parser::statement()
{
    try
    {
        if (peek().type == TokenType::LET)
        {
            return variable_declaration();
        }
        else
        {
            return expression_statement();
        }
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