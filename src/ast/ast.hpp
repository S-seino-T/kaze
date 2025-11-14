#pragma once
#include "../pch.hpp"
#include "../utils/common.hpp"
#include "../interpret/out/out.hpp"

class Expr
{
public:
    virtual std::string pp() const = 0;
    virtual ~Expr() = default;
    virtual Output interpret() const = 0;
};

class Int : public Expr
{
private:
    long long value;

public:
    Int(long long v) : value(v) {}
    std::string pp() const override;
    Output interpret() const override;
};

// class Var : public Expr
// {
// private:
//     std::string variable;

// public:
//     Var(std::string v) : variable(v) {}
//     std::string pp() const override;
//     Output interpret() const override;
// };

// class WildCard : public Expr
// {
// public:
//     WildCard() {}
//     std::string pp() const override;
//     Output interpret() const override;
// };

class Neg : public Expr
{
private:
    std::unique_ptr<Expr> value;

public:
    Neg(std::unique_ptr<Expr> v) : value(std::move(v)) {}
    std::string pp() const override;
    Output interpret() const override;
};

class Paren : public Expr
{
private:
    std::unique_ptr<Expr> value;

public:
    Paren(std::unique_ptr<Expr> v) : value(std::move(v)) {}
    std::string pp() const override;
    Output interpret() const override;
};
