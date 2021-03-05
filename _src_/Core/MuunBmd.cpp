#include "MuunBmd.h"

//------------------------------------------------------------------------
//--MuunOptionBmd
//------------------------------------------------------------------------

int MuunOptionBmd::GetKey(MUUN_OPTION * ptr)
{
	return ptr->ID;
}

void MuunOptionBmd::TxtOut(ofstream & os)
{
	assert(os);

	//	"//ID\tMuunID\tOptionName\tValueEvo\tValueLvl_1\tValueLvl_2\tValueLvl_3\tValueLvl_4\tValueLvl_5\t"
	//	"ConditionType_1\tOptionDesc\tConditionValue_1\tConditionValue_2\tConditionType_2";
	static const string LABEL = MUUN_OPTION::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		MUUN_OPTION* ptr = it->second;
		os << ptr->ID << '\t';
		os << ptr->MuunID << '\t';
		os << (Utls::IsEmptyCStr(ptr->OptionName) ? "[NULL]" : ptr->OptionName) << '\t';
		os << ptr->ValueEvo << '\t';
		os << ptr->ValueLvl_1 << '\t';
		os << ptr->ValueLvl_2 << '\t';
		os << ptr->ValueLvl_3 << '\t';
		os << ptr->ValueLvl_4 << '\t';
		os << ptr->ValueLvl_5 << '\t';
		os << (int)ptr->ConditionType_1 << '\t';
		os << (Utls::IsEmptyCStr(ptr->OptionDesc) ? "[NULL]" : ptr->OptionDesc) << '\t';
		os << ptr->ConditionValue_1 << '\t';
		os << ptr->ConditionValue_2 << '\t';
		os << (int)ptr->ConditionType_2 << '\t';

		os << endl;
	}
}

void MuunOptionBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = MUUN_OPTION::GetFormat();

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
			//"%d\t%hd\t%[^\t]%*c\t%d\t%d\t%d\t%d\t%d\t%d\t%hhd\t%[^\t]%*c\t%d\t%d\t%hhd"
			FORMAT.c_str()
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

//------------------------------------------------------------------------
//--MuunInfoBmd
//------------------------------------------------------------------------

int MuunInfoBmd::GetKey(MUUN_INFO * ptr)
{
	return ptr->ID;
}

void MuunInfoBmd::TxtOut(ofstream & os)
{
	assert(os);

	static const string LABEL = MUUN_INFO::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		MUUN_INFO* ptr = it->second;
		os << ptr->ID << '\t';
		os << ptr->MuunID << '\t';
		os << (DWORD)ptr->Type << '\t';
		os << (DWORD)ptr->Rank << '\t';
		os << ptr->OptionIndex << '\t';
		os << ptr->AddOptionType << '\t';
		os << ptr->AddOptionValue << '\t';
		os << ptr->AddOptCheckType << '\t';
		os << ptr->OptionStartDate_Year << '\t';
		os << ptr->OptionStartDate_Month << '\t';
		os << ptr->OptionStartDate_Day << '\t';
		os << ptr->OptionEndDate_Year << '\t';
		os << ptr->OptionEndDate_Month << '\t';
		os << ptr->OptionEndDate_Day << '\t';
		os << ptr->EvoID << '\t';
		os << ptr->SkillDelayTime << '\t';

		os << endl;
	}
}

void MuunInfoBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = MUUN_INFO::GetFormat();

	string line;
	int size = sizeof(MUUN_INFO);
	int n = 0;

	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		MUUN_INFO* ptr = (MUUN_INFO*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			FORMAT.c_str()
			, &ptr->ID, &ptr->MuunID, &ptr->Type, &ptr->Rank, &ptr->OptionIndex, &ptr->AddOptionType, &ptr->AddOptionValue, &ptr->AddOptCheckType, &ptr->OptionStartDate_Year
			, &ptr->OptionStartDate_Month, &ptr->OptionStartDate_Day, &ptr->OptionEndDate_Year, &ptr->OptionEndDate_Month, &ptr->OptionEndDate_Day, &ptr->EvoID, &ptr->SkillDelayTime
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}

//------------------------------------------------------------------------
//--MuunTooltipInfoBmd
//------------------------------------------------------------------------

// write the decrypted binary file -> to reverse the struct
//BOOL MuunTooltipInfoBmd::Unpack(const char * szSrcBmd, const char * szDestTxt)
//{
//	return FileOpen(szSrcBmd)
//		&& Decrypt()
//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
//}

int MuunTooltipInfoBmd::GetKey(MUUN_TOOLTIP_INFO * ptr)
{
	return ptr->MuunID;
}

void MuunTooltipInfoBmd::TxtOut(ofstream & os)
{
	assert(os);

	static const string LABEL = MUUN_TOOLTIP_INFO::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		MUUN_TOOLTIP_INFO* ptr = it->second;
		os << ptr->MuunID << '\t';
		os << ptr->Translate_X << '\t';
		os << ptr->Translate_Y << '\t';
		os << ptr->Translate_Z << '\t';
		os << ptr->Rotate_X << '\t';
		os << ptr->Rotate_Y << '\t';
		os << ptr->Rotate_Z << '\t';
		os << ptr->Scale << '\t';


		os << endl;
	}
}

void MuunTooltipInfoBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = MUUN_TOOLTIP_INFO::GetFormat();

	string line;
	int size = sizeof(MUUN_TOOLTIP_INFO);
	int n = 0;

	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		MUUN_TOOLTIP_INFO* ptr = (MUUN_TOOLTIP_INFO*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			FORMAT.c_str()
			, &ptr->MuunID, &ptr->Translate_X, &ptr->Translate_Y, &ptr->Translate_Z
			, &ptr->Rotate_X, &ptr->Rotate_Y, &ptr->Rotate_Z, &ptr->Scale
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
