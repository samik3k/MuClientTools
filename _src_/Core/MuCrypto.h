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
		enc_.SetKey(key, enc_.DEFAULT_KEYLENGTH);
		dec_.SetKey(key, dec_.DEFAULT_KEYLENGTH);
		m_maxRunCount = MAX_RUN;
		m_blockSize = enc_.BLOCKSIZE;
		return true;

	}

	int Encrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
	{
		if (inBuf && outBuf && len)
		{
			for (int i = 0; i < len; i += dec_.BLOCKSIZE)
			{
				enc_.ProcessBlock(&inBuf[i], &outBuf[i]);
			}
			return len;
		}

		return -1;
	}

	int Decrypt(BYTE *inBuf, size_t len, BYTE *outBuf)
	{
		if (inBuf && outBuf && len)
		{
			for (int i = 0; i < len; i += dec_.BLOCKSIZE)
			{
				dec_.ProcessBlock(&inBuf[i], &outBuf[i]);
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
	DWORD CalculateCRC(BYTE *buf, int len, WORD wkey);
	DWORD Xor3Byte(BYTE *buf, int len);
	BYTE _xor3key[3];

	BOOL InitModulusCrypto(DWORD algorithm, BYTE * key, DWORD keyLength);
	int BlockEncrypt(BYTE *inBuf, size_t len, BYTE *outBuf);
	int BlockDecrypt(BYTE *inBuf, size_t len, BYTE *outBuf);
	int GetBlockSize() { return m_cipher ? m_cipher->m_blockSize : 0; }

	BOOL ModulusEncrypt(std::vector<BYTE>& buf);
	BOOL ModulusDecrypt(std::vector<BYTE>& buf);

private:
	AbstractCipher * m_cipher;
};

#endif