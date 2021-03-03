#include "ExcellentOptionBmd.h"

//------------------------------------------------------------------------
//--ExcellentOptionBmd
//------------------------------------------------------------------------

int ExcellentOptionBmd::GetKey(EXCELLENT_OPTION * ptr)
{
	return (ptr->Category << 8) | ptr->Number;;
}

void ExcellentOptionBmd::TxtOut(ofstream& os)
{
	assert(os);

	static const char* LABEL =
		"//Category\tNumber\tName\tOperator\tValue\tDmg\t"
		"Zen\tDmgChance\tOffense\tDefense\tLife\tMana\tOther";
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		EXCELLENT_OPTION* ptr = it->second;
		os << (DWORD)ptr->Category << '\t';
		os << (DWORD)ptr->Number << '\t';
		os << ptr->Name << '\t';
		os << (DWORD)ptr->Operator << '\t';
		os << ptr->Value << '\t';
		os << ptr->Dmg << '\t';
		os << (DWORD)ptr->Zen << '\t';
		os << (DWORD)ptr->DmgChance << '\t';
		os << (DWORD)ptr->Offense << '\t';
		os << (DWORD)ptr->Defense << '\t';
		os << (DWORD)ptr->Life << '\t';
		os << (DWORD)ptr->Mana << '\t';
		os << (DWORD)ptr->Other << '\t';

		os << endl;
	}
}

void ExcellentOptionBmd::TxtIn(ifstream& is)
{
	assert(is);

	string line;
	int size = sizeof(EXCELLENT_OPTION);
	int n = 0;
	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));
		EXCELLENT_OPTION* ptr = (EXCELLENT_OPTION*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			"%hhd\t%hhd\t%[^\t]%*c\t%hhd\t%d\t%d\t"
			"%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd"
			, &ptr->Category, &ptr->Number, &ptr->Name, &ptr->Operator, &ptr->Value, &ptr->Dmg
			, &ptr->Zen, &ptr->DmgChance, &ptr->Offense, &ptr->Defense, &ptr->Life, &ptr->Mana, &ptr->Other
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
