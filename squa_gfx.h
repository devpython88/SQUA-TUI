#ifndef SQUA_GFX_H
#define SQUA_GFX_H

#include "squa.h"

inline void SQUA_MoveCursor(int newX, int newY){
    move(newY, newX);
}

inline void SQUA_PrintAtCursor(const char *text){
    printw(text);
}

inline void SQUA_MoveAndPrint(int newX, int newY, const char *text){
    SQUA_MoveCursor(newX, newY);
    SQUA_PrintAtCursor(text);
}

inline void SQUA_SetModeToHighlight(){
    attron(A_REVERSE);
}

inline void SQUA_SetModeToNormal(){
    attroff(A_REVERSE);
}

#endif