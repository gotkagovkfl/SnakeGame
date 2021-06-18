#include "Object.h"


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