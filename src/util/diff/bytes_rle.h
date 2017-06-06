

#ifndef __BYTES_RLE_H_
#define __BYTES_RLE_H_

#include <vector>

enum TRleParameter{ kRle_bestSize=1, kRle_default=3, kRle_bestUnRleSpeed=32 };

void bytesRLE_save(std::vector<unsigned char>& out_code,const unsigned char* src,const unsigned char* src_end,int rle_parameter=kRle_default);

#endif //__BYTES_RLE_H_
