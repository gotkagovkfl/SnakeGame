#ifndef __ITEM__
#define __ITEM__

#include <vector>
#include <time.h>
#include <random>
#include "Object.h"

using namespace std;

//-----------------------아이템 클래스---------------- 
class Item
{
    protected:
        int height;
        int width;
    public:
        int numItem=0;
        vector <Object> it;

        Item(Object**& m, int h, int w): height(h), width(w) { }

        //초기화 함수
        void Init(Object**& m){while(numItem > 0) popItem(m);}
        // 아이템 생성 (시간마다)
        void pushItem(Object**& m);
        // 가장 오래된 아이템 제거 (시간 초과, 스테이지 클리어 시)
        void popItem(Object**& m);
        // 특정 아이템 제거  (뱀과 접촉시)
        void eraseItem(int y,int x);
};

#endif