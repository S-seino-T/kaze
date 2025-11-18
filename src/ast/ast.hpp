#pragma once
#include "../pch.hpp"
#include "../utils/common.hpp"
#include "../interpret/out/out.hpp"

class Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;

public:
    virtual std::string pp() const = 0;
    virtual ~Expr() = default;
    virtual Conf interpret(Conf c) const = 0;
};

class Int : public Expr
{
private:
    long long value;
    using Conf = std::unique_ptr<Config<Output>>;

public:
    Int(long long v) : value(v) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

class Var : public Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;
    std::string variable;
    bool defining;

public:
    std::string get_var() const { return variable; }
    Var(std::string v, bool b = false) : variable(v), defining(b) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

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
    using Conf = std::unique_ptr<Config<Output>>;
    std::unique_ptr<Expr> value;

public:
    Neg(std::unique_ptr<Expr> v) : value(std::move(v)) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

class Paren : public Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;
    std::unique_ptr<Expr> value;

public:
    Paren(std::unique_ptr<Expr> v) : value(std::move(v)) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

class Add : public Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;
    std::unique_ptr<Expr> lvalue;
    std::unique_ptr<Expr> rvalue;

public:
    Add(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : lvalue(std::move(l)), rvalue(std::move(r)) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

class Sub : public Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;
    std::unique_ptr<Expr> lvalue;
    std::unique_ptr<Expr> rvalue;

public:
    Sub(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : lvalue(std::move(l)), rvalue(std::move(r)) {}
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

class Let : public Expr
{
private:
    using Conf = std::unique_ptr<Config<Output>>;
    std::unique_ptr<Expr> variable;
    std::unique_ptr<Expr> expr;

public:
    Let(std::unique_ptr<Expr> v, std::unique_ptr<Expr> e) : variable(std::move(v)), expr(std::move(e)) {};
    std::string pp() const override;
    Conf interpret(Conf c) const override;
};

// class Mul : public Expr
// {
// private:
//     std::unique_ptr<Expr> lvalue;
//     std::unique_ptr<Expr> rvalue;

// public:
//     Mul(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : lvalue(std::move(l)), rvalue(std::move(r)) {}
//     std::string pp() const override;
//     Output interpret() const override;
// };

// class Div : public Expr
// {
// private:
//     std::unique_ptr<Expr> lvalue;
//     std::unique_ptr<Expr> rvalue;

// public:
//     Div(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : lvalue(std::move(l)), rvalue(std::move(r)) {}
//     std::string pp() const override;
//     Output interpret() const override;
// };

// class Mod : public Expr
// {
// private:
//     std::unique_ptr<Expr> lvalue;
//     std::unique_ptr<Expr> rvalue;

// public:
//     Mod(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : lvalue(std::move(l)), rvalue(std::move(r)) {}
//     std::string pp() const override;
//     Output interpret() const override;
// };