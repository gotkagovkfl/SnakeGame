#include <ncurses.h>

extern int gateUse;
extern int plusScore;
extern int minusScore;
extern bool gameClear;

class Score
{
public:
    int stageNum;
    int scoreBodyLen;
    int scoreGateUse;
    //생성자
    Score(int stageNum = 1, int scoreBodyLen = 0, int scoreGateUse = 0)
    :stageNum(stageNum), scoreBodyLen(scoreBodyLen), scoreGateUse(scoreGateUse){}
    //점수달성 여부를 확인하고 화면전환
    bool LevelUp();
    void nextStageScreen();
    void nextStage();
};