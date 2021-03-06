#include "Core.h"
#include "MuunExchangeBmd.h"

//BOOL MuunExchangeBmd::Unpack(const char * szSrcBmd, const char * szDestTxt)
//{
//	return FileOpen(szSrcBmd)
//		&& Decrypt()
//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
//}

BOOL MuunExchangeBmd::Decrypt()
{
	assert(_buf.size() > 12);

	int size = sizeof(MUUN_EXCHANGE);
	int count1 = *(int*)&_buf[0];
	int count2 = *(int*)&_buf[4];

	DWORD CRC = *(DWORD*)&_buf[_buf.size() - 4];
	if (CRC != CalculateCRC(&_buf[8], _buf.size() - 12, _wkey))
	{
		cout << "Warning: CRC check failed. (may be a wrong file) \n";
#ifdef STRICT_CRC_CHECK
		return FALSE;
#endif
	}

	if ((_buf.size() - 12) != ((count1 + count2) * size))
	{
		cout << "Warning: InputFile size check failed. (may be a wrong file) \n";
#ifdef STRICT_SIZE_CHECK
		return FALSE;
#endif
	}

	int pos = 8, err = -1;
	for (int i = 0; i < count1; i++)
	{
		Xor3Byte(&_buf[pos], size);
		MUUN_EXCHANGE* ptr = (MUUN_EXCHANGE*)&_buf[pos];
		int key = (0 << 8) | ptr->Column_4;
		_map.insert(make_pair(key, ptr));
		pos += size;
	}

	for (int i = 0; i < count2; i++)
	{
		Xor3Byte(&_buf[pos], size);
		MUUN_EXCHANGE* ptr = (MUUN_EXCHANGE*)&_buf[pos];
		int key = (1 << 8) | ptr->Column_1;
		_map.insert(make_pair(key, ptr));
		pos += size;
	}

	return TRUE;
}

BOOL MuunExchangeBmd::Encrypt()
{
	assert(_buf.size() > 12);

	int size = sizeof(MUUN_EXCHANGE);
	for (int p = 8; p + size < _buf.size(); p += size)
	{
		Xor3Byte(&_buf[p], size);
	}
	DWORD CRC = CalculateCRC(&_buf[8], _buf.size() - 12, _wkey);
	*(DWORD*)&_buf[_buf.size() - 4] = CRC;

	_map.clear(); // T* now -> encrypted data
	return TRUE;
}

void MuunExchangeBmd::TxtOut(ofstream & os)
{
	assert(os);

	os << "//Group0: Required Item Exchange" << endl;
	os << "//Group\tItemID\tCount\tInventoryType\tExchangeType" << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		if ((it->first >> 8) == 0)
		{
			MUUN_EXCHANGE* ptr = it->second;
			os << "0" << '\t';
			os << ptr->Column_1 << '\t';
			os << ptr->Column_2 << '\t';
			os << ptr->Column_3 << '\t';
			os << ptr->Column_4 << '\t';
			os << endl;
		}
	}

	os << "//Group1: Exchange Type" << endl;
	os << "//Group\tExchangeType\tEvoStoneID\tMuunEvoID\tInventoryType" << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		if ((it->first >> 8) == 1)
		{
			MUUN_EXCHANGE* ptr = it->second;
			os << "1" << '\t';
			os << ptr->Column_1 << '\t';
			os << ptr->Column_2 << '\t';
			os << ptr->Column_3 << '\t';
			os << ptr->Column_4 << '\t';
			os << endl;
		}
	}
}

void MuunExchangeBmd::TxtIn(ifstream & is)
{
	assert(is);

	string line;
	int size = sizeof(MUUN_EXCHANGE);
	int n = 0;
	_map.clear();

	map<int, vector<MUUN_EXCHANGE>> temp;

	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		MUUN_EXCHANGE mex;
		int group;
		sscanf(line.c_str(),
			"%d\t%d\t%d\t%d\t%d"
			, &group, &mex.Column_1, &mex.Column_2, &mex.Column_3, &mex.Column_4
		);
		temp[group].push_back(mex);
		n++;
	}

	_buf.resize(8 + (n * size) + 4);

	*(DWORD*)&_buf[0] = temp[0].size();
	*(DWORD*)&_buf[4] = temp[1].size();

	int pos = 8;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < temp[i].size(); j++)
		{
			MUUN_EXCHANGE* dst = (MUUN_EXCHANGE*)&_buf[pos];
			MUUN_EXCHANGE* src = &temp[i][j];
			memcpy(dst, src, size);

			int key = i == 0 ? dst->Column_4 : (1 << 8) | dst->Column_1;
			_map.insert(make_pair(key, dst));
			pos += size;

		}
	}
}
