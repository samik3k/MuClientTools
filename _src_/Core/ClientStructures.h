#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

struct MUUN_INFO
{
	BYTE Unk[64];
};

//struct MUUN_OPTION
STRUCT(MUUN_OPTION) LAZY
(
	int ID;
	short MuunID;
	char OptionName[256];
	//BYTE GAP_1[2];
	int ValueEvo;
	int ValueLvl_1;
	int ValueLvl_2;
	int ValueLvl_3;
	int ValueLvl_4;
	int ValueLvl_5;
	BYTE ConditionType_1;
	char OptionDesc[256];
	//BYTE GAP_2[3];
	int ConditionValue_1;
	int ConditionValue_2;
	BYTE ConditionType_2;
	//BYTE GAP_3[3];
);


//struct PENTAGRAM_MIX_SOURCE
STRUCT(PENTAGRAM_MIX_SOURCE) LAZY
(
	int Category;
	int Index;
	int SuccessRate_Cat0;
	int ItemID[5];
	int ItemCat[5];
	int ItemIndex[5];
	int ItemCount[5];
	int MoneyNeed;
	int ItemLevelNeed;
	int ErrtelRankNeed;
	int ErrtelCount;
	int SuccessRate_Cat1[5];
	int Unk_Block[4];
);

//struct INFO_TOOLTIP_TEXT
STRUCT(INFO_TOOLTIP_TEXT) LAZY
(
	short ID;
	char Text[256];
);

//struct INFO_TOOLTIP
STRUCT(INFO_TOOLTIP) LAZY
(
	short ID;
	//struct { short Type; short Value; } Info[10];
	short Type_1; short Value_1;
	short Type_2; short Value_2;
	short Type_3; short Value_3;
	short Type_4; short Value_4;
	short Type_5; short Value_5;
	short Type_6; short Value_6;
	short Type_7; short Value_7;
	short Type_8; short Value_8;
	short Type_9; short Value_9;
	short Type_10; short Value_10;
);

//struct FORMULA_DATA
STRUCT(FORMULA_DATA) LAZY
(
	int ID;
	char Text[64];
);

//struct EXCELLENT_OPTION
STRUCT(EXCELLENT_OPTION) LAZY
(
	BYTE Category;
	BYTE Number;
	char Name[100];
	BYTE Operator;
	//BYTE GAP_103;
	int Value;
	int Dmg;
	BYTE Zen;
	BYTE DmgChance;
	BYTE Offense;
	BYTE Defense;
	BYTE Life;
	BYTE Mana;
	BYTE Other;
);

//struct ITEM_ATTRIBUTE
STRUCT(ITEM_ATTRIBUTE) LAZY
(
	DWORD ItemIndex;
	WORD ItemSubGroup;
	WORD ItemSubIndex;
	char szModelFolder[260];
	char szModelName[260];
	char szItemName[30];
	BYTE KindA;
	BYTE KindB;
	BYTE Type;
	BYTE TwoHands;
	WORD DropLevel;
	BYTE Slot;
	//BYTE GAP_564;
	WORD SkillIndex;
	BYTE Width;
	BYTE Height;
	WORD DamageMin;
	WORD DamageMax;
	BYTE DefenseRate;
	//BYTE GAP_575;
	WORD Defense;
	WORD MagicResistance;
	BYTE AttackSpeed;
	BYTE WalkSpeed;
	BYTE Durability;
	BYTE MagicDur;
	DWORD MagicPower;
	WORD ReqStr;
	WORD ReqDex;
	WORD ReqEne;
	WORD ReqVit;
	WORD ReqCmd;
	WORD ReqLvl;
	BYTE ItemValue;
	//BYTE GAP3_601;
	DWORD Money;
	BYTE SetAttr;
	BYTE Classes[8];
	BYTE Resistances[7];
	BYTE Dump;
	BYTE Transaction;
	BYTE PersonalStore;
	BYTE Warehouse;
	BYTE SellNpc;
	BYTE Expensive;
	BYTE Repair;
	BYTE Overlap;
	DWORD Unk_End;
);


#endif