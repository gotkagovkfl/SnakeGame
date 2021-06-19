#include "Map.h"

//생성자
Map::Map(int w,int h): width(w), height(h)
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

// 가로 벽 생성

void Map::makeHorizontal(int height)
{
    for(int i = 4; i < width-4; i++)
    {
        if(m[height][i].getTN()==2) m[height][i] = ImmueWall(height, i);
        else m[height][i] = NormalWall(height, i);
    }
}
// 세로 벽 생성 
//@author 김유진(20203045)
void Map::makeVertical(int width)
{
    for(int i = 4; i < height-4; i++)
    {
        if(m[i][width].getTN()==2) m[i][width] = ImmueWall(i, width);
        else m[i][width] = NormalWall(i, width);
    }
}