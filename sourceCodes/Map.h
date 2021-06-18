#include "Object.h"


//--------------------------맵 클래스 ------------------------------
class Map
{
        int width;
        int height;
    
    friend class Snake;

    public:
        Object** m;

        //생성자
        Map(int w,int h);
        //게터
        int getHeight(){return height;}
        int getWidth(){return width;}

        // 가로 벽 생성
        void makeHorizontal(int height);
        // 세로 벽 생성 
        void makeVertical(int width);
};