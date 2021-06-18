#include <ncurses.h>
#include <vector>
#include <thread>

#include "Score.h"
#include "Map.h"
#include "GateNWall.h"
#include "Object.h"
#include "Snake.h"
#include "Item.h"

using namespace std;

//
bool play= true; //게임 종료 플래그
bool gameClear = false;
void fail(){play=false;} // 게임 종료 함수

int mapWidth;
int mapHeight;
int gateUse = 0;

//----------------ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ--------전역함수----------------------- 
// 게임오버화면
void gameover()
{
    clear();
    WINDOW *gameover = subwin(stdscr, 5, 60, 10, 10);
    init_pair(21, COLOR_WHITE, COLOR_RED);
    box(gameover, 0,0);
    attron(COLOR_PAIR(21));
    wbkgd(gameover, COLOR_PAIR(21));

    init_pair(20, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(20));
    mvprintw(11, 35, "YOU LOSE");
    attron(A_BLINK);
    attron(COLOR_PAIR(21));
    mvprintw(13, 19, "!!!!!!!!!!!!!!!!GAME OVER!!!!!!!!!!!!!!!!");
    refresh();
    
    napms(2000);
    endwin();
    fail();
}
// 클리어화면
void GameClear()
{
    clear();
    init_pair(20, COLOR_RED, COLOR_RED);
    attron(COLOR_PAIR(20));
    int x = 5; int y = 11;
    mvprintw(x, y+2, "00");
    mvprintw(x, y+4, "00");
    mvprintw(x, y+6, "00");
    mvprintw(x, y+8, "00");
    mvprintw(x+1, y, "00");
    mvprintw(x+2, y, "00");
    mvprintw(x+3, y, "00");
    mvprintw(x+4, y, "00");
    mvprintw(x+5, y, "00");
    mvprintw(x+6, y+2, "00");
    mvprintw(x+6, y+4, "00");
    mvprintw(x+6, y+6, "00");
    mvprintw(x+6, y+8, "00");

    mvprintw(x, y+12, "00");
    mvprintw(x+1, y+12, "00");
    mvprintw(x+2, y+12, "00");
    mvprintw(x+3, y+12, "00");
    mvprintw(x+4, y+12, "00");
    mvprintw(x+5, y+12, "00");
    mvprintw(x+6, y+12, "00");

    mvprintw(x+1, y+16, "00");
    mvprintw(x+2, y+16, "00");
    mvprintw(x+3, y+16, "00");
    mvprintw(x+4, y+16, "00");
    mvprintw(x+5, y+16, "00");
    mvprintw(x, y+18, "00");
    mvprintw(x, y+20, "00");
    mvprintw(x, y+22, "00");
    mvprintw(x, y+24, "00");
    mvprintw(x+3, y+18, "00");
    mvprintw(x+3, y+20, "00");
    mvprintw(x+3, y+22, "00");
    mvprintw(x+3, y+24, "00");
    mvprintw(x+6, y+18, "00");
    mvprintw(x+6, y+20, "00");
    mvprintw(x+6, y+22, "00");
    mvprintw(x+6, y+24, "00");
    mvprintw(x+5, y+26, "00");
    mvprintw(x+1, y+26, "00");
    mvprintw(x+2, y+26, "00");

    mvprintw(x+2, y+30, "00");
    mvprintw(x+3, y+30, "00");
    mvprintw(x+4, y+30, "00");
    mvprintw(x+1, y+32, "00");
    mvprintw(x+5, y+32, "00");
    mvprintw(x, y+34, "00");
    mvprintw(x, y+36, "00");
    mvprintw(x, y+38, "00");
    mvprintw(x+6, y+34, "00");
    mvprintw(x+6, y+36, "00");
    mvprintw(x+5, y+38, "00");
    mvprintw(x+4, y+40, "00");
    mvprintw(x+1, y+40, "00");
    mvprintw(x+2, y+42, "00");
    mvprintw(x+3, y+42, "00");
    mvprintw(x+4, y+42, "00");
    mvprintw(x+5, y+42, "00");
    mvprintw(x+6, y+44, "00");

    mvprintw(x, y+48, "00");
    mvprintw(x+1, y+48, "00");
    mvprintw(x+2, y+48, "00");
    mvprintw(x+3, y+48, "00");
    mvprintw(x+4, y+48, "00");
    mvprintw(x+5, y+48, "00");
    mvprintw(x+6, y+48, "00");
    mvprintw(x+2, y+50, "00");
    mvprintw(x+1, y+52, "00");
    mvprintw(x, y+54, "00");
    mvprintw(x, y+56, "00");

    WINDOW *startWin = subwin(stdscr, 5, 60, 15, 10);
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    box(startWin, 0,0);
    attron(COLOR_PAIR(1));
    wbkgd(startWin, COLOR_PAIR(1));
    refresh();

    attron(A_BLINK);
    mvprintw(17, 22, "Congratulations! cleared all stages");
    
    napms(2000);
    endwin();
    fail(); //화면 종료를 위함
}

//시작대기화면
void startScreen()
{
    start_color();
    // 초기화면
    int x = 4;
    int y = 10;

    int b = 33;
    mvprintw(12, b, "G");
    mvprintw(12, b+4, "A");
    mvprintw(12, b+8, "M");
    mvprintw(12, b+12, "E");

    init_color(14,1000,700,0 ); // 몸색 (노란색)
    init_color(15, 1000, 400,0); // 머리색 (오렌지)
    init_pair(4, 14, 14); //뱀 몸통 색
    init_pair(5,  15, 15); // 뱀 머리 색
    //s
    attron(COLOR_PAIR(5));
    mvprintw(x+0, y+2, "00");
    mvprintw(x+0, y+4, "00");
    mvprintw(x+0, y+6, "00");
    mvprintw(x+1, y, "00");
    mvprintw(x+2, y, "00");
    mvprintw(x+3, y+2, "00");
    mvprintw(x+3, y+4, "00");
    mvprintw(x+3, y+6, "00");
    mvprintw(x+4, y+8, "00");
    mvprintw(x+5, y+8, "00");
    mvprintw(x+6, y+2, "00");
    mvprintw(x+6, y+4, "00");
    mvprintw(x+6, y+6, "00");
    //nake
    attron(COLOR_PAIR(4));
    mvprintw(x, y+12, "00");
    mvprintw(x+1, y+12, "00");
    mvprintw(x+2, y+12, "00");
    mvprintw(x+3, y+12, "00");
    mvprintw(x+4, y+12, "00");
    mvprintw(x+5, y+12, "00");
    mvprintw(x+6, y+12, "00");
    mvprintw(x+2, y+14, "00");
    mvprintw(x+3, y+16, "00");
    mvprintw(x+4, y+18, "00");
    mvprintw(x, y+20, "00");
    mvprintw(x+1, y+20, "00");
    mvprintw(x+2, y+20, "00");
    mvprintw(x+3, y+20, "00");
    mvprintw(x+4, y+20, "00");
    mvprintw(x+5, y+20, "00");
    mvprintw(x+6, y+20, "00");

    mvprintw(x+3, y+24, "00");
    mvprintw(x+4, y+24, "00");
    mvprintw(x+5, y+24, "00");
    mvprintw(x+6, y+24, "00");
    mvprintw(x+4, y+26, "00");
    mvprintw(x+4, y+28, "00");
    mvprintw(x+4, y+30, "00");
    mvprintw(x+3, y+32, "00");
    mvprintw(x+4, y+32, "00");
    mvprintw(x+5, y+32, "00");
    mvprintw(x+6, y+32, "00");
    mvprintw(x, y+28, "00");
    mvprintw(x+1, y+26, "00");
    mvprintw(x+2, y+26, "00");
    mvprintw(x+1, y+30, "00");
    mvprintw(x+2, y+30, "00");

    mvprintw(x, y+36, "00");
    mvprintw(x+1, y+36, "00");
    mvprintw(x+2, y+36, "00");
    mvprintw(x+3, y+36, "00");
    mvprintw(x+4, y+36, "00");
    mvprintw(x+5, y+36, "00");
    mvprintw(x+6, y+36, "00");
    mvprintw(x+3, y+38, "00");
    mvprintw(x+2, y+40, "00");
    mvprintw(x+4, y+40, "00");
    mvprintw(x+1, y+42, "00");
    mvprintw(x+5, y+42, "00");
    mvprintw(x, y+44, "00");
    mvprintw(x+6, y+44, "00");

    mvprintw(x, y+48, "00");
    mvprintw(x+1, y+48, "00");
    mvprintw(x+2, y+48, "00");
    mvprintw(x+3, y+48, "00");
    mvprintw(x+4, y+48, "00");
    mvprintw(x+5, y+48, "00");
    mvprintw(x+6, y+48, "00");
    mvprintw(x, y+50, "00");
    mvprintw(x, y+52, "00");
    mvprintw(x, y+54, "00");
    mvprintw(x, y+56, "00");
    mvprintw(x+3, y+50, "00");
    mvprintw(x+3, y+52, "00");
    mvprintw(x+3, y+54, "00");
    mvprintw(x+3, y+56, "00");
    mvprintw(x+6, y+50, "00");
    mvprintw(x+6, y+52, "00");
    mvprintw(x+6, y+54, "00");
    mvprintw(x+6, y+56, "00");
    

    WINDOW *startWin = subwin(stdscr, 5, 60, 15, 10);
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    box(startWin, 0,0);
    attron(COLOR_PAIR(1));
    wbkgd(startWin, COLOR_PAIR(1));
    refresh();

    attron(A_BLINK);
    mvprintw(17, 32, "press 's' key");


    // 겜 시작
    while(1){
        int input = getch();
        
        if(input == 's') {break;}
    }

    clear();
}

//맵 그래픽 생성 
void mapUpdate(Object** m, int h, int w)
{
    clear();
    for(int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            int objType= m[j][i].getTN();
            attrset(COLOR_PAIR(objType)); //타입에 맞게 색칠함
            mvprintw(j, i*2, "00");
        }
    }
    refresh();
}

// 시간의 흐름             // 레퍼런스 전달시 컴파일에러
void timeUpdate(Score *score, Map *map,Snake *s,Item *i,GateNWall *g)
{
    for(int a=0;a <5; a++)
    {
        //상태창 (스테이지마다 상태창을 새로 씀)
        WINDOW *win;
        win = newwin(map->getHeight(),30,0,map->getWidth()*2);
        wbkgd(win, COLOR_PAIR(10));
        box(win, 0,0);

        wattron(win,A_BOLD); // 제목 강조
        mvwprintw(win, 1,2, "SNAKE GAME");
        wattroff(win,A_BOLD);
        mvwprintw(win, 4,2, "STATUS:");
        mvwprintw(win, 6,2, "STAGE: %d",score->stageNum);
        mvwprintw(win, 11,5, "- score");
        mvwprintw(win, 12,5, "+ score");
        wattron(win,COLOR_PAIR(6));
        mvwprintw(win, 11,2, "00");
        wattroff(win,COLOR_PAIR(6));
        wattron(win,COLOR_PAIR(7));
        mvwprintw(win, 12,2, "00");
        wattroff(win,COLOR_PAIR(7));
        
        double time =0;
        int tick= 100;  //몇초마다 화면 갱신 (뱀 이동 )할지 정함-  단위 ms 
        int initItemCD = 4000; // 아이템이 나오는 시간- 단위 ms
        int initGateCD = 10000;
        double ItemCD = 0;
        double GateCD = 0;

        // 스테이지 별로 뱀 위치 조정
        if(a > 0)
        {
            s->Init(map->m);
            i->Init(map->m);
        }
        if(score->stageNum == 2) {map->makeVertical(mapWidth/2  + 6); g->fillWalls(map->m);}
        else if(score->stageNum == 3) {map->makeHorizontal(mapHeight/2 - 6);g->fillWalls(map->m);}
        else if(score->stageNum == 4) {map->makeVertical(mapHeight/2 - 6);g->fillWalls(map->m);}
        //시간 흐름 
        do {
            box(win, 0,0);

            wattron(win,A_BOLD); // 제목 강조
            mvwprintw(win, 1,2, "SNAKE GAME");
            wattroff(win,A_BOLD);
            mvwprintw(win, 4,2, "STATUS:");
            mvwprintw(win, 6,2, "STAGE: %d",score->stageNum);
            mvwprintw(win, 10,2, "num of items : %d     ",i->numItem);
            // wclear(stdscr);

            //ItemCD가 0이 될때마다 아이템 생성 
            if (ItemCD==0)  
            {
                if (time >=initItemCD*0.003 && i->numItem >=3) // 동시에 3개만 유지할수있도록. 근데 가끔씩 4개됨. 해결 필요 ****************************** 
                {
                    i->popItem(map->m);
                }
                i->pushItem(map->m);
                ItemCD=initItemCD;
            }
            // GateCD가 0이 될때마다 게이트 생성
            s->decreaseOnGate();
            if (GateCD==0)
            {
                if (s->onGate==0){g->selectGate(map->m);} //게이트 생성

                GateCD=initGateCD;

                // mvwprintw(win, 11,2, "(%d,%d)  ,  (%d,%d)   ",g->gate1.getY(),g->gate1.getX(),g->gate2.getY(),g->gate2.getX()); //占쏙옙占쏙옙占쏙옙 占쏙옙탈占쏙옙치 占쏙옙占
            }
            
            // 뱀 움직임 업데이트
            s->move(map->m,*i,*g);
            mapUpdate(map->m,mapHeight,mapWidth);

            // 점수업데이트
            if(score->stageNum == 1) mvwprintw(win, 7,2, "SCORE: %d/3     ",s->numBody-3);
            else if(score->stageNum == 2) mvwprintw(win, 7,2, "SCORE: %d/5     ",s->numBody-3);
            else if(score->stageNum == 3) mvwprintw(win, 7,2, "SCORE: %d/7     ",s->numBody-3);
            else if(score->stageNum == 4) mvwprintw(win, 7,2, "SCORE: %d/10     ",s->numBody-3);
            mvwprintw(win, 8,2, "GateUse: %d/3     ",gateUse);
            score->scoreBodyLen = s->numBody-3;
            

            // 시간 업데이트
            mvwprintw(win, 9,2, "TIME: %1.1f sec  ",time);
            mvwprintw(win, 10,2, "num of items : %d     ",i->numItem);
            time+=tick*0.001;
            wrefresh(win);

            napms(tick); //sleep과 같은 기능
            ItemCD-=tick;
            GateCD-=tick;

            bool stageEnd = false;
            if(score->LevelUp() == true)
            {
                while(play && !gameClear)
                {
                    int input = getch();
                    if(input == 'r')
                    {
                        stageEnd = true;
                        break;
                    } 
                }
            }
            if(stageEnd == true)
            {
                clear();
                break;
            }
        } while (play && !gameClear);
    }
    if(play==false) gameover();
    if(gameClear) GameClear();
}
// 맵크기 선택
void selectMapSize()
{
    mvprintw(3, 8, "select map size number and press number key");
    mvprintw(5, 8, "1: width 24 Height 18");
    mvprintw(6, 8, "2: width 30 Height 24");
    mvprintw(7, 8, "3: width 36 Height 30");

    while(1){
        int input = getch();
        if(input == '1')
        {
            mapWidth = 24;
            mapHeight = 18;
            break;
        }
        else if(input == '2')
        {
            mapWidth = 30;
            mapHeight = 24;
            break;
        }
        if(input == '3')
        {
            mapWidth = 36;
            mapHeight = 30;
            break;
        }
    }
    clear();
}

// 사용할 색깔 초기화
void setColor()
{
    //기본 색이 너무 칙칙해서 밝게 바꿨습니다.
    // start_color();
    init_color(11,1000,1000,1000); //빈공간색 (흰색);
    init_color(12, 400, 400, 400); // 일반벽 색 (회색);
    init_color(13, 0,0,0);// 무적 벽(검은색);
    init_color(14,1000,700,0 ); // 몸색 (노란색)
    init_color(15, 1000, 400,0); // 머리색 (오렌지;
    init_color(18,1000,100,500); // 게이트색(핑크)
    // 만든 색상 적용
    init_pair(1, 11, 11); //빈공간 색
    init_pair(2,12,12);                     // 일반 벽 색
    init_pair(3, 13, 13); // 딴딴벽 색
    init_pair(4, 14, 14); //뱀 몸통 색
    init_pair(5,  15, 15); // 뱀 머리 색
    init_pair(6, COLOR_GREEN, COLOR_GREEN); // 독색
    init_pair(7, COLOR_RED, COLOR_RED); //사과색
    init_pair(8, 18,18); //게이트색
    init_pair(10, COLOR_BLACK, COLOR_WHITE); //상태창 색
}

// 사용자입력 받기
void getInput(Map& map, Snake& snake)
{
    int input;
    keypad(stdscr, true); //특수키 입력받기 활성화
    while(play == true)
    {
        input=getch();
        switch(input)
        {
            case KEY_UP:
                snake.setToY(-1);
                snake.setToX(0);
                break;

            case KEY_DOWN:
                snake.setToY(1);
                snake.setToX(0);
                break;
                
            case KEY_LEFT:
                snake.setToY(0);
                snake.setToX(-1);
                break;

            case KEY_RIGHT:
                snake.setToY(0);
                snake.setToX(1);
                break;
        }
        //디버깅용 입력

        // 몸통추가
        if (input == '1')
        {
            snake.pushBody(map.m);
        }
    }
}

//-----------------------메인 함수------------------------ 
int main()
{
    initscr();

    curs_set(FALSE); // 
    noecho(); // 

    // 맵크기 선택
    selectMapSize();

    // 시작화면
    startScreen();

    // 겜초기화
    Map map(mapWidth,mapHeight);// 맵 초기화
    Item item(map.m,map.getHeight(),map.getWidth());//아이템 리스트 초기화 
    Snake snake(map.m,map.getHeight(),map.getWidth());// 뱀 초기화
    GateNWall gnw(map.m,map.getHeight(),map.getWidth());// 게이트 &월 초기화
    Score score;//화면 

    setColor(); //사용할 색깔 초기화

    thread t(timeUpdate,&score,&map, &snake, &item, &gnw) ; // 스레드 생성
    getInput(map,snake); //사용자입력 받기    

    if(t.joinable()){t.join();} // 쓰레드 끝나길 기다림
    return 0;
}