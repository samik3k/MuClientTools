#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

struct INFO_TOOLTIP_TEXT
{
	short ID;
	char Text[256];
};

struct INFO_TOOLTIP
{
	short ID;
	struct { short Type; short Value; } Info[10];
};

struct FORMULA_DATA
{
	int ID;
	char Text[64];
};

struct EXCELLENT_OPTION
{
	BYTE Category;
	BYTE Number;
	char Name[100];
	BYTE Operator;
	BYTE GAP_103;
	int Value;
	int Dmg;
	BYTE Zen;
	BYTE DmgChance;
	BYTE Offense;
	BYTE Defense;
	BYTE Life;
	BYTE Mana;
	BYTE Other;
};

struct ITEM_ATTRIBUTE
{
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
	BYTE GAP_564;
	WORD SkillIndex;
	BYTE Width;
	BYTE Height;
	WORD DamageMin;
	WORD DamageMax;
	BYTE DefenseRate;
	BYTE GAP_575;
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
	BYTE GAP3_601;
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
};


#endif