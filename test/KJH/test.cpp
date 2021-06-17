#include <ncurses.h>
#include <vector>
#include <thread>

using namespace std;

//
bool play= true; //게임 종료 플래그
bool gameClear = false;
void fail(){play=false;} // 게임 종료 함수

int mapWidth;
int mapHeight;
int gateUse = 0;

// 
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

//
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

// 각 오브젝트의 속성을 담는 부모 클래스 (화면에 표시된 정사각형 하나하나가 오브젝트임)
class Object
{
    protected:
        int x,y;
        int typeNum;
        
    public:
        
        Object(int y=0, int x=0, int tn = 0):x(x), y(y) , typeNum(tn){}
        virtual ~Object(){}
        
        int getY() {return y;}
        int getX() {return x;}
        void setYX(int y,int x){this->y=y;this->x=x;}

        int getTN(){return typeNum;}

        void setTN(int typeNum) {this->typeNum = typeNum;}

};
// 빈공간
class Space :public Object
{
    public:
        Space (int y, int x):Object(y,x,1){}

        ~Space(){}
};
// 일반벽
class NormalWall : public Object
{
    public:
        bool isGate=false;
        NormalWall (int y, int x):Object(y,x,2){}

        ~NormalWall(){}

};
// 딴딴벽
class ImmueWall : public Object
{
    public:
        ImmueWall (int y, int x):Object(y,x,3){}

        ~ImmueWall(){}
};
// 뱀 몸통
class Body: public Object
{
    public:
        Body (int y, int x):Object(y,x,4){}

        ~Body(){}
};
// 뱀 머리
class Head : public Object
{     
    public:
        Head (int y, int x):Object(y,x,5){}

        ~Head(){}
};
// 독
class Poison : public Object
{
    public:
        Poison (int y, int x):Object(y,x,6){}

        ~Poison(){}
};
// 사과
class Apple : public Object
{
    public:
        Apple (int y, int x):Object(y,x,7){}

        ~Apple(){}
};
//게이트
class Gate: public Object
{
    public:
        Gate (int y, int x):Object(y,x,8){}

        ~Gate(){}
};
//---------게이트 클래스------------ 
class GateNWall
{
    protected:
        int height;
        int width;
        
    public:
        Object gate1;
        Object gate2;
        bool gateOpen=false; 

        //출구를 구하기 위한 변수들
        int exitOfGate[4][2] ={{-1,0},{0,1},{1,0},{0,-1}};
        int idxForFind=0;

        vector <Object> walls; //벽을 담는 벡터 

        //생성자
        GateNWall(Object**& m ,int h=30, int w= 24):height(h),width(w)
        {
            fillWalls(m);
            selectGate(m);
            // debugging(m);
        }
        // walls 벡터를 맵에서 일반 벽인 오브젝트로 채움
        void fillWalls(Object**& m)
        {
            walls.clear();
            
            for (int j=0;j<height;j++){
                for (int i=0;i<width;i++)
                {
                    if (m[j][i].getTN()==2){walls.push_back(m[j][i]);}
                }
            }
        }
        // //for debugging
        // void debugging(Object**& m)
        // {
        //     gate1 = Gate(0,5);
        //     gate2 = Gate(0,6);
        //     m[0][5]=gate1;
        //     m[0][6]=gate2;
        // }
        //게이트 선택
        void selectGate(Object** & m)
        {
            //먼저 현재 게이트는 벽으로 복구
            restore(m);
             // 게이트의 인덱스 뽑기 (2개)
            int randIdx1,randIdx2;
            do
            {
                srand((unsigned int)time(NULL));
                randIdx1=rand()%(walls.size());
                srand((unsigned int)time(NULL)*-1);
                randIdx2=rand()%(walls.size());
            } 
            while (randIdx1==randIdx2);
            
            Object temp1 = walls[randIdx1];
            Object temp2 = walls[randIdx2];

            m[temp1.getY()][temp1.getX()] = Gate(temp1.getY(),temp1.getX());
            m[temp2.getY()][temp2.getX()] = Gate(temp2.getY(),temp2.getX());

            gate1 = m[temp1.getY()][temp1.getX()];
            gate2 = m[temp2.getY()][temp2.getX()];

            gateOpen=true;

            // walls[randIdx1]= 
        }
        //게이트 되돌리기
        void restore(Object**& m)
        {
            if (gateOpen)
            {
                m[gate1.getY()][gate1.getX()] = NormalWall(gate1.getY(),gate1.getX());
                m[gate2.getY()][gate2.getX()] = NormalWall(gate2.getY(),gate2.getX());
            }
        }
        //게이트 출구 좌표구하기
        void setExit(Object**& m,Object& g,int& toY,int& toX)
        {
            int tempY;
            int tempX;
            // 원형 리스트의 시작 인덱스 구하기
            for(int i=0;i<4;i++)
            {
                if (exitOfGate[i][0]== false && exitOfGate[i][1]) {idxForFind=i;break;} 
            }

             //시계방향으로 탐색
            for (int i=0;i<4;i++)
            {
                tempY= g.getY()+exitOfGate[idxForFind][0],  
                tempX= g.getX()+exitOfGate[idxForFind][1]; // 현재 게이트의 위치에서 시계방향으로 찾기
				// 해당좌표가 빈공간이라면, 게이트의 출구임
                if (0<=tempY &&tempY<height&& 0<tempX &&tempX< width) // 시계방향으로 확인하는 좌표가 맵 밖이 아니어야함
                {
                    if (m[tempY][tempX].getTN()==1){break;}   //만약 출구게이트의 사방이 벽으로 막혀있으면 죽음
                }
                ++idxForFind%=4;
            }
            int retToY = exitOfGate[idxForFind][0];
            int retToX = exitOfGate[idxForFind][1];

            toY=retToY;
            toX=retToX;
        }

};
//-----------------------아이템 클래스---------------- 
class Item
{
    protected:
        int height;
        int width;
    public:
        int numItem=0;
        vector <Object> it;

        Item(Object**& m, int h = 30, int w = 24): height(h), width(w) { }

        void Init(Object**& m)
        {
            while(numItem > 0) popItem(m);
        }


        // 아이템 생성 (시간마다)
        void pushItem(Object**& m)
        {
             //랜덤 y,x값 추출 (빈공간이어야함 ) 랙걸리면 여기서 while도느라 그런거
            int randY, randX;
            do
            {
                srand((unsigned int)time(NULL));
                randY=rand()%(height-2)+1;
                randX=rand()%(width-2)+1;
            } while (m[randY][randX].getTN() != 1); // 빈공간을 찾을때까지 
            
            //독 일지 사과일지 정함
			srand(time(NULL));
            int n = rand()%2; //50 %확률
            //그리고 아이템 만들어서
            Object item;
            if (n) {item = Apple(randY,randX);}
            else {item = Poison(randY,randX);}
            //벡터에 삽입
            it.insert(it.begin(),item); 
            m[randY][randX] = item;
            numItem++;
        }
        // 가장 오래된 아이템 제거 (시간 초과, 스테이지 클리어 시)
        void popItem(Object**& m)
        {
            Object item = it[numItem-1];
            it.pop_back();
            m[item.getY()][item.getX()]=Space(item.getY(),item.getX());
            numItem--;
        }
        // 특정 아이템 제거  (뱀과 접촉시)
        void eraseItem(int y,int x)
        {
            for (int i=0;i<numItem;i++)
            {
                if (it[i].getY()==y&&it[i].getX()==x)
                {
                    Object temp = it[i];
                    it.erase(it.begin()+i);
                    numItem--;
                }
            }
            
        }
};
//----------------------뱀 클래스------------------------------ 
class Snake
{
    int toX=-1;
    int toY=0;
    int nextY, nextX;
    
    public:
        int numBody=2;
        int onGate =0;
        int  tailY, tailX;
        vector <Object> s;
        
        Snake(Object**& m,int h=30,int w=24) : tailY(h/2), tailX(w/2)
        {
            //처음에 길이가 3인 뱀 생성
            Head head(tailY,tailX);
            m[tailY][tailX]= head;
            s.push_back(head);
            Body body(tailY,++tailX);
            m[tailY][tailX]= body;
            s.push_back(body);

            pushBody(m);
        }

        void Init(Object**& m)
        {
            while(numBody > 3) popBody(m);
            m[s[0].getY()][s[0].getX()].setTN(1);
            m[s[1].getY()][s[1].getX()].setTN(1);
            m[s[2].getY()][s[2].getX()].setTN(1);

            toY=0;
            toX=-1;

            s[0].setYX(mapWidth/2, mapHeight/2);
            s[1].setYX(mapWidth/2, mapHeight/2 + 1);
            s[2].setYX(mapWidth/2, mapHeight/2 + 1);
        }

        void setToY(int y){toY=y;}
        void setToX(int x){toX=x;}

        //게이트 통과중임을 나타내는 상태변수 조정
        void setOnGate(){onGate=numBody;}
        void decreaseOnGate(){if(onGate){onGate--;}}
        
        int getToY(){return toY;}
        int getToX(){return toX;}
        //뱀 몸통 생성
        void pushBody(Object**& m)
        {
            //모서리에서 생성시 가끔 벽 뚫는 현상 해결해야함 **********************************여기서
            int chaiY = s[numBody-1].getY()-s[numBody-2].getY();
            int chaiX = s[numBody-1].getX()-s[numBody-2].getX();
            tailY += chaiY;
            tailX += chaiX;
            Body tail(tailY,tailX);
            m[tailY][tailX] = tail;

            s.push_back(tail);
            numBody++;
        }
        //뱀 몸통 제거
        void popBody(Object**& m)
        {
            m[s[numBody-1].getY()][s[numBody-1].getX()] = Space(s[numBody-1].getY(),s[numBody-1].getX());
            s.pop_back();
            numBody--;
            tailY = s[numBody-1].getY();
            tailX = s[numBody-1].getX();
        }
        // 뱀의 몸통 위치 설정(바로앞의 몸통의 위치로 이동함) (머리는 제외)
        void setBodyPos()
        {
            for (int i=numBody-1; i>0; i--)
            {
                s[i].setYX(s[i-1].getY(),s[i-1].getX());
            }
        }
        //머리위치설정(next값을 설정하고 그 값으로 이동)
        void setHeadPos()
        {
            nextY = s[0].getY()+toY;
            nextX = s[0].getX()+toX;
            s[0].setYX(nextY,nextX);   
        }
        // 뱀의 이동
        void move(Object**& m,Item& item, GateNWall& gnw)
        {
            setBodyPos();
            setHeadPos();
            
            // 꼬리는 빈공간으로
            m[tailY][tailX]= Space(tailY,tailX); 
            //그리고 꼬리 좌표 다시
            tailY = s[numBody-1].getY();
            tailX = s[numBody-1].getX();    
            
            // 움직인 곳에 뭔가 있을때,
            afterMove(m,item,gnw);            
            
            //변화 업뎃
            for (int i=0;i<numBody;i++)
            {
                m[s[i].getY()][s[i].getX()]= s[i];
            }
        }
        //이동한 곳에 뭔가 있는 경우
        void afterMove(Object**& m,Item& item,GateNWall& gnw)
        {
             //아이템
            for (int i=0;i<item.numItem;i++)
            { 
                Object obj = item.it[i];
                if ((obj.getY()==s[0].getY())&&(obj.getX()==s[0].getX())) // 머리랑 좌표가 같으면,
                {   
                     // 벽에 닿았을 때의 경우도 만들어야함 **********************************************************************
                    if (obj.getTN()==6)  //독먹으면 
                    {
                        popBody(m);
                        item.eraseItem(obj.getY(),obj.getX()); // 특정 아이템 제거

                        // 몸통 길이가 2이면 종료
                        if (s.size() == 2){
                            fail();
                        }

                    }
                    else if (obj.getTN()==7)  // 사과먹으면
                    {
                        pushBody(m);
                        item.eraseItem(obj.getY(),obj.getX());
                    }
                }
            }
            // 아이템이 아닌경우 
            Object obj = m[s[0].getY()][s[0].getX()];//뱀 머리의 현재 위치에 있는 오브젝트
            if (obj.getTN()==8) // 오브젝트가 게이트라면 
            {
                setOnGate(); 

                if (obj.getY() == gnw.gate1.getY() && obj.getX() == gnw.gate1.getX()) //오브젝트가 게이트1 일때  게이트 2로나옴
                {
                    gateUse++;
                    gnw.setExit(m,gnw.gate2,toY,toX);
                    s[0].setYX(gnw.gate2.getY()+toY,gnw.gate2.getX()+toX);
                }
                else //오브젝트가 게이트 2일때
                {
                    gateUse++;
                    gnw.setExit(m,gnw.gate1,toY,toX);
                    s[0].setYX(gnw.gate1.getY()+toY,gnw.gate1.getX()+toX);
                }
            }
            else if (obj.getTN()==2 ||obj.getTN()==4) // 벽에 닿거나 몸통에 닿았을 때 실패
            {
                fail();
            }
        }
};
//--------------------------맵 클래스 ------------------------------
class Map
{
    int width;
    int height;
    
    friend class Snake;

    public:
        Object** m;

        Map(int w=30,int h=24): width(w), height(h)
        {
            // 좌표 형성
            m = new Object*[height];
            for (int i=0;i<height;i++){m[i]= new Object[width];}
            // 일단 벽과 빈공간으로 초기화
            for (int j=0;j<height;j++){
                for (int i=0;i<width;i++)
                {
                    if (j==0 || j==(height-1) ||i==0|| i==(width-1)) { m[j][i] =NormalWall(j,i);}
                    else {m[j][i] = Space(j,i);} 
                }
            }
            // 꼭지점은 딴딴벽으로 
            m[0][width-1]=ImmueWall(0,width-1);
            m[0][0] = ImmueWall(0,0);
            m[height-1][0] = ImmueWall(height-1,0);
            m[height-1][width-1] = ImmueWall(height-1,width-1);
            
        }

        int getHeight(){return height;}
        int getWidth(){return width;}

        // 가로 벽 생성
        void makeHorizontal(int height)
        {
            for(int i = 4; i < width-4; i++)
            {
                if(m[height][i].getTN()==2) m[height][i] = ImmueWall(height, i);
                else m[height][i] = NormalWall(height, i);
            }
        }
        // 세로 벽 생성 
        void makeVertical(int width)
        {
            for(int i = 4; i < height-4; i++)
            {
                if(m[i][width].getTN()==2) m[i][width] = ImmueWall(i, width);
                else m[i][width] = NormalWall(i, width);
            }
        }
};


//----------------ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ--------전역함수----------------------- 
//시작화면
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
