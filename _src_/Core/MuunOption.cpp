#include "MuunOption.h"

// write the decrypted binary file -> to reverse the struct
//BOOL MuunOptionBmd::Unpack(const char * szSrcBmd, const char * szDestTxt)
//{
//	return FileOpen(szSrcBmd)
//		&& Decrypt()
//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
//}

int MuunOptionBmd::GetKey(MUUN_OPTION * ptr)
{
	return ptr->ID;
}

void MuunOptionBmd::TxtOut(ofstream & os)
{
	assert(os);

	static const char* LABEL =
		"//ID\tMuunID\tOptionName\tValueEvo\tValueLvl_1\tValueLvl_2\tValueLvl_3\tValueLvl_4\tValueLvl_5\t"
		"ConditionType_1\tOptionDesc\tConditionValue_1\tConditionValue_2\tConditionType_2";
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		MUUN_OPTION* ptr = it->second;
		os << ptr->ID << '\t';
		os << ptr->MuunID << '\t';
		os << ptr->OptionName << '\t';
		os << ptr->ValueEvo << '\t';
		os << ptr->ValueLvl_1 << '\t';
		os << ptr->ValueLvl_2 << '\t';
		os << ptr->ValueLvl_3 << '\t';
		os << ptr->ValueLvl_4 << '\t';
		os << ptr->ValueLvl_5 << '\t';
		os << (int)ptr->ConditionType_1 << '\t';
		os << ptr->OptionDesc << '\t';
		os << ptr->ConditionValue_1 << '\t';
		os << ptr->ConditionValue_2 << '\t';
		os << (int)ptr->ConditionType_2 << '\t';

		os << endl;
	}
}

void MuunOptionBmd::TxtIn(ifstream & is)
{
	assert(is);

	string line;
	int size = sizeof(MUUN_OPTION);
	int n = 0;
	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		MUUN_OPTION* ptr = (MUUN_OPTION*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			"%d\t%hd\t%[^\t]%*c\t%d\t%d\t%d\t%d\t%d\t%d\t%hhd\t%[^\t]%*c\t%d\t%d\t%hhd"
			, &ptr->ID, &ptr->MuunID, &ptr->OptionName, &ptr->ValueEvo, &ptr->ValueLvl_1, &ptr->ValueLvl_2, &ptr->ValueLvl_3
			, &ptr->ValueLvl_4, &ptr->ValueLvl_5, &ptr->ConditionType_1, &ptr->OptionDesc, &ptr->ConditionValue_1, &ptr->ConditionValue_2, &ptr->ConditionType_2
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
