#ifndef _MU_CRYPTO_H
#define _MU_CRYPTO_H

#define _MU_XOR3_KEY_  0xFC, 0xCF, 0xAB
#define _MU_MODULUS_KEY_ "webzen#@!01webzen#@!01webzen#@!0"

class AbstractCipher
{
	friend class MuCrypto;
public:
	AbstractCipher() {}
	virtual ~AbstractCipher() {}

protected:
	virtual bool Init(BYTE *key, DWORD length) = 0;
	virtual int Encrypt(BYTE *inBuf, size_t len, BYTE *outBuf) = 0;
	virtual int Decrypt(BYTE *inBuf, size_t len, BYTE *outBuf) = 0;

	int m_maxRunCount;
	int m_blockSize;
};


template <class CRYPTO, int MAX_RUN> 
class ConcreteCipher : public AbstractCipher
{
public:
	ConcreteCipher() {}
	virtual ~ConcreteCipher() {}

	bool Init(BYTE *key, DWORD length)
	{
		this->enc_.SetKey(key, this->enc_.DEFAULT_KEYLENGTH);
		this->dec_.SetKey(key, this->dec_.DEFAULT_KEYLENGTH);
		this->m_maxRunCount = MAX_RUN;
		this->m_blockSize = this->enc_.BLOCKSIZE;
		return true;

	}

	int Encrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
	{
		if (inBuf && outBuf && len)
		{
			for (int i = 0; i < len; i += this->dec_.BLOCKSIZE)
			{
				this->enc_.ProcessBlock(&inBuf[i], &outBuf[i]);
			}
			return len;
		}

		return -1;
	}

	int Decrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
	{
		if (inBuf && outBuf && len)
		{
			for (int i = 0; i < len; i += this->dec_.BLOCKSIZE)
			{
				this->dec_.ProcessBlock(&inBuf[i], &outBuf[i]);
			}
			return len;
		}

		return -1;
	}

	typename CRYPTO::Encryption enc_;
	typename CRYPTO::Decryption dec_;
};

class MuCrypto
{
public:
	MuCrypto(): _xor3key{ _MU_XOR3_KEY_ } {};
	virtual ~MuCrypto() {};

protected:
	BOOL InitModulusCrypto(DWORD algorithm, BYTE * key, DWORD keyLength);
	int ModulusEncrypt(BYTE *inBuf, size_t len, BYTE *outBuf);
	int ModulusDecrypt(BYTE *inBuf, size_t len, BYTE *outBuf);

	virtual DWORD CalculateCRC(BYTE *buf, int len, WORD wkey);
	virtual DWORD Xor3Byte(BYTE *buf, int len);
	BYTE _xor3key[3];

private:
	AbstractCipher * m_cipher;
	DWORD m_algorithm;
};

#endif