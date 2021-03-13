#include "MuCrypto.h"

#include "cryptopp/tea.h"
#include "cryptopp/3way.h"
#include "cryptopp/cast.h"
#include "cryptopp/rc5.h"
#include "cryptopp/rc6.h"
#include "cryptopp/mars.h"
#include "cryptopp/idea.h"
#include "cryptopp/gost.h"

BOOL MuCrypto::InitModulusCrypto(DWORD algorithm, BYTE * key, DWORD keyLength)
{
	typedef ConcreteCipher < CryptoPP::TEA, 1024 * 8 >			Cipher0;
	typedef ConcreteCipher < CryptoPP::ThreeWay, 1024 * 8 >		Cipher1;
	typedef ConcreteCipher < CryptoPP::CAST128, 1024 * 8 >		Cipher2;
	typedef ConcreteCipher < CryptoPP::RC5, 1024 * 8 >			Cipher3;
	typedef ConcreteCipher < CryptoPP::RC6, 1024 * 8 >			Cipher4;
	typedef ConcreteCipher < CryptoPP::MARS, 1024 * 8 >			Cipher5;
	typedef ConcreteCipher < CryptoPP::IDEA, 1024 * 8 >			Cipher6;
	typedef ConcreteCipher < CryptoPP::GOST, 1024 * 8 >			Cipher7;

	switch (algorithm & 7)	// algorithm % 8
	{
	case 0:
		this->m_cipher = sInstance(Cipher0);
		break;
	case 1:
		this->m_cipher = sInstance(Cipher1);
		break;
	case 2:
		this->m_cipher = sInstance(Cipher2);
		break;
	case 3:
		this->m_cipher = sInstance(Cipher3);
		break;
	case 4:
		this->m_cipher = sInstance(Cipher4);
		break;
	case 5:
		this->m_cipher = sInstance(Cipher5);
		break;
	case 6:
		this->m_cipher = sInstance(Cipher6);
		break;
	case 7:
		this->m_cipher = sInstance(Cipher7);
		break;
	default:	//should never reach here
		this->m_cipher = sInstance(Cipher7);
		break;
	}

	return this->m_cipher->Init(key, keyLength);
}

int MuCrypto::ModulusEncrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
{
	if (this->m_cipher)
		return this->m_cipher->Encrypt(inBuf, len, outBuf);

	return -1;
}

int MuCrypto::ModulusDecrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
{
	if (this->m_cipher)
		return this->m_cipher->Decrypt(inBuf, len, outBuf);

	return -1;
}

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


