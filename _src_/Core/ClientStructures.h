#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H


struct SERVER_LIST_EX
{
	char DontCare[39];
	char Msg[1];
};

#pragma pack(1)
struct SERVER_LIST
{
	short ID;
	char Name[32];
	BYTE PosType;
	BYTE Index;
	BYTE Type;
	WORD MsgLen;

	static string GetLabel() { return string(); };
	static string GetFormat() { return string(); };
	static vector<OffsetInfo> GetOffset() { return vector<OffsetInfo>(); };
};
#pragma pack()

//struct MURUMMY_SLOT
STRUCT(MURUMMY_SLOT) LAZY
(
	BYTE ID;
	BYTE SlotType;
	BYTE CardType;
	BYTE Unk[8];
);

//struct MURUMMY_CARD
STRUCT(MURUMMY_CARD) LAZY
(
	WORD Unk[30];
);

//struct MURUMMY_OPTION
STRUCT(MURUMMY_OPTION) LAZY
(
	short Type;
	short Index;
	int Option;
);

//struct PLAY_GUIDE_INFO
STRUCT(PLAY_GUIDE_INFO) LAZY
(
	int ID;
	char Text[256];
);

//struct SOCKET_ITEM_INFO
STRUCT(SOCKET_ITEM_INFO) LAZY
(
	//BYTE Unk[168];
	int ID;
	int ElementType;
	int Level;
	char Name[64];
	int BonusType;
	int BonusValue1;
	int BonusValue2;
	int BonusValue3;
	int BonusValue4;
	int BonusValue5;
	int BonusValue6;
	int BonusValue7;
	int BonusValue8;
	int BonusValue9;
	int BonusValue10;
	int BonusValue11;
	int BonusValue12;
	int BonusValue13;
	int BonusValue14;
	int BonusValue15;
	int BonusValue16;
	int BonusValue17;
	int BonusValue18;
	int BonusValue19;
	int BonusValue20;
	BYTE FireNeed;
	BYTE WaterNeed;
	BYTE IceNeed;
	BYTE WindNeed;
	BYTE LighteningNeed;
	BYTE EarthNeed;
);

struct QUEST_INFO_ITEM
{
	BYTE Flag;
	BYTE QuestType;
	WORD ItemCat;
	BYTE ItemIndex;
	BYTE Level;
	BYTE Amount;
	BYTE GL;
	BYTE DW;
	BYTE DK;
	BYTE FE;
	BYTE MG;
	BYTE DL;
	BYTE SU;
	BYTE RF;
	WORD Msg_1;
	WORD Msg_2;
	WORD Msg_3;
	WORD Msg_4;
};

struct QUEST_INFO_TYPE
{
	BYTE Flag;
	char Type;
	short QuestIndex;
	WORD MinLvl;
	WORD MaxLvl;
	DWORD NeedStr;
	DWORD NeedZen;
	WORD Msg;
	WORD GAP;
};

struct QUEST_INFO
{
	//BYTE Unk[744];
	WORD ItemCount;
	WORD TypeCount;
	WORD NPC;
	char QuestName[32];
	QUEST_INFO_ITEM Items[16];
	QUEST_INFO_TYPE Types[16];

	static string GetLabel() { return string(); };
	static string GetFormat() { return string(); };
	static vector<OffsetInfo> GetOffset() { return vector<OffsetInfo>(); };
};

//struct STAT_OPTION_TEXT
STRUCT(STAT_OPTION_TEXT) LAZY
(
	int ID;
	char Text[256];
);

//struct STAT_OPTION
STRUCT(STAT_OPTION) LAZY
(
	int Class;
	int StatType;
	int TextID;
);

//struct MUUN_EXCHANGE
STRUCT(MUUN_EXCHANGE) LAZY
(
	int Column_1;
	int Column_2;
	int Column_3;
	int Column_4;
);

//struct MUUN_TOOLTIP_INFO
STRUCT(MUUN_TOOLTIP_INFO) LAZY
(
	int MuunID;
	float Translate_X;
	float Translate_Y;
	float Translate_Z;
	float Rotate_X;
	float Rotate_Y;
	float Rotate_Z;
	float Scale;
);

//struct MUUN_INFO
STRUCT(MUUN_INFO) LAZY
(
	int ID;
	int MuunID;
	BYTE Type;
	BYTE Rank;
	//BYTE GAP_10[2];
	int OptionIndex;
	int AddOptionType;
	int AddOptionValue;
	int AddOptCheckType;
	int OptionStartDate_Year;
	int OptionStartDate_Month;
	int OptionStartDate_Day;
	int OptionEndDate_Year;
	int OptionEndDate_Month;
	int OptionEndDate_Day;
	int EvoID;
	int SkillDelayTime;
);

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