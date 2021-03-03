#pragma once
#define _MU_XOR3KEY_  0xFC, 0xCF, 0xAB

class MuCrypto
{
public:
	MuCrypto(): _xor3key{ _MU_XOR3KEY_ } {};
	virtual ~MuCrypto() {};

protected:
	virtual DWORD CalculateCRC(BYTE *buf, int len, WORD wkey);
	virtual DWORD Xor3Byte(BYTE *buf, int len);
	BYTE _xor3key[3];
};