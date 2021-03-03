#ifndef TXT_CONVERTOR_H
#define TXT_CONVERTOR_H

#define _COMMON_TXTCONVERTOR_WKEY_ 0xE2F1

template<typename T>
class TxtConvertor : public BaseIO
{
public:
	TxtConvertor(WORD w) : _wkey(w) {};
	virtual ~TxtConvertor() {};

	virtual BOOL Unpack(const char *szSrcBmd, const char *szDestTxt);
	virtual BOOL Pack(const char *szSrcTxt, const char *szDestBmd);

	map<int, T*> _map;	//make public for further ref. (temporary)
protected:
	virtual int GetKey(T* pT) = 0;
	virtual void TxtOut(ofstream& os) = 0;
	virtual void TxtIn(ifstream& is) = 0;

	virtual BOOL Decrypt();
	virtual BOOL Encrypt();
	virtual BOOL ComposeTxt(const char *szDestTxt);
	virtual BOOL ParseTxt(const char *szSrcTxt);

	WORD _wkey;
};

//--END HEADER PART

//------------------------------------------------------------------------
//--TxtConvertor
//------------------------------------------------------------------------

template<typename T>
inline BOOL TxtConvertor<T>::Unpack(const char * szSrcBmd, const char * szDestTxt)
{
	return FileOpen(szSrcBmd)
		&& Decrypt()
		&& ComposeTxt(szDestTxt ? szDestTxt : fs::path(szSrcBmd).replace_extension("txt").string().c_str());
}

template<typename T>
inline BOOL TxtConvertor<T>::Pack(const char * szSrcTxt, const char * szDestBmd)
{
	return ParseTxt(szSrcTxt)
		&& Encrypt()
		&& FileWrite(szDestBmd ? szDestBmd : fs::path(szSrcTxt).replace_extension(".out.bmd").string().c_str());
}

template<typename T>
BOOL TxtConvertor<T>::Decrypt()
{
	assert(_buf.size() > 8);

	const int size = sizeof(T);

	DWORD CRC = *(DWORD*)&_buf[_buf.size() - 4];
	if (CRC != CalculateCRC(&_buf[4], _buf.size() - 8, _wkey))
	{
		cout << "Warning: CRC check failed. (may be a wrong file) \n";
#ifdef STRICT_CRC_CHECK
		return FALSE;
#endif
	}

	int N = *(int*)&_buf[0];
	if ((_buf.size() - 8) != N * size)
	{
		cout << "Warning: InputFile size check failed. (may be a wrong file) \n";
#ifdef STRICT_SIZE_CHECK
		return FALSE;
#endif
	}

	_map.clear();

	int err = -1;
	for (int p = 4; p + size < _buf.size(); p += size)
	{
		Xor3Byte(&_buf[p], size);

		T *pT = (T *)&_buf[p];
		int key = GetKey(pT);
		while (_map.find(key) != _map.end())	//check duplicated keys
		{
			key = err;
			err--;
		}
		_map.insert(make_pair(key, pT));
	}

	return TRUE;
}

template<typename T>
BOOL TxtConvertor<T>::Encrypt()
{
	assert(_buf.size() > 8);

	int size = sizeof(T);
	for (int p = 4; p + size < _buf.size(); p += size)
	{
		Xor3Byte(&_buf[p], size);
	}
	DWORD CRC = CalculateCRC(&_buf[4], _buf.size() - 8, _wkey);
	*(DWORD*)&_buf[_buf.size() - 4] = CRC;

	_map.clear(); // T* now -> encrypted data
	return TRUE;
}

template<typename T>
BOOL TxtConvertor<T>::ComposeTxt(const char * szDestTxt)
{
	assert(_map.size() && szDestTxt);

	fs::path pFile = BackupPath(szDestTxt);
	CreateParentDir(pFile);

	ofstream os(pFile, ios::out | ios::binary);
	if (!os.is_open())
	{
		cout << "Error: Failed to write the txt file: " << pFile << '\n';
		return FALSE;
	}

	TxtOut(os);

	os.close();

	return TRUE;
}

template<typename T>
BOOL TxtConvertor<T>::ParseTxt(const char * szSrcTxt)
{
	assert(szSrcTxt);

	ifstream is(szSrcTxt);
	if (!is.is_open())
	{
		cout << "Error: Failed to read the txt file: " << szSrcTxt << '\n';
		return FALSE;
	}

	_map.clear();

	TxtIn(is);

	is.close();

	return TRUE;
}
#endif