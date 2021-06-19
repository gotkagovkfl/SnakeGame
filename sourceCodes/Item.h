//기여도 
// 김중현 40 %
// 구예진 40 %
// 김유진 20 %

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
        void Init(Object**& m){while(numItem > 0) popItem(m);}  //@author 김유진(20203045)
        // 아이템 생성 (시간마다)
        void pushItem(Object**& m);   //@author 김중현(20163199)
        // 가장 오래된 아이템 제거 (시간 초과, 스테이지 클리어 시) 
        void popItem(Object**& m); //@author 구예진(20192004)
        // 특정 아이템 제거  (뱀과 접촉시)
        void eraseItem(int y,int x); //@author 구예진(20192004)
};
#endif