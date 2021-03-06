#include "FormulaDataBmd.h"

BOOL FormulaDataBmd::Decrypt()
{
	assert(_buf.size() > 12);

	int size = sizeof(FORMULA_DATA);
	int total = *(int*)&_buf[0];
	int group_count = *(int*)&_buf[4];

	DWORD CRC = *(DWORD*)&_buf[_buf.size() - 4];
	if (CRC != CalculateCRC(&_buf[8], _buf.size() - 12, _wkey))
	{
		cout << "Warning: CRC check failed. (may be a wrong file) \n";
#ifdef STRICT_CRC_CHECK
		return FALSE;
#endif
	}

	if ((_buf.size() - 12) != ((total * size) + (4 * group_count)))
	{
		cout << "Warning: InputFile size check failed. (may be a wrong file) \n";
#ifdef STRICT_SIZE_CHECK
		return FALSE;
#endif
	}

	int pos = 8, err = -1;
	for (int i = 0; i < group_count; i++)
	{
		Xor3Byte(&_buf[pos], 4);
		int sub_count = *(int*)&_buf[pos];
		pos += 4;
		for (int j = 0; j < sub_count; j++)
		{
			Xor3Byte(&_buf[pos], size);
			FORMULA_DATA* pData = (FORMULA_DATA*)&_buf[pos];
			int key = (i << 8) | j;
			while (_map.find(key) != _map.end())	//check duplicated keys
			{
				key = err;
				err--;
			}
			_map.insert(make_pair(key, pData));
			pos += size;
		}
	}

	return TRUE;
}

BOOL FormulaDataBmd::Encrypt()
{
	assert(_buf.size() > 12);
	int size = sizeof(FORMULA_DATA);
	int total = *(int*)&_buf[0];
	int group_count = *(int*)&_buf[4];

	assert(_buf.size() == 12 + (total * size) + (group_count * 4));

	int pos = 8;
	for (int i = 0; i < group_count; i++)
	{
		int sub_count = *(int*)&_buf[pos];
		Xor3Byte(&_buf[pos], 4);
		pos += 4;
		for (int j = 0; j < sub_count; j++)
		{
			Xor3Byte(&_buf[pos], size);
			pos += size;
		}
	}
	DWORD CRC = CalculateCRC(&_buf[8], _buf.size() - 12, _wkey);
	*(DWORD*)&_buf[_buf.size() - 4] = CRC;

	_map.clear();

	return TRUE;
}

void FormulaDataBmd::TxtOut(ofstream & os)
{
	assert(os);

	//	"//Group\tID\tFormula_Text";
	static const string LABEL = "//Group\t" + FORMULA_DATA::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		FORMULA_DATA* ptr = it->second;
		int group = (it->first >> 8);
		os << group << '\t';
		os << ptr->ID << '\t';
		os << (Utls::IsEmptyCStr(ptr->Text) ? "[NULL]" : ptr->Text) << '\t';

		os << endl;
	}
}

void FormulaDataBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = "%d\t" + FORMULA_DATA::GetFormat();

	string line;
	int size = sizeof(FORMULA_DATA);
	int n = 0;

	map<int, vector<FORMULA_DATA>> temp;
	_map.clear();

	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		FORMULA_DATA Data;
		int group;
		sscanf(line.c_str(),
			//"%d\t%d\t%[^\t]%*c"
			FORMAT.c_str()
			, &group, &Data.ID, &Data.Text);
		temp[group].push_back(Data);
		n++;
	}
	int group_count = temp.size();
	_buf.resize(12 + (n * size) + (group_count *  4));
	*(DWORD*)&_buf[0] = n;
	*(DWORD*)&_buf[4] = temp.size();

	int pos = 8;
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		int group = it->first;
		int sub_count = it->second.size();
		*(int*)&_buf[pos] = sub_count;
		pos += 4;
		for (int i = 0; i < sub_count; i++)
		{
			FORMULA_DATA* ptr = &it->second[i];
			memcpy(&_buf[pos], ptr, size);
			int key = (group << 8) | ptr->ID;
			_map.insert(make_pair(key, (FORMULA_DATA*)&_buf[pos]));
			pos += size;
		}
	}
}
