#include <iostream>

#include "UI.h"
#include "Board.h"

const int BOARD_B = 1;
const int BOARD_H = BOARD_ROWS * 3 /*height*/ + BOARD_B * 2 /*border*/;
const int BOARD_W = BOARD_COLS * 3 /*height*/ + BOARD_B * 2 /*border*/;
const int BOARD_X = 0;
const int BOARD_Y = 0;

const int INPUT_B = 1;
const int INPUT_H = 1 /*height*/ + INPUT_B * 2 /*border*/;
const int INPUT_W = BOARD_W;
const int INPUT_X = 0;
const int INPUT_Y = BOARD_H;

UI* UI::mInstance = nullptr;

UI::UI()
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
    init_pair(Color::CELL_P1_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(Color::CELL_P1_WHITE, COLOR_RED, COLOR_WHITE);
    init_pair(Color::CELL_P2_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(Color::CELL_P2_WHITE, COLOR_GREEN, COLOR_WHITE);

    refresh();

    mBoardWindow = createWindow(BOARD_H, BOARD_W, BOARD_Y, BOARD_X);
    mInputWindow = createWindow(INPUT_H, INPUT_W, INPUT_Y, INPUT_X);

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

    //keypad(mBoardWindow, true);
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
            color = isBlack ? Color::CELL_P1_BLACK : Color::CELL_P1_WHITE;
            break;
        case 2:
            color = isBlack ? Color::CELL_P2_BLACK : Color::CELL_P2_WHITE;
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

std::string UI::getMove(const bool& playerOne)
{
    std::string move;

    eraseWindow(mInputWindow);
    mvwprintw(mInputWindow, INPUT_B, INPUT_B, "P%i's move: ", 2 - playerOne);
    wrefresh(mInputWindow);

    bool rowMode = true;
    int i = 0;

    while (i < 4) {
        bool accepted = false;
        int ch = wgetch(mInputWindow);

        if (rowMode && ((ch >= 'a' && ch <= 'a' + BOARD_ROWS) || (ch >= 'A' && ch <= 'A' + BOARD_ROWS))) {
            ch = toupper(ch);
            accepted = true;
        } else if (!rowMode && (ch >= '0' && ch <= '0' + BOARD_COLS)) {
            accepted = true;
        }

        if (accepted) {
            rowMode = !rowMode;
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
