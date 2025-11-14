#pragma once
#include "../pch.hpp"
#include "../lex/lex.hpp"
#include "../token/token.hpp"
#include "../ast/ast.hpp"
#include "../utils/common.hpp"

class Parser
{
private:
    size_t pos = 0;
    std::vector<Token> tokens;

    const Token &peek() const;
    const Token &get_next_token();
    void expect_token(const TokenType &);

    std::unique_ptr<Expr> integer_literal();

    std::unique_ptr<Expr> literal();

    std::unique_ptr<Expr> primary_expression();
    std::unique_ptr<Expr> paren_expression();

    std::unique_ptr<Expr> call_access_expression();

    std::unique_ptr<Expr> unary_expression();

    std::unique_ptr<Expr> expression();

    std::unique_ptr<Expr> statement();

    std::unique_ptr<Expr> program();

public:
    Parser() {}
    std::unique_ptr<Expr> parse(const std::vector<Token> &);
};