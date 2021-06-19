//기여도 
// 김중현 40 %
// 김유진 60 %

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
        Map(int w,int h); //@김중현(20163199)
        //게터
        int getHeight(){return height;} 
        int getWidth(){return width;}

        // 가로 벽 생성
        void makeHorizontal(int height); //@author 김유진(20203045)
        // 세로 벽 생성 
        void makeVertical(int width);  //@author 김유진(20203045)
};