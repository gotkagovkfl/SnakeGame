#include "Score.h"

//점수달성 여부를 확인하고 화면전환
bool Score::LevelUp()
{
    scoreGateUse = gateUse;
    switch(stageNum)
    {
        case 1:
        if(scoreBodyLen >= 3 &&  scoreGateUse >= 3) 
        {
            stageNum++;
            clear();
            WINDOW *loadingWin = subwin(stdscr, 5, 60, 10, 10);
            init_pair(21, COLOR_WHITE, COLOR_GREEN);
            box(loadingWin, 0,0);
            attron(COLOR_PAIR(21));
            wbkgd(loadingWin, COLOR_PAIR(21));
            refresh();

            init_pair(20, COLOR_RED, COLOR_GREEN);
            attron(COLOR_PAIR(20));
            mvprintw(11, 24, "Are you ready for the next stage?");
            attron(A_BLINK);
            attron(COLOR_PAIR(21));
            mvprintw(13, 32, "press 'r' key");
            gateUse = 0;
            return true;
        }
        case 2:
        if(scoreBodyLen >= 5 &&  scoreGateUse >= 3)
        {
            stageNum++;
            clear();
            WINDOW *loadingWin = subwin(stdscr, 5, 60, 10, 10);
            init_pair(21, COLOR_WHITE, COLOR_GREEN);
            box(loadingWin, 0,0);
            attron(COLOR_PAIR(21));
            wbkgd(loadingWin, COLOR_PAIR(21));
            refresh();

            init_pair(20, COLOR_RED, COLOR_GREEN);
            attron(COLOR_PAIR(20));
            mvprintw(11, 24, "Are you ready for the next stage?");
            attron(A_BLINK);
            attron(COLOR_PAIR(21));
            mvprintw(13, 32, "press 'r' key");
            gateUse = 0;
            return true;
        }
        case 3:
        if(scoreBodyLen >= 7 &&  scoreGateUse >= 3)
        {
            stageNum++;
            clear();
            WINDOW *loadingWin = subwin(stdscr, 5, 60, 10, 10);
            init_pair(21, COLOR_WHITE, COLOR_GREEN);
            box(loadingWin, 0,0);
            attron(COLOR_PAIR(21));
            wbkgd(loadingWin, COLOR_PAIR(21));
            refresh();

            init_pair(20, COLOR_RED, COLOR_GREEN);
            attron(COLOR_PAIR(20));
            mvprintw(11, 24, "Are you ready for the next stage?");
            attron(A_BLINK);
            attron(COLOR_PAIR(21));
            mvprintw(13, 32, "press 'r' key");
            gateUse = 0;
            return true;
        }
        case 4:
        if(scoreBodyLen >= 10 &&  scoreGateUse >= 3)
        {
            stageNum++;
            clear();

            gameClear = true;
            return true;
        }
        break;
    }
    return false;
}