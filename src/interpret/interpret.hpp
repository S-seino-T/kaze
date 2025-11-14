#pragma once
#include "../pch.hpp"
#include "../utils/common.hpp"
#include "../ast/ast.hpp"
#include "out/out.hpp"

class Interpretter
{
private:
public:
    Interpretter() {}
    Output interpret(std::unique_ptr<Expr>);
};