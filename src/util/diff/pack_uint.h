
#ifndef __PACK_UINT_H_
#define __PACK_UINT_H_

#include <vector>

//变长正整数编码方案(x bit额外类型标志位,x<=7),从高位开始输出1--n byte:
// x0*  7-x bit
// x1* 0*  7+7-x bit
// x1* 1* 0*  7+7+7-x bit
// x1* 1* 1* 0*  7+7+7+7-x bit
// x1* 1* 1* 1* 0*  7+7+7+7+7-x bit
// ...
template<class TUInt>
static void packUIntWithTag(std::vector<unsigned char>& out_code,TUInt iValue,int highBit,const int kTagBit){//写入并前进指针.
    const int kPackMaxTagBit=7;
    assert((0<=kTagBit)&&(kTagBit<=kPackMaxTagBit));
    assert((highBit>>kTagBit)==0);
    const int kMaxPackUIntByteSize=(kPackMaxTagBit+sizeof(TUInt)*8+6)/7;
    const TUInt kMaxValueWithTag=(1<<(7-kTagBit))-1;

    unsigned char codeBuf[kMaxPackUIntByteSize];
    unsigned char* codeEnd=codeBuf;
    while (iValue>kMaxValueWithTag) {
        *codeEnd=iValue&((1<<7)-1); ++codeEnd;
        iValue>>=7;
    }
    out_code.push_back((unsigned char)( (highBit<<(8-kTagBit)) | iValue | (((codeBuf!=codeEnd)?1:0)<<(7-kTagBit))  ));
    while (codeBuf!=codeEnd) {
        --codeEnd;
        out_code.push_back((*codeEnd) | (((codeBuf!=codeEnd)?1:0)<<7));
    }
}

template<class TUInt>
inline static void packUInt(std::vector<unsigned char>& out_code,TUInt iValue){
    packUIntWithTag(out_code,iValue,0,0);
}

#endif //__PACK_UINT_H_
