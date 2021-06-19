//@author 김유진(20203045) 100%
#include "Score.h"

//점수달성 여부를 확인하고 화면전환
bool Score::LevelUp()
{
    switch(stageNum)
        {
            case 1:
            if(scoreBodyLen >= 3 &&  gateUse >= 3 && plusScore >= 4 && minusScore >= 1) 
            {
                stageNum++;
                nextStage();
                return true;
            }
            case 2:
            if(scoreBodyLen >= 5 &&  gateUse >= 3 && plusScore >= 7 && minusScore >= 2)
            {
                stageNum++;
                nextStage();
                return true;
            }
            case 3:
            if(scoreBodyLen >= 7 &&  gateUse >= 3 && plusScore >= 10 && minusScore >= 3)
            {
                stageNum++;
                nextStage();
                return true;
            }
            case 4:
            if(scoreBodyLen >= 10 &&  gateUse >= 3 && plusScore >= 14 && minusScore >= 4)
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

void Score::nextStageScreen()
{
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
}

void Score::nextStage()
{
    gateUse = 0;
    plusScore = 0;
    minusScore = 0;

    nextStageScreen();
}