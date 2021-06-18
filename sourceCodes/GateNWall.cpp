#include "GateNWall.h"
#include <random>
#include <time.h>

//생성자
GateNWall::GateNWall(Object**& m ,int h, int w):height(h),width(w)
{
    fillWalls(m); //기존의 벽 벡터를 지우고
    selectGate(m); //맵을 스캔하면서 벡터 재구성
}
// walls 벡터를 맵에서 일반 벽인 오브젝트로 채움
void GateNWall::fillWalls(Object**& m)
{
    walls.clear();
    
    for (int j=0;j<height;j++){
        for (int i=0;i<width;i++)
        {
            if (m[j][i].getTN()==2){walls.push_back(m[j][i]);}
        }
    }
}
//게이트 선택
void GateNWall::selectGate(Object** & m)
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

}
//게이트 되돌리기
void GateNWall::restore(Object**& m)
    {
        if (gateOpen)
        {
            m[gate1.getY()][gate1.getX()] = NormalWall(gate1.getY(),gate1.getX());
            m[gate2.getY()][gate2.getX()] = NormalWall(gate2.getY(),gate2.getX());
        }
    }
//게이트 출구 좌표구하기
void GateNWall::setExit(Object**& m,Object& g,int& toY,int& toX)
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