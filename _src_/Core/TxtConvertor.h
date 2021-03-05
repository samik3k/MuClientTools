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
	virtual void MakeLabelEx(ofstream& os) {};

	//----------------------

	virtual BOOL Decrypt();
	virtual BOOL Encrypt();
	virtual void TxtOut(ofstream& os);
	virtual void TxtIn(ifstream& is);
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
void TxtConvertor<T>::TxtOut(ofstream & os)
{
	assert(os);

	static const vector<OffsetInfo> OFFSET = T::GetOffset();
	static const string LABEL = T::GetLabel();

	MakeLabelEx(os);
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		T* ptr = it->second;

		for (int i = 0; i < OFFSET.size(); i++)
		{
			int type = OFFSET[i].Type;
			size_t pos = OFFSET[i].Offset;
			if (pos < 0 || pos >= sizeof(T)) continue;

			pos += (size_t)ptr;
			switch (type)
			{
			case LAZY_TYPE_FLAG::_CSTR_:
				//if (Utls::IsEmptyCStr((const char*)pos))
				//	os << "[NULL]" << '\t';
				//else
				//	os << (const char*)pos << '\t';
				os << (const char*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_1BYTE_:
				os << (DWORD)(*(BYTE*)pos) << '\t';
				break;
			case LAZY_TYPE_FLAG::_1BYTE_ | LAZY_TYPE_FLAG::_SIGNED_:
				os << (int)(*(char*)pos) << '\t';
				break;
			case LAZY_TYPE_FLAG::_2BYTE_:
				os << *(WORD*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_2BYTE_ | LAZY_TYPE_FLAG::_SIGNED_:
				os << *(short*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_4BYTE_:
				os << *(DWORD*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_4BYTE_ | LAZY_TYPE_FLAG::_SIGNED_:
				os << *(int*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_FLOAT_:
				os << *(float*)pos << '\t';
				break;
			case LAZY_TYPE_FLAG::_DOUBLE_:
				os << *(double*)pos << '\t';
				break;
			default:
				break;
			}
		}

		os << endl;
	}
}

template<typename T>
void TxtConvertor<T>::TxtIn(ifstream & is)
{
	assert(is);

	static const vector<OffsetInfo> OFFSET = T::GetOffset();
	//static const string FORMAT = T::GetFormat();

	string line;
	size_t size = sizeof(T);
	size_t n = 0;

	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		T* ptr = (T*)&_buf[4 + (n * size)];
		memset(ptr, 0x00, size);

		line += '\t';
		size_t a = 0;
		size_t b = line.find('\t', a);
		size_t i = 0;
		do
		{
			if (b > a)
			{
				string s = line.substr(a, b - a);
				size_t pos = OFFSET[i].Offset + (size_t)ptr;
				sscanf(s.c_str(), OFFSET[i].Format.c_str(), (void*)pos);
			}

			i++;
			a = b + 1;
			b = line.find('\t', a);
		} while (b != string::npos && i < OFFSET.size());
		

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}

template<typename T>
BOOL TxtConvertor<T>::ComposeTxt(const char * szDestTxt)
{
	assert(_map.size() && szDestTxt);

	fs::path pFile = Utls::BackupPath(szDestTxt);
	Utls::CreateParentDir(pFile);

	ofstream os(pFile);
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