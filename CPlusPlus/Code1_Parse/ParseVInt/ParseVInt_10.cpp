#include "ParseVInt_10.h"

int32_t parse_vint(const char* sz_data, int& nlen)
{
	nlen = 0;
	unsigned char sz_buff[4] = {0};
	uint32_t n_buff = 0;

	uint32_t nRet = sz_data[nlen] & 0x7F;
	if( (sz_data[nlen]&0x80)!=0 )
	{
		nlen = nlen + 1;
		sz_buff[nlen] = sz_data[nlen] & 0x7F;
		n_buff = *(reinterpret_cast<uint32_t*>(sz_buff));
		n_buff = n_buff >> 1;
		nRet = nRet | n_buff;
		
		if( (sz_data[nlen]&0x80)!=0 )
		{
			nlen = nlen + 1;
			sz_buff[nlen-1] = {0};
			sz_buff[nlen] = sz_data[nlen] & 0x7F;
			n_buff = *(reinterpret_cast<uint32_t*>(sz_buff));
			n_buff = n_buff >> 2;
			nRet = nRet | n_buff;
			
			if( (sz_data[nlen]&0x80)!=0 )
			{
				nlen = nlen + 1;
				sz_buff[nlen-1] = {0};
				sz_buff[nlen] = sz_data[nlen] & 0x7F;
				n_buff = *(reinterpret_cast<uint32_t*>(sz_buff));
				n_buff = n_buff >> 3;
				nRet = nRet | n_buff;
				
				if( (sz_data[nlen]&0x80)!=0 )
				{
					nlen = nlen + 1;
					sz_buff[nlen-1] = {0};
					sz_buff[nlen] = sz_data[nlen] & 0x7F;
					n_buff = *(reinterpret_cast<uint32_t*>(sz_buff));
					n_buff = n_buff >> 4;
					nRet = nRet | n_buff;
				}
			}
		}
	}

	nRet = (nRet>>1)^-(nRet&1);
	nlen++;
	return (int32_t)nRet;
}