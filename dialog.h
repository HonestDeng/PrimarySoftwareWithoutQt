#ifndef DIALOG_H
#define DIALOG_H
#include <map>
#include <string>
class Dialog
{
private:
    double xmin = 0, xmax = 1;
    double step = 0.01;
    std::map<int, double> exp;
    typedef enum {NUMBER, ID, LPARAM, RPARAM, EQ, MUL, PLUS, MINUS, POWER, LIMIT, DEFINE, SET, CLEAR, SHOW, ERROR, SEMI, COMMA} TokenType;


    void getToken();
    TokenType token;
    std::string tokenString;
    std::string command;  // 输入的命令
    int ichar;  // 当前正在读取命令的第ichar个字符
    double cal(double x);
    void setLimit(double l, double r);
    bool parse(std::string& comm);
    void freshLine();
    static void error(const std::string&);
    bool match(TokenType);
};
#endif // DIALOG_H
