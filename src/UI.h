#pragma once

#include "Move.h"
#include "GameManager.h"

#include <curses.h>
#include <utility>
#include <string>
#include <list>

enum Color
{
    DEFAULT = 1,
    CELL_EMPTY_BLACK,
    CELL_EMPTY_WHITE,
    CELL_GREEN_BLACK,
    CELL_GREEN_WHITE,
    CELL_RED_BLACK,
    CELL_RED_WHITE
};

class UI
{
private:
    static UI* mInstance;
    UI();

    WINDOW* mPlayerSelectWindow = nullptr;
    WINDOW* mSearchMethodOptionsWindow = nullptr;
    WINDOW* mBoardWindow = nullptr;
    WINDOW* mInputWindow = nullptr;
    WINDOW* mLogWindow = nullptr;

    std::list<std::tuple<const bool, const Move, const int>> mLog;

    unsigned int pickMenuOption(WINDOW* win, const int& y, const int& x, const char** opts, const unsigned int& numOpts);
    void drawMenu(WINDOW* win, const int& y, const int& x, const char** opts, const unsigned int& numOpts, const unsigned int& selected);

    const char* getPlayerDisplayName(const bool& playerOne);
    int getPlayerDisplayAttributes(const bool& playerOne);
public:
    static UI* getInstance();
    virtual ~UI();

    void init();
    void mainMenu();
    void startGame();

    // window ops
    WINDOW* createWindow(const int& h, const int& w, const int& y, const int& x);
    void destroyWindow(WINDOW* win);
    void eraseWindow(WINDOW* win);

    // board ops
    void setCell(const int& y, const int& x, const int& val);

    // input ops
    unsigned int selectPlayer(const char** opts, const unsigned int& numOpts, const bool& playerOne);
    unsigned int selectSearchMethod(const char** opts, const unsigned int& numOpts, const bool& playerOne);
    std::string getMove(const bool& playerOne);
    void message(const std::string& m, const bool& pause);
    void outcome(const GameManager::Outcome& outcome);

    // log ops
    void log(const bool& playerOne, const Move& move, const int& value);
};
