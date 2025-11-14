#pragma once
#include "../pch.hpp"
#include "../token/token.hpp"
#include "../lex/lex.hpp"
#include "../ast/ast.hpp"
#include "../parse/parse.hpp"
#include "../utils/common.hpp"
#include "../interpret/interpret.hpp"
#include "../interpret/out/out.hpp"

class Tester
{
private:
    Lexer lex;
    Parser parse;
    Interpretter ip;

public:
    Tester() {}
    void test_lex(const std::string &, const std::string &);
    void test_parse(const std::string &, const std::string &);
    void test_interpret(const std::string &, const long long &);
    void test_error(const std::string &);
};