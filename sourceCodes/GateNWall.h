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

#endif