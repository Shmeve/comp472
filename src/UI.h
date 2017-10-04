#pragma once

#include "Move.h"

#include <curses.h>
#include <string>

enum Color
{
    DEFAULT = 1,
    CELL_EMPTY_BLACK,
    CELL_EMPTY_WHITE,
    CELL_P1_BLACK,
    CELL_P1_WHITE,
    CELL_P2_BLACK,
    CELL_P2_WHITE
};

class UI
{
private:
    static UI* mInstance;
    UI();

    WINDOW* mBoardWindow = nullptr;
    WINDOW* mInputWindow = nullptr;
    WINDOW* mLogWindow = nullptr;
public:
    static UI* getInstance();
    virtual ~UI();

    void init();

    // window ops
    WINDOW* createWindow(const int& h, const int& w, const int& y, const int& x);
    void destroyWindow(WINDOW* win);
    void eraseWindow(WINDOW* win);

    // board ops
    void setCell(const int& y, const int& x, const int& val);

    // input ops
    std::string getMove(const bool& playerOne);
    void message(const std::string& m, const bool& pause);

    // log ops
    void log(const int& player, const Move& move);
};
