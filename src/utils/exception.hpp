#pragma once
#include "../pch.hpp"

class ProjectException
{
private:
    std::string msg;

public:
    ProjectException(std::string s) : msg(s) {}
    std::string what() const { return msg; }
};

class LexicalException : public ProjectException
{
public:
    LexicalException(std::string s) : ProjectException(s) {}
};

class ParseException : public ProjectException
{
public:
    ParseException(std::string s) : ProjectException(s) {}
};

class InterpretException : public ProjectException
{
public:
    InterpretException(std::string s) : ProjectException(s) {}
};

class VariableException : public ProjectException
{
public:
    VariableException(std::string s) : ProjectException(s) {}
};

class FatalException : public ProjectException
{
public:
    FatalException(std::string s) : ProjectException(s) {}
};