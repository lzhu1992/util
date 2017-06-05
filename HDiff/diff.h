

#ifndef HDiff_diff_h
#define HDiff_diff_h

#include <vector>

//生成diff数据.
void create_diff(const unsigned char* newData,const unsigned char* newData_end,const unsigned char* oldData,const unsigned char* oldData_end,std::vector<unsigned char>& out_diff);
//检查生成的序列化的diff数据是否正确.
bool check_diff(const unsigned char* newData,const unsigned char* newData_end,const unsigned char* oldData,const unsigned char* oldData_end,const unsigned char* diff,const unsigned char* diff_end);

#endif
