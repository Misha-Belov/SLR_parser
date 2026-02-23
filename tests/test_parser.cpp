#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <string>
#include <vector>

#include "token.hpp"
#include "parser.hpp"

extern int yylex();
extern std::vector<Token> tokens;

bool run_parser(const std::string& input, bool expect_success) {
    char filename[] = "/tmp/slr_test_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        perror("mkstemp");
        return false;
    }
    FILE* tmp = fdopen(fd, "w");
    if (!tmp) {
        perror("fdopen");
        close(fd);
        return false;
    }
    fprintf(tmp, "%s", input.c_str());
    fclose(tmp);

    if (freopen(filename, "r", stdin) == nullptr) {
        perror("freopen");
        unlink(filename);
        return false;
    }
    unlink(filename);

    int stdout_fd = dup(1);
    FILE* tmp_out = tmpfile();
    int tmp_out_fd = fileno(tmp_out);
    dup2(tmp_out_fd, 1);

    tokens.clear();
    yylex();
    tokens.emplace_back(TokenType::END, "$");

    SLRParser parser;
    parser.parse(tokens);

    fflush(stdout);
    dup2(stdout_fd, 1);
    close(stdout_fd);

    fseek(tmp_out, 0, SEEK_SET);
    char buffer[1024];
    std::string output;
    while (fgets(buffer, sizeof(buffer), tmp_out)) {
        output += buffer;
    }
    fclose(tmp_out);

    bool has_accept = output.find("ACCEPT") != std::string::npos;
    bool has_error = output.find("Syntax error") != std::string::npos;

    if (expect_success)
        return has_accept && !has_error;
    else
        return has_error && !has_accept;
}

#define TEST(expr, expected) \
    do { \
        std::cout << "Testing: " << expr << " ... "; \
        if (run_parser(expr, expected)) \
            std::cout << "PASSED\n"; \
        else { \
            std::cout << "FAILED\n"; \
            failed++; \
        } \
    } while (0)

int main() {
    int failed = 0;

    // Корректные выражения
    TEST("a", true);
    TEST("123", true);
    TEST("a+b", true);
    TEST("a-b", true);
    TEST("a*b", true);
    TEST("a/b", true);
    TEST("(a+b)*c", true);
    TEST("a+b*c", true);
    TEST("(a)", true);
    TEST("((a))", true);
    TEST("a+b-c", true);
    TEST("a*b/c", true);
    TEST("a+b*c/d", true);
    TEST("(a+b)*(c-d)", true);
    TEST("a+b*c/d-e", true);

    // Некорректные выражения (ожидаем ошибку)
    TEST("a+", false);
    TEST("+a", false);
    TEST("a b", false);
    TEST("a+*b", false);
    TEST("(a+b", false);
    TEST("a+b)", false);
    TEST("a//b", false);
    TEST("()", false);
    TEST("a+(b*)c", false);

    std::cout << "\nTotal failed: " << failed << std::endl;
    return failed ? 1 : 0;
}