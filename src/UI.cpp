#include <iostream>
#include <cstdlib>

#include "UI.h"
#include "Board.h"

// Board window
const int BOARD_B = 1;
const int BOARD_H = BOARD_ROWS * 3 /*height*/ + BOARD_B * 2 /*border*/;
const int BOARD_W = BOARD_COLS * 3 /*height*/ + BOARD_B * 2 /*border*/;
const int BOARD_X = 0;
const int BOARD_Y = 0;

// Input window
const int INPUT_B = 1;
const int INPUT_H = 1 /*height*/ + INPUT_B * 2 /*border*/;
const int INPUT_W = BOARD_W;
const int INPUT_X = 0;
const int INPUT_Y = BOARD_H;

// Log window
const int LOG_B = 1;
const int LOG_H = BOARD_H + INPUT_H /*height*/;
const int LOG_W = 9 /*width*/ + LOG_B * 2 /*border*/;
const int LOG_X = BOARD_W;
const int LOG_Y = 0;

// Player window
const int PLAYER_B = 1;
const int PLAYER_H = BOARD_H + INPUT_H - 6;
const int PLAYER_W = BOARD_W + LOG_W;
const int PLAYER_X = 0;
const int PLAYER_Y = 6;

// Physical window
const int WINDOW_H = BOARD_H + INPUT_H;
const int WINDOW_W = BOARD_W + LOG_W;

UI* UI::mInstance = nullptr;

UI::UI() : mLog()
{
}

UI::~UI()
{
    if (mBoardWindow != nullptr) {
        destroyWindow(mBoardWindow);
    }

    if (mInputWindow != nullptr) {
        destroyWindow(mInputWindow);
    }

    if (mLogWindow != nullptr) {
        destroyWindow(mLogWindow);
    }
}

UI* UI::getInstance()
{
    if (mInstance == nullptr) {
        mInstance = new UI();
    }

    return mInstance;
}

void UI::init()
{
#if defined(__unix__) || defined(__APPLE__)
    printf("\033]2;Armadillo\a");
#elif _WIN32 && !defined(__CYGWIN__)
    {
        PDC_set_title("Armadillo");
        char* cmd = new char[100];
        sprintf(cmd, "mode con cols=%d lines=%d", WINDOW_W, WINDOW_H);
        system(cmd);
        delete[] cmd;
    }
#endif

    // init curses window
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();

    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
    }

    // enable key inputs
    keypad(stdscr, true);
    //mousemask(BUTTON1_PRESSED, nullptr);

    // init color presets
    start_color();
    init_pair(Color::DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(Color::CELL_EMPTY_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(Color::CELL_EMPTY_WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(Color::CELL_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(Color::CELL_GREEN_WHITE, COLOR_GREEN, COLOR_WHITE);
    init_pair(Color::CELL_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(Color::CELL_RED_WHITE, COLOR_RED, COLOR_WHITE);

    refresh();
}

void UI::mainMenu()
{
    const char logo[][30] = {R"(   ___                       )",
                             R"(  / _ )___  ___  ___ ___ ___ )",
                             R"( / _  / _ \/ _ \/_ // -_) -_))",
                             R"(/____/\___/_//_//__/\__/\__/ )"};

    int padding = (WINDOW_W - 30) / 2;
    move(1, 0);
    attron(A_BOLD);
    for (auto& line : logo) {
        mvaddstr(getcury(stdscr), padding + 1, line);
        move(getcury(stdscr) + 1, getcurx(stdscr));
    }
    attroff(A_BOLD);

    refresh();
}

void UI::startGame()
{
    destroyWindow(mPlayerSelectWindow);
    mPlayerSelectWindow = nullptr;

    /*
     * board window init
     */

    mBoardWindow = createWindow(BOARD_H, BOARD_W, BOARD_Y, BOARD_X);

    // draw row marks
    for (int y = 0; y < BOARD_ROWS; ++y) {
        const chtype ch = ('A' + y) | A_BOLD;
        mvwaddch(mBoardWindow, BOARD_B + y * 3 + 1, 0, ch);
        mvwaddch(mBoardWindow, BOARD_B + y * 3 + 1, BOARD_W - 1, ch);
    }

    // draw col marks
    for (int x = 0; x < BOARD_COLS; ++x) {
        const chtype ch = ('1' + x) | A_BOLD;
        mvwaddch(mBoardWindow, 0, BOARD_B + x * 3 + 1, ch);
        mvwaddch(mBoardWindow, BOARD_H - 1, BOARD_B + x * 3 + 1, ch);
    }

    /*
     * input window init
     */

    mInputWindow = createWindow(INPUT_H, INPUT_W, INPUT_Y, INPUT_X);

    mvwaddstr(mInputWindow, 0, 1, "Command");
    wrefresh(mInputWindow);

    /*
     * log window init
     */

    mLogWindow = createWindow(LOG_H, LOG_W, LOG_Y, LOG_X);

    mvwaddstr(mLogWindow, 0, 1, "Log");
    wmove(mLogWindow, LOG_B, LOG_B);
    wrefresh(mLogWindow);
}

WINDOW* UI::createWindow(const int& h, const int& w, const int& y, const int& x)
{
    WINDOW* win = newwin(h, w, y, x);
    eraseWindow(win);

    return win;
}

void UI::destroyWindow(WINDOW* win)
{
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}

void UI::eraseWindow(WINDOW* win)
{
    werase(win);
    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    wrefresh(win);
}

void UI::setCell(const int& y, const int& x, const int& val)
{
    int color;
    bool isBlack = !((x % 2 == 0) ^ (y % 2 == 0));

    switch (val) {
        case 0:
        default:
            color = isBlack ? Color::CELL_EMPTY_BLACK : Color::CELL_EMPTY_WHITE;
            break;
        case 1:
            color = isBlack ? Color::CELL_GREEN_BLACK : Color::CELL_GREEN_WHITE;
            break;
        case 2:
            color = isBlack ? Color::CELL_RED_BLACK : Color::CELL_RED_WHITE;
            break;
    }

    /*
     * Print the piece, row by row
     */

    const chtype piece[] = {ACS_ULCORNER, ACS_HLINE, ACS_URCORNER,
                            ACS_VLINE,    ACS_BLOCK, ACS_VLINE,
                            ACS_LLCORNER, ACS_HLINE, ACS_LRCORNER};

    int dy = y * 3 + BOARD_B;
    int dx = x * 3 + BOARD_B;

    for (int i = 0; i < 3 * 3; ++i) {
        mvwaddch(mBoardWindow, dy + i / 3, dx + i % 3, (val == 0 ? ' ' : piece[i]) | COLOR_PAIR(color));
    }

    wrefresh(mBoardWindow);
}

unsigned int UI::selectPlayer(const char** opts, const unsigned int& numOpts, const bool& playerOne)
{
    mPlayerSelectWindow = createWindow(PLAYER_H, PLAYER_W, PLAYER_Y, PLAYER_X);

    const char* playerName = getPlayerDisplayName(playerOne);
    const int color = playerOne ? Color::CELL_GREEN_BLACK : Color::CELL_RED_BLACK;

    mvwprintw(mPlayerSelectWindow, 0, 1, "Select a %s player", playerName);
    wattron(mPlayerSelectWindow, COLOR_PAIR(color));
    mvwaddstr(mPlayerSelectWindow, 0, 10, playerName);
    wattroff(mPlayerSelectWindow, COLOR_PAIR(color));

    return pickMenuOption(mPlayerSelectWindow, 1, 2, opts, numOpts);
}

std::string UI::getMove(const bool& playerOne)
{
    std::string move(4, ' ');

    eraseWindow(mInputWindow);
    mvwaddstr(mInputWindow, 0, 1, "Command");
    mvwprintw(mInputWindow, INPUT_B, INPUT_B, "P%i's move: ", 2 - playerOne);
    wrefresh(mInputWindow);

    int i = 0;

    while (i < 4) {
        bool rowMode = i % 2 == 0;
        bool accepted = false;
        int ch = wgetch(mInputWindow);

        if (i > 0 && (ch == KEY_BACKSPACE || ch == 127 || ch == 8)) {
            mvwaddch(mInputWindow, getcury(mInputWindow), getcurx(mInputWindow) - 1 - (i == 2), ' ');
            wmove(mInputWindow, getcury(mInputWindow), getcurx(mInputWindow) - 1);
            --i;
        } else if (rowMode && ((ch >= 'a' && ch < 'a' + BOARD_ROWS) || (ch >= 'A' && ch < 'A' + BOARD_ROWS))) {
            ch = toupper(ch);
            accepted = true;
        } else if (!rowMode && (ch >= '1' && ch < '1' + BOARD_COLS)) {
            accepted = true;
        }

        if (accepted) {
            move[i] = static_cast<char>(ch);
            waddch(mInputWindow, static_cast<const chtype>(ch));

            if (i == 1) {
                waddch(mInputWindow, ' ');
            }

            wrefresh(mInputWindow);
            ++i;
        }
    }

    waddch(mInputWindow, ' ');

    return move;
}

void UI::message(const std::string& m, const bool& pause)
{
    eraseWindow(mInputWindow);
    mvwaddstr(mInputWindow, INPUT_B, INPUT_B, m.c_str());

    if (pause) {
        wgetch(mInputWindow);
    }
}

void UI::log(const int& player, const Move& move)
{
    // add new log entry to front
    mLog.emplace_front(player, move);

    // pop back to maintain size
    if (mLog.size() > LOG_H - 2 * LOG_B) {
        mLog.pop_back();
    }

    // redraw the log from the top
    wmove(mLogWindow, LOG_B, LOG_B);
    wstandout(mLogWindow);

    for (auto& it : mLog) {
        wprintw(mLogWindow, "P%i: %c%c %c%c",
                it.first,
                'A' + it.second.mStartPos / BOARD_COLS, '1' + it.second.mStartPos % BOARD_COLS,
                'A' + it.second.mEndPos / BOARD_COLS, '1' + it.second.mEndPos % BOARD_COLS);
        wstandend(mLogWindow);
        wmove(mLogWindow, getcury(mLogWindow) + 1, LOG_B);
    }

    wrefresh(mLogWindow);
}

unsigned int UI::pickMenuOption(WINDOW* win, const int& y, const int& x, const char** opts, const unsigned int& numOpts)
{
    unsigned int selected = 0;

    drawMenu(win, y, x, opts, numOpts, selected);

    keypad(win, true);

    while (true) {
        bool done = false;

        switch (wgetch(win)) {
            case KEY_DOWN:
                if (selected < numOpts - 1) {
                    ++selected;
                } else {
                    selected = 0; // wraparound
                }
                break;
            case KEY_UP:
                if (selected > 0) {
                    --selected;
                } else {
                    selected = numOpts - 1; // wraparound
                }
                break;
            case KEY_ENTER:
            case 10:
                done = true;
                break;
            default:
                break;
        }

        drawMenu(win, y, x, opts, numOpts, selected);

        if (done) {
            break;
        }
    }

    return selected;
}

void UI::drawMenu(WINDOW* win, const int& y, const int& x, const char** opts, const unsigned int& numOpts, const unsigned int& selected)
{
    // print all available options
    for (int i = 0; i < numOpts; ++i) {
        mvwprintw(win, y + i, x, opts[i]);
    }

    // highlight selected option
    wstandout(win);
    mvwprintw(win, y + selected, x, opts[selected]);
    wstandend(win);

    wrefresh(win);
}

const char* UI::getPlayerDisplayName(const bool& playerOne)
{
    if (playerOne) {
        return "GREEN";
    }

    return "RED";
}
