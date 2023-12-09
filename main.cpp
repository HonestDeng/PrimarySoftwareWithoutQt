#include <iostream>
#include <string>
#include <functional>
#include "dialog.h"
#include <vector>
#include "gtest/gtest.h"

using namespace std;

TEST(GETTOKEN, DEFINE1) {
    Dialog dialog;
    std::string command = "define Y = X;";
    vector<std::string> expect1 = {"define", "Y", "=", "X", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, ID, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE2) {
    Dialog dialog;
    std::string command = "define Y = 2 * X ^ 3;";
    vector<std::string> expect1 = {"define", "Y", "=", "2", "*", "X", "^", "3", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, NUMBER, MUL, ID, POWER, NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE3) {
    Dialog dialog;
    std::string command = "define Y = 2 * X;";
    vector<std::string> expect1 = {"define", "Y", "=", "2", "*", "X", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, NUMBER, MUL, ID, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE4) {
    Dialog dialog;
    std::string command = "define Y = X ^ 3;";
    vector<std::string> expect1 = {"define", "Y", "=", "X", "^", "3", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, ID, POWER, NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE5) {
    Dialog dialog;
    std::string command = "define Y = 2;";
    vector<std::string> expect1 = {"define", "Y", "=", "2", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE6) {
    Dialog dialog;
    std::string command = "define Y = 23*X^2 + 234*X + 2345*X^123 + X + 2;";
    vector<std::string> expect1 = {"define", "Y", "=", "23", "*", "X", "^", "2", "+", "234", "*", "X", "+", "2345", "*",
                                   "X", "^", "123", "+", "X", "+", "2", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, NUMBER, MUL, ID, POWER, NUMBER, PLUS, NUMBER, MUL, ID, PLUS, NUMBER,
                                 MUL, ID, POWER, NUMBER, PLUS, ID, PLUS, NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, SET) {
    Dialog dialog;
    std::string command = "set X[0] = 123; set X[123] = 998;";
    vector<std::string> expect1 = {"set", "X", "[", "0", "]", "=", "123", ";", "set", "X", "[", "123", "]", "=", "998",
                                   ";"};
    vector<TokenType> expect2 = {SET, ID, LPARAM, NUMBER, RPARAM, EQ, NUMBER, SEMI, SET, ID, LPARAM, NUMBER, RPARAM, EQ,
                                 NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, SHOW) {
    Dialog dialog;
    std::string command = "show;";
    vector<std::string> expect1 = {"show", ";"};
    vector<TokenType> expect2 = {SHOW, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, CLEAR) {
    Dialog dialog;
    std::string command = "clear;";
    vector<std::string> expect1 = {"clear", ";"};
    vector<TokenType> expect2 = {CLEAR, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, LIMIT) {
    Dialog dialog;
    std::string command = "limit 123, 1234;";
    vector<std::string> expect1 = {"limit", "123", ",", "1234", ";"};
    vector<TokenType> expect2 = {LIMIT, NUMBER, COMMA, NUMBER, SEMI};
    dialog.command = command;
    for (int i = 0; i < expect1.size(); i++) {
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(PARSE, LIMIT1) {
    Dialog dialog;
    std::string command = "limit 123, 1234;";
    dialog.parse(command);
    EXPECT_EQ(dialog.xmin, 123);
    EXPECT_EQ(dialog.xmax, 1234);
}

TEST(PARSE, LIMIT2) {
    Dialog dialog;
    std::string command = "limit -123, 1234;";
    dialog.parse(command);
    EXPECT_EQ(dialog.xmin, -123);
    EXPECT_EQ(dialog.xmax, 1234);
}

TEST(PARSE, LIMIT3) {
    Dialog dialog;
    std::string command = "limit -123, +1234;";
    dialog.parse(command);
    EXPECT_EQ(dialog.xmin, -123);
    EXPECT_EQ(dialog.xmax, 1234);
}

TEST(PARSE, SET1) {
    Dialog dialog;
    std::string command = "set X[0] = 1 at Y;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"][0], 1);
}

TEST(PARSE, SET2) {
    Dialog dialog;
    std::string command = "set X[123] = -1324 at Y;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"][123], -1324);
}

TEST(PARSE, DEFINE1) {
    Dialog dialog;
    std::string command = "define Y = 2*X^332;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][332], 2);
}

TEST(PARSE, DEFINE2) {
    Dialog dialog;
    std::string command = "define Y = -2*X^332;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][332], -2);
}

TEST(PARSE, DEFINE3) {
    Dialog dialog;
    std::string command = "define Y = X^332;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][332], 1);
}

TEST(PARSE, DEFINE4) {
    Dialog dialog;
    std::string command = "define Y = -X^332;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][332], -1);
}

TEST(PARSE, DEFINE5) {
    Dialog dialog;
    std::string command = "define Y = -X;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][1], -1);
}

TEST(PARSE, DEFINE6) {
    Dialog dialog;
    std::string command = "define Y = X;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][1], 1);
}

TEST(PARSE, DEFINE7) {
    Dialog dialog;
    std::string command = "define Y = 2;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][0], 2);
}

TEST(PARSE, DEFINE8) {
    Dialog dialog;
    std::string command = "define Y = -2;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 1);
    EXPECT_EQ(dialog.exps["Y"][0], -2);
}

TEST(PARSE, DEFINE9) {
    Dialog dialog;
    std::string command = "define Y = -2 + X^2 - 32*X^4 - 123*X^3 - X;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 5);
    EXPECT_EQ(dialog.exps["Y"][0], -2);
    EXPECT_EQ(dialog.exps["Y"][1], -1);
    EXPECT_EQ(dialog.exps["Y"][2], 1);
    EXPECT_EQ(dialog.exps["Y"][4], -32);
    EXPECT_EQ(dialog.exps["Y"][3], -123);
}

TEST(SYTHESIS, TEST1) {
    Dialog dialog;
    std::string command = "define Y = -2 -X + X^2 - 123*X^3 - 32*X^4;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"].size(), 5);
    EXPECT_EQ(dialog.exps["Y"][0], -2);
    EXPECT_EQ(dialog.exps["Y"][1], -1);
    EXPECT_EQ(dialog.exps["Y"][2], 1);
    EXPECT_EQ(dialog.exps["Y"][4], -32);
    EXPECT_EQ(dialog.exps["Y"][3], -123);

    command = "set X[0] = 4 at Y;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"][0], 4);

    command = "limit -12, 10";
    dialog.parse(command);
    EXPECT_EQ(dialog.xmin, -12);
    EXPECT_EQ(dialog.xmax, 10);

    command = "set X[5] = 6 at Y;";
    dialog.parse(command);
    EXPECT_EQ(dialog.exps["Y"][5], 6);
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
