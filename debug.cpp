#include "pch.hpp"
#include "test/test.hpp"

int main()
{
    Tester t;

    // Test 1 Lexer
    std::cout << std::endl;
    std::cout << "## Lex Test." << std::endl;
    t.test_lex("2;", "INT(2), ;");
    t.test_lex("-1", "-, INT(1)");
    t.test_lex("1+2", "INT(1), +, INT(2)");
    t.test_lex("1+2+3+4+5", "INT(1), +, INT(2), +, INT(3), +, INT(4), +, INT(5)");
    t.test_lex("1+(2+3)", "INT(1), +, (, INT(2), +, INT(3), )");
    t.test_lex("- - 1", "-, -, INT(1)");
    t.test_lex("my_var", "VAR(my_var)");
    t.test_lex("-(x+1)", "-, (, VAR(x), +, INT(1), )");
    t.test_lex("_ + 1", "WILDCARD, +, INT(1)");
    t.test_lex("1 * 1", "INT(1), *, INT(1)");
    t.test_lex("2 / 1", "INT(2), /, INT(1)");
    t.test_lex("3 % 2", "INT(3), %, INT(2)");
    t.test_lex("let x = 3;", "LET, VAR(x), =, INT(3), ;");

    // Test 2 Parser
    std::cout
        << std::endl;
    std::cout << "## Parse Test." << std::endl;
    t.test_parse("1;", "1");
    t.test_parse("-1;", "(NEG 1)");
    t.test_parse("-23;", "(NEG 23)");
    t.test_parse("-(-(-1));", "(NEG (PAREN (NEG (PAREN (NEG 1)))))");
    t.test_parse("9223372036854775807;", "9223372036854775807");
    t.test_parse("-9223372036854775807;", "(NEG 9223372036854775807)");
    t.test_parse("1+2+3+4+5;", "(ADD (ADD (ADD (ADD 1 2) 3) 4) 5)");
    t.test_parse("-1+2-3+4-5;", "(SUB (ADD (SUB (ADD (NEG 1) 2) 3) 4) 5)");

    // Test 3 Interpretter
    std::cout << std::endl;
    std::cout << "## Interpret Test." << std::endl;
    t.test_interpret("2;", 2ll);
    t.test_interpret("-(2);", -2ll);
    t.test_interpret("-(-(-(-42)));", 42ll);
    t.test_interpret("-9223372036854775807;", -9223372036854775807ll);
    t.test_interpret("1+2+3+4+5;", 15ll);
    t.test_interpret("(1+2)-3;", 0ll);
    t.test_interpret("-1+2-3+4-5;", -3ll);
    t.test_interpret("-9223372036854775807-1;", -9223372036854775807ll - 1ll);

    // Test Error case
    std::cout
        << std::endl;
    std::cout << "## Error Test." << std::endl;
    t.test_error("2 @ 3;");
    t.test_error("- - - 3;");
    t.test_error("--3;");
    t.test_error("1+-2;");
    t.test_error("9223372036854775808;");
    t.test_error("9223372036854775807 + 1;");
    t.test_error("-9223372036854775807 - 2;");

    t.test_error("1+(2+3);");
    // t.test_error("-(-(-9223372036854775807))");
    return 0;
}