


#ifndef __SUFFIX_STRING_H_
#define __SUFFIX_STRING_H_
#include <vector>
#include <stddef.h> //for ptrdiff_t,size_t
#ifdef _MSC_VER
#   if (_MSC_VER < 1300)
        typedef signed int      int32_t;
#   else
        typedef signed __int32  int32_t;
#   endif
#else
#   include <stdint.h> //for int32_t
#endif

class TSuffixString{
public:
    typedef ptrdiff_t     TInt;
    TSuffixString();
    
    //throw std::runtime_error when create SA error
    TSuffixString(const char* src_begin,const char* src_end);
    void resetSuffixString(const char* src_begin,const char* src_end);

    inline const char* src_begin()const{ return m_src_begin; }
    inline const char* src_end()const{ return m_src_end; }
    inline size_t SASize()const{ return (size_t)(m_src_end-m_src_begin); }

    inline TInt SA(TInt i)const{//return m_SA[i];//排好序的后缀字符串数组.
        if (isUseLargeSA())
            return m_SA_large[i];
        else
            return (TInt)m_SA_limit[i];
    }
    TInt lower_bound(const char* str,const char* str_end)const;//return index in SA
private:
    typedef int32_t     TInt32;
    const char*         m_src_begin;//原字符串.
    const char*         m_src_end;
    std::vector<TInt32> m_SA_limit;
    std::vector<TInt>   m_SA_large;
    inline bool isUseLargeSA()const{
        static const int32_t kMaxLimitSize= (1<<30)-1 + (1<<30);//2G-1
        return (sizeof(TInt)>=sizeof(TInt32)) && (SASize()>(size_t)kMaxLimitSize);
    }
};

#endif //__SUFFIX_STRING_H_
