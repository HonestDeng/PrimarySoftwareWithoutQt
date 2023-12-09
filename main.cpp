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
    for(int i = 0; i < expect1.size(); i++){
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
    for(int i = 0; i < expect1.size(); i++){
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
    for(int i = 0; i < expect1.size(); i++){
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
    for(int i = 0; i < expect1.size(); i++){
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
    for(int i = 0; i < expect1.size(); i++){
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

TEST(GETTOKEN, DEFINE6) {
    Dialog dialog;
    std::string command = "define Y = 23*X^2 + 234*X + 2345*X^123 + X + 2;";
    vector<std::string> expect1 = {"define", "Y", "=", "23", "*", "X", "^", "2", "+", "234", "*", "X", "+", "2345", "*", "X", "^", "123", "+", "X", "+", "2", ";"};
    vector<TokenType> expect2 = {DEFINE, ID, EQ, NUMBER, MUL, ID, POWER, NUMBER, PLUS, NUMBER, MUL, ID, PLUS, NUMBER, MUL, ID, POWER, NUMBER, PLUS, ID, PLUS, NUMBER, SEMI};
    dialog.command = command;
    for(int i = 0; i < expect1.size(); i++){
        dialog.getToken();
        EXPECT_EQ(dialog.tokenString, expect1[i]);
        EXPECT_EQ(dialog.token, expect2[i]);
    }
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
