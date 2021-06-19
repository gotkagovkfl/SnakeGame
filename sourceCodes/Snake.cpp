#include "Snake.h"

//생성자
Snake::Snake(Object**& m,int h,int w) : tailY(h/2), tailX(w/2), mapHeight(h),mapWidth(w)
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
//맵전환시 뱀의 위치 초기화
void Snake::Init(Object**& m)
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

//뱀 몸통 생성
void Snake::pushBody(Object**& m)
{
    //기본 몸통생성 지점 
    int chaiY = s[numBody-1].getY()-s[numBody-2].getY();
    int chaiX = s[numBody-1].getX()-s[numBody-2].getX(); 
    
    int tempY;
    int tempX;
    // 원형 리스트의 시작 인덱스 구하기
    for(int i=0;i<4;i++)
    {
        if (nextTailPos[i][0]== chaiY && nextTailPos[i][1]== chaiX) {idxForFind=i;break;} 
    }
    //시계방향으로 탐색
    for (int i=0;i<4;i++)
    {
        tempY= tailY+nextTailPos[idxForFind][0],  
        tempX= tailX+nextTailPos[idxForFind][1]; // 현재 꼬리 위치에서 시계방향으로 찾기
        // 해당좌표가 빈공간이라면, 게이트의 출구임
        if (0<=tempY &&tempY<mapHeight&& 0<tempX &&tempX< mapWidth) // 시계방향으로 확인하는 좌표가 맵 밖이 아니어야함
        {
            if (m[tempY][tempX].getTN()==1){break;}   //탐색하는 좌표가 빈공간이면 원형리스트의 현재 인덱스를 사용함
        }
        ++idxForFind%=4;
    }
    int tempChaiY = nextTailPos[idxForFind][0];
    int tempChaiX = nextTailPos[idxForFind][1];
    
    tailY += tempChaiY;
    tailX += tempChaiX;
    Body tail(tailY,tailX);
    m[tailY][tailX] = tail;

    s.push_back(tail);
    numBody++;
}
//뱀 몸통 제거
void Snake::popBody(Object**& m)
{
    m[s[numBody-1].getY()][s[numBody-1].getX()] = Space(s[numBody-1].getY(),s[numBody-1].getX());
    s.pop_back();
    numBody--;
    tailY = s[numBody-1].getY();
    tailX = s[numBody-1].getX();
}
// 뱀의 몸통 위치 설정(바로앞의 몸통의 위치로 이동함) (머리는 제외)
void Snake::setBodyPos()
{
    for (int i=numBody-1; i>0; i--)
    {
        s[i].setYX(s[i-1].getY(),s[i-1].getX());
    }
}
//머리위치설정(next값을 설정하고 그 값으로 이동)
void Snake::setHeadPos()
{
    nextY = s[0].getY()+toY;
    nextX = s[0].getX()+toX;
    s[0].setYX(nextY,nextX);   
}
// 뱀의 이동
void Snake::move(Object**& m,Item& item, GateNWall& gnw)
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
void Snake::afterMove(Object**& m,Item& item,GateNWall& gnw)
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