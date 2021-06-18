#ifndef __OBJ__
#define __OBJ__

// 각 오브젝트의 속성을 담는 부모 클래스 (화면에 표시된 정사각형 하나하나가 오브젝트임)
class Object
{
    protected:
        int x,y;
        int typeNum;
        
    public:
        
        Object(int y=0, int x=0, int tn = 0):x(x), y(y) , typeNum(tn){}
        virtual ~Object(){}
        
        //좌표값 얻기
        int getY() {return y;}
        int getX() {return x;}
        void setYX(int y,int x){this->y=y;this->x=x;}
        //타입넘버 얻기
        int getTN(){return typeNum;}
        //타입넘버 세팅
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
#endif