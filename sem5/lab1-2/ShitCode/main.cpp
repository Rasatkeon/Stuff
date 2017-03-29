#include <sys/types.h>
#include <curses.h>
#include <iostream>
#include "./TypeManipulations.h"


using namespace std;
uint getUint() {
    printw("Enter uint: ");
    uint input;
    scanw("%u", &input);
    return input;
}

double getDouble() {
    printw("Enter double: ");
    double input;
    scanw("%lf", &input);
    return input;
}

int main(int argc, char const *argv[]) {

    /*        CURSES SECTION        */

//    double inp;
//    cout << "Enter dat double: ";
//    cin >> inp;
//    cout << "Raw var is ";
//    printLnRawDouble(inp);
//    inp = setDoubleBit(inp, 40, 1);
//    inp = setDoubleBit(inp, 50, 1);
//    inp = setDoubleBit(inp, 41, 0);
//    cout << "Rav is " << inp << endl;
//    cout << "Raw rav is ";
//    printLnRawDouble(inp);

    initscr(); // Initiate screen
//    start_color();
    keypad(stdscr, TRUE); // Turn on special keys
//    noecho(); // Turn off echoes
    refresh();
    uint inp = getUint();
    printw("You entered %u\n", inp);
    printw("Its raw representation is %s\n", convertUintToRaw(inp));
    printw("Now in direct editing mode. Press n to continue");
    int x,y, begx, begy, stry, input;
    bool updateNumFlag = false;
    uint pos;
    noecho();
    getyx(curscr, y, x);
    getbegyx(curscr, begy, begx);
    stry = y;
    move(y+1, 26);
    while((input = getch()) != 'n') {
        getyx(curscr, y, x);
        switch (input) {
            case KEY_LEFT:
                if (x > 26) move(y, x - 1);
                break;
            case KEY_RIGHT:
                if (x < 26 + 31) move(y, x + 1);
                break;
            case KEY_UP:
                updateNumFlag = true;
                pos = (uint) (26 + 31 - x);
                inp = setUintBit(inp, pos, 1);
                break;
            case KEY_DOWN:
                updateNumFlag = true;
                pos = (uint) (26 + 31 - x);
                inp = setUintBit(inp, pos, 0);
                break;
            default:
                break;
        }
        if (updateNumFlag) {
            mvprintw(y - 1, begx, "You entered %u\n", inp);
            mvprintw(y, begx, "Its raw representation is %s\n", convertUintToRaw(inp));
            move(y, x);
            updateNumFlag = false;
        }
        refresh();
    }
    move(y + 3, begx);
    refresh();
    echo();
    double dinp = getDouble();
    printw("You entered %.32lg\n", dinp);
    printw("Its raw representation is %s\n", convertDoubleToRaw(dinp));
    printw("Now in direct editing mode. Press n to continue");
    noecho();
    getyx(curscr, y, x);
    getbegyx(curscr, begy, begx);
    stry = y;
    move(y+1, 26);
    while((input = getch()) != 'n') {
        getyx(curscr, y, x);
        switch (input) {
            case KEY_LEFT:
                if (x > 26) move(y, x - 1);
                break;
            case KEY_RIGHT:
                if (x < 26 + 63) move(y, x + 1);
                break;
            case KEY_UP:
                updateNumFlag = true;
                pos = (uint) (26 + 63 - x);
                dinp = setDoubleBit(dinp, pos, 1);
                break;
            case KEY_DOWN:
                updateNumFlag = true;
                pos = (uint) (26 + 63 - x);
                dinp = setDoubleBit(dinp, pos, 0);
                break;
            default:
                break;
        }
        if (updateNumFlag) {
            getyx(curscr, y, x);
            mvprintw(y - 1, begx, "You entered %.32lg\n", dinp);
            mvprintw(y, begx, "Its raw representation is %s\n", convertDoubleToRaw(dinp));
            move(y, x);
            updateNumFlag = false;
        }
        refresh();
    }
    refresh();
    noecho();
    getch();
//    int inp, x, y, maxx, maxy;
//    getmaxyx(curscr, maxy, maxx);
    endwin();
}