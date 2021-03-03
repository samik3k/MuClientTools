#include "PentagramMixNeedSourceBmd.h"


int PentagramMixNeedSourceBmd::GetKey(PENTAGRAM_MIX_SOURCE * ptr)
{
	return (ptr->Category << 8) | ptr->Index;
}

void PentagramMixNeedSourceBmd::MakeLabel(ofstream & os)
{
	assert(os);

	os << "// Cat0: Material Combination" << endl;
	os << "// Cat1: Errtel" << endl;
	os << "// Cat2 : Errtel Level Upgrade" << endl;
	os << "// Cat3 : Errtel Rank Upgrade" << endl;
	os << "// Cat4: Errtal Socket Upgrade" << endl;
	os << "// Cat5: Wing Add Option" << endl;
	os << "// Cat6: Wing Option Level Upgrade" << endl;

	os << "//Category\tIndex\tSuccessRate_Cat0";
	char temp[64];
	for (int i = 0; i < 5; i++)
	{
		sprintf(temp, "\tItemID_%d", i);
		os << temp;
	}
	for (int i = 0; i < 5; i++)
	{
		sprintf(temp, "\tItemCat_%d", i);
		os << temp;
	}
	for (int i = 0; i < 5; i++)
	{
		sprintf(temp, "\tItemIndex_%d", i);
		os << temp;
	}
	for (int i = 0; i < 5; i++)
	{
		sprintf(temp, "\tItemCount_%d", i);
		os << temp;
	}

	os << "\tMoneyNeed\tItemLevelNeed\tErrtelRankNeed\tErrtelCount";

	os << endl;
}

void PentagramMixNeedSourceBmd::TxtOut(ofstream & os)
{
	assert(os);

	MakeLabel(os);

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		PENTAGRAM_MIX_SOURCE* ptr = it->second;
		os << ptr->Category << '\t';
		os << ptr->Index << '\t';
		os << ptr->SuccessRate_Cat0 << '\t';
		for (int i = 0; i < 5; i++)
			os << ptr->ItemID[i] << '\t';
		for (int i = 0; i < 5; i++)
			os << ptr->ItemCat[i] << '\t';
		for (int i = 0; i < 5; i++)
			os << ptr->ItemIndex[i] << '\t';
		for (int i = 0; i < 5; i++)
			os << ptr->ItemCount[i] << '\t';
		os << ptr->MoneyNeed << '\t';
		os << ptr->ItemLevelNeed << '\t';
		os << ptr->ErrtelRankNeed << '\t';
		os << ptr->ErrtelCount << '\t';
		for (int i = 0; i < 5; i++)
			os << ptr->SuccessRate_Cat1[i] << '\t';
		for (int i = 0; i < 4; i++)
			os << ptr->Unk_Block[i] << '\t';

		os << endl;
	}
}

void PentagramMixNeedSourceBmd::TxtIn(ifstream & is)
{
	assert(is);

	string line;
	int size = sizeof(PENTAGRAM_MIX_SOURCE);
	int n = 0;
	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		PENTAGRAM_MIX_SOURCE* ptr = (PENTAGRAM_MIX_SOURCE*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
			"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t"
			"%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d"
			, &ptr->Category, &ptr->Index, &ptr->SuccessRate_Cat0, &ptr->ItemID[0]
			, &ptr->ItemID[1], &ptr->ItemID[2], &ptr->ItemID[3], &ptr->ItemID[4]
			, &ptr->ItemCat[0], &ptr->ItemCat[1], &ptr->ItemCat[2], &ptr->ItemCat[3]
			, &ptr->ItemCat[4], &ptr->ItemIndex[0], &ptr->ItemIndex[1], &ptr->ItemIndex[2]
			, &ptr->ItemIndex[3], &ptr->ItemIndex[4], &ptr->ItemCount[0], &ptr->ItemCount[1]
			, &ptr->ItemCount[2], &ptr->ItemCount[3], &ptr->ItemCount[4], &ptr->MoneyNeed
			, &ptr->ItemLevelNeed, &ptr->ErrtelRankNeed, &ptr->ErrtelCount, &ptr->SuccessRate_Cat1[0]
			, &ptr->SuccessRate_Cat1[1], &ptr->SuccessRate_Cat1[2], &ptr->SuccessRate_Cat1[3], &ptr->SuccessRate_Cat1[4]
			, &ptr->Unk_Block[0], &ptr->Unk_Block[1], &ptr->Unk_Block[2], &ptr->Unk_Block[3]
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
