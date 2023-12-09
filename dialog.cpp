#include "dialog.h"
#include <iostream>

double Dialog::cal(double x, const std::string& id) {
    double res = 0;
    const auto& exp = exps[id];
    for (const auto &term: exp) {
        res += term.second * pow(x, term.first);
    }
    return res;
}

void Dialog::freshLine(const std::string &id) {
}

void Dialog::freshAll() {
    for (const auto &exp: exps) {
        freshLine(exp.first);
    }
}

bool Dialog::match(TokenType expect) {
    if (expect == token) {
        getToken();
        return true;
    }
    return false;
}

bool Dialog::parse(std::string &com) {
    command = com;
    ichar = 0;
    getToken();
    if (token == LIMIT) {
        std::string l, r;
        int lflag = 1, rflag = 1;
        if (!match(LIMIT)) {
            return false;
        }

        if (token == PLUS) {
            lflag = 1;
            match(PLUS);
        } else if (token == MINUS) {
            lflag = -1;
            match(MINUS);
        }
        l = tokenString;
        if (!match(NUMBER)) {
            return false;
        }

        if (!match(COMMA)) {
            return false;
        }

        if (token == PLUS) {
            rflag = 1;
            match(PLUS);
        } else if (token == MINUS) {
            rflag = -1;
            match(MINUS);
        }
        r = tokenString;
        if (!match(NUMBER)) {
            return false;
        }

        this->xmin = std::stod(l) * lflag;
        this->xmax = std::stod(r) * rflag;

    } else if (token == DEFINE) {
        if(!match(DEFINE)) {
            return false;
        }
        std::string id = tokenString;
        if(exps.count(id) > 0){
            // 如果这条线已经出现过了
            exps[id].clear();
        }
        if (!match(ID) || !match(EQ)) {
            return false;
        }
        while (token != SEMI) {
            int flag = 1;
            int index = 0;
            double correlation = 1;
            if (token == PLUS) {
                flag = 1;
                match(PLUS);
            } else if (token == MINUS) {
                flag = -1;
                match(MINUS);
            }
            // 这里一共会出现四种情况的项：
            // 1. 系数和幂数都出现了：Y = 2 * X ^ 3
            // 2. 系数出现，幂数默认为1，Y = 2 * X
            // 3. 系数出现，幂数默认为0，Y = 2
            // 4. 系数默认为1，Y = X ^ 3
            // 5. 系数和幂数都默认为1，Y = X
            if (token == NUMBER) { // 第1，2，3种情况
                correlation = std::stod(tokenString);  // 确定系数
                match(NUMBER);
                if (token == MUL) { // 第1，2种情况
                    if (!match(MUL) || !match(ID)) {
                        return false;
                    }
                    if (token == POWER) { // 第1种情况
                        match(POWER);
                        index = std::stoi(tokenString); // 确定阶数
                        if (!match(NUMBER)) {
                            return false;
                        }
                    } else {  // 第2种情况
                        index = 1;
                    }
                } else {  // 第3种情况
                    index = 0;
                }
            } else if (token == ID) {  // 第4，5种情况
                correlation = 1;
                match(ID);
                if (token == POWER) { // 第4种情况
                    match(POWER);
                    index = std::stoi(tokenString);
                    if (!match(NUMBER)) {
                        return false;
                    }
                } else {
                    index = 1;  // 第5种情况
                }
            }
            exps[id][index] = correlation * flag;
        }
    } else if (token == SET) { // set X[0] = 12;
        std::string index, correlation;
        int iflag = 1, cflag = 1;
        if (!match(SET) || !match(ID) || !match(LPARAM)) {
            return false;
        }
        if (token == PLUS) {
            iflag = 1;
            match(PLUS);
        } else if (token == MINUS) {
            iflag = -1;
            match(MINUS);
        }
        index = tokenString;
        if (!match(NUMBER) || !match(RPARAM)) {
            return false;
        }
        if (!match(EQ)) {
            return false;
        }

        if (token == PLUS) {
            cflag = 1;
            match(PLUS);
        } else if (token == MINUS) {
            cflag = -1;
            match(MINUS);
        }
        correlation = tokenString;
        if (!match(NUMBER)) {
            return false;
        }

        if (!match(AT)) {
            return false;
        }
        std::string id = tokenString;
        if (!match(ID)) {
            return false;
        }
        auto &exp = exps[id];
        exp[std::stoi(index) * iflag] = std::stod(correlation) * cflag;
    } else if (token == CLEAR) {  // clear;
        if (!match(CLEAR) || !match(AT)) {
            return false;
        }
        std::string id = tokenString;
        auto &exp = exps[id];
        exp.clear();
        freshLine(id);
    } else if (token == SHOW) { // show;
        for (const auto &exp: exps) {
            std::cout << "====== exp:" << exp.first << " ======" << std::endl;
            for (const auto &term: exp.second) {
                std::cout << std::to_string(term.second) << "*X^" << std::to_string(term.first) << std::endl;
            }
        }
    } else if (token == REFRESH) {
        freshAll();
    } else {
        return false;
    }
    return true;
}

void Dialog::error(const std::string &info) {
    std::cout << info << std::endl;
}

void Dialog::getToken() {
    tokenString = "";
    int state = 0;
    TokenType tokenType = ERROR;
    while (state != 5 && ichar <= command.length()) {
        char c;
        if (ichar < command.length()) {
            c = command[ichar++];
        } else {
            c = '\0';
        }
        switch (state) {
            case 0:
                if (c == '\t' || c == ' ') {
                    state = 0;
                } else if (isdigit(c)) {
                    tokenString += c;
                    state = 2;
                } else if (c == '=' || c == '+' || c == '-' || c == '*' || c == '^' || c == '[' || c == ']') {
                    state = 5;
                    tokenString += c;
                    switch (c) {
                        case '=':
                            tokenType = EQ;
                            break;
                        case '*':
                            tokenType = MUL;
                            break;
                        case '^':
                            tokenType = POWER;
                            break;
                        case '[':
                            tokenType = LPARAM;
                            break;
                        case ']':
                            tokenType = RPARAM;
                            break;
                        case '+':
                            tokenType = PLUS;
                            break;
                        case '-':
                            tokenType = MINUS;
                            break;
                        default:
                            tokenType = ERROR;
                            state = 5;
                    }
                } else if (c == ';') {
                    tokenType = SEMI;
                    state = 5;
                    tokenString += c;
                } else if (c == ',') {
                    tokenType = COMMA;
                    state = 5;
                    tokenString += c;
                } else if (isalpha(c)) {
                    state = 6;
                    tokenString += c;
                } else {
                    error("scaner: unknown token -> " + tokenString);
                    state = 5;
                    ichar--;
                    tokenType = ERROR;
                }
                break;
            case 2:
                if (isdigit(c)) {
                    state = 2;
                    tokenString += c;
                } else if (c == '.') {
                    state = 3;
                    tokenString += c;
                } else {
                    ichar--;
                    state = 5;
                    tokenType = NUMBER;
                }
                break;
            case 3:
                if (isdigit(c)) {
                    state = 4;
                    tokenString += c;
                } else {
                    error("scaner: unknown token -> " + tokenString);
                    ichar--;
                    tokenType = ERROR;
                    state = 5;
                }
                break;
            case 4:
                if (isdigit(c)) {
                    state = 4;
                    tokenString += c;
                } else {
                    state = 5;
                    ichar--;
                    tokenType = NUMBER;
                }
                break;
            case 6:
                if (isalpha(c)) {
                    state = 6;
                    tokenString += c;
                } else {
                    state = 5;
                    ichar--;
                    tokenType = ID;
                }
                break;
            default:
                error("scaner: unknown token ->" + tokenString);
                state = 5;
        }
    }
    if (tokenType == ID) {
        if (tokenString == "limit") {
            tokenType = LIMIT;
        } else if (tokenString == "define") {
            tokenType = DEFINE;
        } else if (tokenString == "set") {
            tokenType = SET;
        } else if (tokenString == "clear") {
            tokenType = CLEAR;
        } else if (tokenString == "show") {
            tokenType = SHOW;
        } else if (tokenString == "at") {
            tokenType = AT;
        } else if (tokenString == "refresh") {
            tokenType = REFRESH;
        }
    }
    token = tokenType;
}
