#ifndef DIALOG_H
#define DIALOG_H
#include <map>
#include <string>
#include <vector>

typedef enum {NUMBER, ID, LPARAM, RPARAM, EQ, MUL, PLUS, MINUS, POWER, LIMIT, DEFINE, SET, CLEAR, SHOW, AT, ERROR, SEMI, COMMA, REFRESH} TokenType;
class Dialog
{
public:
    double xmin = 0, xmax = 1;
    double step = 0.01;
    void getToken();
    TokenType token;
    std::string tokenString;
    std::string command;  // 输入的命令
    int ichar = 0;  // 当前正在读取命令的第ichar个字符
    double cal(double x, const std::string& id);
    bool parse(std::string& comm);
    void freshLine(const std::string&);
    void freshAll();
    static void error(const std::string&);
    bool match(TokenType);

    std::map<std::string, std::map<int, double> > exps;
};
#endif // DIALOG_H
