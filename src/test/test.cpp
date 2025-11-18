#include "test.hpp"

void Tester::test_lex(const std::string &ex, const std::string &ac)
{
    try
    {
        std::vector<Token> ex_tokens = lex.tokenize(ex);
        std::string expected = "";

        for (size_t i = 0; i < ex_tokens.size(); ++i)
        {
            if (i > 0 && i <= ex_tokens.size())
                expected += ", ";
            expected += ex_tokens[i].to_str();
        }
        if (expected == ac)
        {
            std::cout << "Success!" << std::endl;
        }
        else
        {
            std::cout << "Failure..." << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << ac << std::endl;
            std::cout << "But Actual:" << std::endl;
            std::cout << expected << std::endl;
        }
    }
    catch (const ProjectException &e)
    {
        std::cout << "Failure..." << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void Tester::test_parse(const std::string &ex, const std::string &ac)
{
    // std::vector<Token> ex_tokens = lex.tokenize(ex);
    try
    {
        auto expr = parse.parse(lex.tokenize(ex));
        std::string expected = expr->pp();

        if (expected == ac)
        {
            std::cout << "Success!" << std::endl;
        }
        else
        {
            std::cout << "Failure..." << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << ac << std::endl;
            std::cout << "But Actual:" << std::endl;
            std::cout << expected << std::endl;
        }
    }
    catch (const ProjectException &e)
    {
        std::cout << "Failure..." << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void Tester::test_interpret(const std::string &ex, const long long &ac)
{
    try
    {
        auto output = ip.interpret(parse.parse(lex.tokenize(ex)));
        if (output.output == ac)
        {
            std::cout << "Success!" << std::endl;
        }
        else
        {
            std::cout << "Failure..." << std::endl;
            std::cout << "Expected:" << std::endl;
            std::cout << ac << std::endl;
            std::cout << "But Actual:" << std::endl;
            std::cout << output.output << std::endl;
        }
    }
    catch (const ProjectException &e)
    {
        std::cout << "Failure..." << std::endl;
        std::cerr << e.what() << '\n';
    }
}

void Tester::test_error(const std::string &ex)
{
    long long expected;
    try
    {
        auto tried = ip.interpret(parse.parse(lex.tokenize(ex)));
        expected = tried.output;
    }
    catch (const ProjectException &e)
    {
        std::cout << "Success!" << std::endl;
        std::cout << e.what() << std::endl;
        return;
    }
    std::cout << "Failure..." << std::endl;
    std::cout << "Expected to failure." << std::endl;
    std::cout << "But Actual:" << std::endl;
    std::cout << expected << std::endl;
}