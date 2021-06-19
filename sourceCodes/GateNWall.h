//@author 김중현(201631999) 100%

#ifndef __GATE__
#define __GATE__

#include <vector>

#include "Object.h"

using namespace std;

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
        GateNWall(Object**& m ,int h, int w);
        // walls 벡터를 맵에서 일반 벽인 오브젝트로 채움
        void fillWalls(Object**& m);
        //게이트 선택
        void selectGate(Object** & m);
        //게이트 되돌리기
        void restore(Object**& m);
        //게이트 출구 좌표구하기
        void setExit(Object**& m,Object& g,int& toY,int& toX);
};

#endif