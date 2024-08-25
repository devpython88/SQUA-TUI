#ifndef SQUA_H
#define SQUA_H

/********************************************/

#include <ncurses.h>
#include <vector>
#include <functional>
#include <optional>
#include "squa_gfx.h"
#include <string.h> // for strlen
#include <string>

/********************************************/

#define OPTION_OK 1
#define OPTION_CANCEL 0
#define ESC 27
const std::function<void(void)> NO_ONCLICK_COMMAND;

/********************************************/

struct BUTTON
{
    int posX, posY;
    const char *text;
    std::function<void(void)> onClick;
};

/********************************************/

static std::vector<BUTTON> buttons;
static int selectedButton;
static char lastKeyPressed;

/********************************************/

inline void SQUA_Init(bool hideCursor = true, bool makeESCKeyInstant = true)
{
    // initialize ncurses
    initscr();
    keypad(stdscr, true);
    noecho();
    cbreak();

    if (hideCursor)
        curs_set(false);
    if (makeESCKeyInstant)
        set_escdelay(0);
    selectedButton = 0;
}

inline int SQUA_Begin(char exitKey = ESC, char selectKey = '\t', char useKey = '\n')
{
    int currentButton = 0;
    if (!buttons.empty())
        for (const BUTTON &btn : buttons)
        {
            if (currentButton == selectedButton)
            {
                attron(A_REVERSE);
            }
            mvprintw(btn.posY, btn.posX, btn.text);
            if (currentButton == selectedButton)
            {
                attroff(A_REVERSE);
            }

            currentButton++;
        }

    lastKeyPressed = getch();

    if (lastKeyPressed == ERR){
        printf("Error occured in getch().");
        std::exit(1);
    }

    if (lastKeyPressed == exitKey)
    {
        return 1;
    }
    else if (lastKeyPressed == selectKey)
    {
        if (buttons.empty()) return 0;
        
        if (selectedButton < buttons.size() - 1)
            selectedButton++;
        else
            selectedButton = 0;
    }
    else if (lastKeyPressed == useKey)
    {
        if (buttons.empty()) return 0;

        if (buttons[selectedButton].onClick)
            (buttons[selectedButton].onClick)();
    }

    return 0;
}

inline void SQUA_CreateButton(int posX, int posY, const char *text,
                              std::function<void(void)> clicked)
{
    BUTTON btn = {posX, posY, text};
    if (clicked)
        btn.onClick = clicked;
    buttons.push_back(btn);
}

inline void SQUA_Terminate()
{
    curs_set(true);
    endwin();
}

inline void SQUA_Clear() { clear(); }

inline void SQUA_MessageBox(const char *msg, const char *title = "Message")
{
    SQUA_Clear();
    refresh();

    int row, col;
    getmaxyx(stdscr, row, col);

    WINDOW *win = newwin(row - 4, col - 4, 2, 2);
    box(win, 0, 0);
    wrefresh(win);

    mvprintw(2, (col / 2) - strlen(title), title);

    int text_x = (col / 2) - strlen(msg);
    int button_x = (col / 2) - 7;

    char ch;
    while (true)
    {
        mvprintw((row / 2) - 2, text_x, msg);
        attron(A_REVERSE);
        mvprintw((row / 2), button_x, "<Close>");
        attroff(A_REVERSE);

        ch = getch();
        if (ch == ESC || ch == '\n')
        {
            break;
        }
    }

    SQUA_Clear();
}

inline int SQUA_Question(const char *msg, const char *title = "Question", const char *opt_1 = "<Ok>", const char *opt_2 = "<Cancel>")
{
    SQUA_Clear();
    refresh();

    int row, col;
    getmaxyx(stdscr, row, col);

    WINDOW *win = newwin(row - 4, col - 3, 2, 2);
    box(win, 0, 0);
    wrefresh(win);

    mvprintw(2, (col / 2) - strlen(title), title);

    int text_x = (col / 2) - strlen(msg);
    int button1_x = (col / 2) - strlen(opt_1);
    int button2_x = (col / 2) - strlen(opt_2);

    int sel = 0;
    int opt = -1;

    char ch;
    while (true)
    {
        mvprintw((row / 2) - 2, text_x, msg);
        if (sel == 0)
            attron(A_REVERSE);
        mvprintw((row / 2), button1_x, "<OK>");
        if (sel == 0)
            attroff(A_REVERSE);

        if (sel == 1)
            attron(A_REVERSE);
        mvprintw((row / 2) + 2, button2_x, "<CANCEL>");
        if (sel == 1)
            attroff(A_REVERSE);

        ch = getch();
        if (ch == ESC)
        {
            break;
        }

        if (ch == '\t')
        {
            if (sel < 1)
                sel++;
            else
                sel = 0;
        }
        if (ch == '\n')
        {
            if (sel == 0)
            {
                opt = OPTION_OK;
                break;
            }
            if (sel == 1)
            {
                opt = OPTION_CANCEL;
                break;
            }
        }
    }

    SQUA_Clear();
    return opt;
}


inline std::function<void(void)> SQUA_ConvertToListener(auto func){
    std::function<void(void)> f = func;
    return f;
}

/********************************************/

#endif