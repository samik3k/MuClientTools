#include "MuCrypto.h"
DWORD MuCrypto::CalculateCRC(BYTE * buf, int len, WORD wkey)
{
	assert(buf);

	DWORD CRC = wkey << 9;
	for (int i = 0; i <= len - 4; i += 4)
	{
		DWORD temp = *(DWORD*)&buf[i];
		//memcpy(&temp, &buf[i], 4);
		if ((wkey + (i >> 2)) % 2 == 1)
			CRC += temp;
		else
			CRC ^= temp;
		if (i % 16 == 0)
			CRC ^= (CRC + wkey) >> ((i >> 2) % 8 + 1);
	}
	return CRC;
}

DWORD MuCrypto::Xor3Byte(BYTE * buf, int len)
{
	DWORD result = 0;
	for (int i = 0; i < len; ++i)
	{
		buf[i] ^= _xor3key[i % 3];
	}
	return result;
}
