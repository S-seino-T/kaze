#include "lex.hpp"

Lexer::Lexer()
{
    token_regex = "^";
    for (size_t i = 0; i < token_re_list.size(); ++i)
    {
        if (i > 0)
            token_regex += "|";
        token_regex += "(" + token_re_list[i].second + ")";
    }
}

std::vector<Token> Lexer::tokenize(const std::string &code)
{
    std::vector<Token> ret;
    std::regex re(token_regex);
    std::smatch m;
    std::string::const_iterator seach_start(code.cbegin());

    while (std::regex_search(seach_start, code.cend(), m, re))
    {
        bool matched = false;
        for (size_t i = 0; i < token_re_list.size(); ++i)
        {
            if (m[i + 1].matched)
            {
                TokenType kind = token_re_list[i].first;
                std::string value = m[i + 1].str();
                if (kind == TokenType::UNKNOWN)
                    throw LexicalException("Lexer internal error (Unknown Token)");
                if (kind != TokenType::WS)
                    ret.push_back({value, kind});
                matched = true;
                break;
            }
        }
        if (!matched)
            throw LexicalException("Lexer internal error (No Match)");

        seach_start = m.suffix().first;
    }
    return ret;
}