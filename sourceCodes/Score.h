#include <ncurses.h>

extern int gateUse;
extern bool gameClear;

class Score
{
public:
    int stageNum;
    int scoreBodyLen;
    int scoreGateUse;

    Score(int stageNum = 1, int scoreBodyLen = 0, int scoreGateUse = 0)
    :stageNum(stageNum), scoreBodyLen(scoreBodyLen), scoreGateUse(scoreGateUse){}

    bool LevelUp()
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
};