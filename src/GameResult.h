#ifndef GAMERESULT_H
#define GAMERESULT_H

#include <string>
#include <chrono>

class GameResult
{
    public:
    GameResult(int p1, int p2, std::string n1, std::string n2, int d, int m, int y) : playerOneScore(p1), playerTwoScore(p2), playerOneName(n1), playerTwoName(n2), day(d), month(m), year(y){};
    int playerOneScore;
    int playerTwoScore;
    std::string playerOneName;
    std::string playerTwoName;
    int day,month,year;
};

#endif