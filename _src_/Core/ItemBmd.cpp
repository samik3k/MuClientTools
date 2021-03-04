#include "ItemBmd.h"

//------------------------------------------------------------------------
//--ItemBmd
//------------------------------------------------------------------------

int ItemBmd::GetKey(ITEM_ATTRIBUTE * ptr)
{
	int check_index = (ptr->ItemSubGroup * 512) + ptr->ItemSubIndex;
	if (ptr->ItemIndex != check_index)
	{
		return -1;	//it will push the problematic row to the top of the out.txt file
	}

	return ptr->ItemIndex;
}

void ItemBmd::TxtOut(ofstream & os)
{
	assert(os);

	//	"//ItemIndex\tItemSubGroup\tItemSubIndex\tszModelFolder\tszModelName\tszItemName\t"
	//	"KindA\tKindB\tType\tTwoHands\tDropLevel\tSlot\tSkillIndex\tWidth\tHeight\tDamageMin\tDamageMax\tDefenseRate\t"
	//	"Defense\tMagicResistance\tAttackSpeed\tWalkSpeed\tDurability\tMagicDur\tMagicPower\tReqStr\tReqDex\tReqEne\tReqVit\t"
	//	"ReqCmd\tReqLvl\tItemValue\tMoney\tSetAttr\tClass_0\tClass_1\tClass_2\tClass_3\tClass_4\tClass_5\tClass_6\tClass_7\t"
	//	"Res_0\tRes_1\tRes_2\tRes_3\tRes_4\tRes_5\tRes_6\tDump\tTransaction\tPersonalStore\tWarehouse\tSellNpc\tExpensive\t"
	//	"Repair\tOverlap\tUnk_End";
	static const string LABEL = ITEM_ATTRIBUTE::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		ITEM_ATTRIBUTE* ptr = it->second;
		os << (DWORD)ptr->ItemIndex << '\t';
		os << (DWORD)ptr->ItemSubGroup << '\t';
		os << (DWORD)ptr->ItemSubIndex << '\t';
		os << (Utls::IsEmptyCStr(ptr->szModelFolder) ? "[NULL]" : ptr->szModelFolder) << '\t';
		os << (Utls::IsEmptyCStr(ptr->szModelName) ? "[NULL]" : ptr->szModelName) << '\t';
		os << (Utls::IsEmptyCStr(ptr->szItemName) ? "[NULL]" : ptr->szItemName) << '\t';
		os << (DWORD)ptr->KindA << '\t';
		os << (DWORD)ptr->KindB << '\t';
		os << (DWORD)ptr->Type << '\t';
		os << (DWORD)ptr->TwoHands << '\t';
		os << (DWORD)ptr->DropLevel << '\t';
		os << (DWORD)ptr->Slot << '\t';
		os << (DWORD)ptr->SkillIndex << '\t';
		os << (DWORD)ptr->Width << '\t';
		os << (DWORD)ptr->Height << '\t';
		os << (DWORD)ptr->DamageMin << '\t';
		os << (DWORD)ptr->DamageMax << '\t';
		os << (DWORD)ptr->DefenseRate << '\t';
		os << (DWORD)ptr->Defense << '\t';
		os << (DWORD)ptr->MagicResistance << '\t';
		os << (DWORD)ptr->AttackSpeed << '\t';
		os << (DWORD)ptr->WalkSpeed << '\t';
		os << (DWORD)ptr->Durability << '\t';
		os << (DWORD)ptr->MagicDur << '\t';
		os << (DWORD)ptr->MagicPower << '\t';
		os << (DWORD)ptr->ReqStr << '\t';
		os << (DWORD)ptr->ReqDex << '\t';
		os << (DWORD)ptr->ReqEne << '\t';
		os << (DWORD)ptr->ReqVit << '\t';
		os << (DWORD)ptr->ReqCmd << '\t';
		os << (DWORD)ptr->ReqLvl << '\t';
		os << (DWORD)ptr->ItemValue << '\t';
		os << (DWORD)ptr->Money << '\t';
		os << (DWORD)ptr->SetAttr << '\t';
		for (int i = 0; i < 8; i++)
			os << (DWORD)ptr->Classes[i] << '\t';
		for (int i = 0; i < 7; i++)
			os << (DWORD)ptr->Resistances[i] << '\t';
		os << (DWORD)ptr->Dump << '\t';
		os << (DWORD)ptr->Transaction << '\t';
		os << (DWORD)ptr->PersonalStore << '\t';
		os << (DWORD)ptr->Warehouse << '\t';
		os << (DWORD)ptr->SellNpc << '\t';
		os << (DWORD)ptr->Expensive << '\t';
		os << (DWORD)ptr->Repair << '\t';
		os << (DWORD)ptr->Overlap << '\t';
		os << (DWORD)ptr->Unk_End << '\t';

		os << endl;
	}
}

void ItemBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = ITEM_ATTRIBUTE::GetFormat();
	string line;
	int size = sizeof(ITEM_ATTRIBUTE);
	int n = 0;

	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		ITEM_ATTRIBUTE* ptr = (ITEM_ATTRIBUTE*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			//"%d\t%hd\t%hd\t%[^\t]%*c\t%[^\t]%*c\t%[^\t]%*c\t%hhd\t%hhd\t%hhd\t%hhd\t"
			//"%hd\t%hhd\t%hd\t%hhd\t%hhd\t%hd\t%hd\t%hhd\t%hd\t%hd\t"
			//"%hhd\t%hhd\t%hhd\t%hhd\t%d\t%hd\t%hd\t%hd\t%hd\t%hd\t"
			//"%hd\t%hhd\t%d\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t"
			//"%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t"
			//"%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%hhd\t%d"
			FORMAT.c_str()
			, &ptr->ItemIndex, &ptr->ItemSubGroup, &ptr->ItemSubIndex, &ptr->szModelFolder, &ptr->szModelName, &ptr->szItemName
			, &ptr->KindA, &ptr->KindB, &ptr->Type, &ptr->TwoHands, &ptr->DropLevel, &ptr->Slot, &ptr->SkillIndex, &ptr->Width, &ptr->Height
			, &ptr->DamageMin, &ptr->DamageMax, &ptr->DefenseRate, &ptr->Defense, &ptr->MagicResistance, &ptr->AttackSpeed, &ptr->WalkSpeed
			, &ptr->Durability, &ptr->MagicDur, &ptr->MagicPower, &ptr->ReqStr, &ptr->ReqDex, &ptr->ReqEne, &ptr->ReqVit, &ptr->ReqCmd, &ptr->ReqLvl
			, &ptr->ItemValue, &ptr->Money, &ptr->SetAttr, &ptr->Classes[0], &ptr->Classes[1], &ptr->Classes[2], &ptr->Classes[3], &ptr->Classes[4]
			, &ptr->Classes[5], &ptr->Classes[6], &ptr->Classes[7], &ptr->Resistances[0], &ptr->Resistances[1], &ptr->Resistances[2], &ptr->Resistances[3]
			, &ptr->Resistances[4], &ptr->Resistances[5], &ptr->Resistances[6], &ptr->Dump, &ptr->Transaction, &ptr->PersonalStore, &ptr->Warehouse, &ptr->SellNpc
			, &ptr->Expensive, &ptr->Repair, &ptr->Overlap, &ptr->Unk_End
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
