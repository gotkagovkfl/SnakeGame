#include <vector>
#include "Object.h"
#include "GateNWall.h"
#include "Item.h"

using namespace std;

extern int mapWidth;
extern int mapHeight;
extern int gateUse;
extern void fail();

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
        
        //생성자
        Snake(Object**& m,int h,int w);

        // 머리방향조절
        void setToY(int y){toY=y;}
        void setToX(int x){toX=x;}
        //머리 방향 값 얻기
        int getToY(){return toY;}
        int getToX(){return toX;}

        //게이트 통과중임을 나타내는 상태변수 조정
        void setOnGate(){onGate=numBody;}
        void decreaseOnGate(){if(onGate){onGate--;}}

        //맵전환시 뱀의 위치 초기화
        void Init(Object**& m);

        //뱀 몸통 생성
        void pushBody(Object**& m);
        //뱀 몸통 제거
        void popBody(Object**& m);
        // 뱀의 몸통 위치 설정(바로앞의 몸통의 위치로 이동함) (머리는 제외)
        void setBodyPos();
        //머리위치설정(next값을 설정하고 그 값으로 이동)
        void setHeadPos();
        // 뱀의 이동
        void move(Object**& m,Item& item, GateNWall& gnw);
        //이동한 곳에 뭔가 있는 경우
        void afterMove(Object**& m,Item& item,GateNWall& gnw);
};