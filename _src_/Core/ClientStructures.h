#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

struct MIX_RULE
{
	int Rule;
	float Div;
};

struct MIX_ITEM
{
	short StartID;
	short EndID;
	int MinLvl;
	int MaxLvl;
	int MinOpt;
	int MaxOpt;
	int MinDur;
	int MaxDur;
	int MinCount;
	int MaxCount;
	int Type;
};

struct MIX_INFO
{
	int ID;
	int Type;
	int Desc_Msg_1;
	int Desc_Msg_2;
	int Desc_Msg_3;
	int Bad_Msg_1;
	int Bad_Msg_2;
	int Bad_Msg_3;
	int Good_Msg_1;
	int Good_Msg_2;
	int Good_Msg_3;
	int Height;
	int Width;
	int MinLevel;
	BYTE MoneyRule;
	int MoneyReq;
	int RulesCount;
	MIX_RULE Rules[32];
	int MaxSuccesRate;
	BYTE Unk_1;
	BYTE Unk_2;
	BYTE Unk_3;
	BYTE Unk_4;
	BYTE Unk_5;
	BYTE Unk_6;
	MIX_ITEM Items[8];
	int ItemsCount;

	static std::string GetLabel() { return std::string(); };
	static std::string GetFormat() { return std::string(); };
	static std::vector<OffsetInfo> GetOffset() { return std::vector<OffsetInfo>(); };
};

//struct JEWEL_OF_HARMONY_OPTION
STRUCT(JEWEL_OF_HARMONY_OPTION) LAZY
(
	int ID;
	char Name[64];
	int Value[14];
	int ZenReq[14];
);

//struct ITEM_ADD_OPTION
STRUCT(ITEM_ADD_OPTION) LAZY
(
	WORD Option_1;
	WORD Value_1;
	WORD Option_2;
	WORD Value_2;
	DWORD Idx;
	int Time;
);

//struct SKILL_TOOLTIP_TEXT
STRUCT(SKILL_TOOLTIP_TEXT) LAZY
(
	WORD ID;
	char Name[256];
	//WORD Gap;
	int C3;
	int C4;
	char Desc_1[256];
	int C6;
	int C7;
	char Desc_2[256];
	int C9;
);

//struct QUEST_PROGRESS
#pragma pack(1)
STRUCT(QUEST_PROGRESS) LAZY1	//size = 41
(
	WORD QuestSwitch;
	WORD Ep;
	BYTE Unk;
	DWORD Introduction;
	DWORD Conversation;
	DWORD Button_1;
	DWORD Button_2;
	DWORD Button_3;
	DWORD Button_4;
	DWORD Button_5;
	DWORD QuestName;
	DWORD QuestDesc;
);
#pragma pack()

//struct QUEST_WORDS
#pragma pack(1)
STRUCT(QUEST_WORDS) LAZY1	//size = 6
(
	DWORD ID;
	WORD Len;
);
#pragma pack()

struct QUEST_WORDS_EX
{
	BYTE DontCare[sizeof(QUEST_WORDS)];
	char Text[1];
};


//struct NPC_DIALOGUE
STRUCT(NPC_DIALOGUE) LAZY
(
	//BYTE Unk[88];
	WORD ID;
	WORD NPC;
	DWORD Label;
	DWORD Button_1;
	DWORD BtnValue_1;
	DWORD Button_2;
	DWORD BtnValue_2;
	DWORD Button_3;
	DWORD BtnValue_3;
	DWORD Button_4;
	DWORD BtnValue_4;
	DWORD Button_5;
	DWORD BtnValue_5;
	DWORD Button_6;
	DWORD BtnValue_6;
	DWORD Button_7;
	DWORD BtnValue_7;
	DWORD Button_8;
	DWORD BtnValue_8;
	DWORD Button_9;
	DWORD BtnValue_9;
	DWORD Button_10;
	DWORD BtnValue_10;

);

//struct MASTER_SKILL_TOOLTIP
STRUCT(MASTER_SKILL_TOOLTIP) LAZY
(
	DWORD SkillNum;
	WORD Class;
	char Text_Lvl[64];
	char Text_Desc[256];
	char Text_Req_1[96];
	char Text_Req_2[128];
	char Text_Req_3[256];
	//BYTE GAP[2];
);

//struct MASTER_SKILL_TREE_DATA
STRUCT(MASTER_SKILL_TREE_DATA) LAZY
(
	WORD ID;
	WORD Class;
	BYTE TreeType;
	BYTE ReqPoint;
	BYTE MaxPoint;
	BYTE Unk1;
	DWORD Parent_Skill_1;
	DWORD Parent_Skill_2;
	DWORD SkillNum;
	DWORD Unk2;
);

//struct MONSTER_SKILL
STRUCT(MONSTER_SKILL) LAZY
(
	int ID;
	int Skill_1;
	int Skill_2;
	int Skill_3;
	int Skill_4;
	int Skill_5;
	int Skill_6;
	int Skill_7;
	int Skill_8;
	int Skill_9;
	int Skill_10;
	int Unk;
);

//struct ITEM_SET_OPTION_TEXT
STRUCT(ITEM_SET_OPTION_TEXT) LAZY
(
	BYTE ID;
	char Text[100];
	BYTE Unk;
);

//struct ITEM_SET_OPTION
STRUCT(ITEM_SET_OPTION) LAZY
(
	char Name1[64];
	char Name2[64];
	int Opt_1stIndex_1;
	int Opt_2ndIndex_1;
	int Opt_1stIndex_2;
	int Opt_2ndIndex_2;
	int Opt_1stIndex_3;
	int Opt_2ndIndex_3;
	int Opt_1stIndex_4;
	int Opt_2ndIndex_4;
	int Opt_1stIndex_5;
	int Opt_2ndIndex_5;
	int Opt_1stIndex_6;
	int Opt_2ndIndex_6;
	int Opt_1stValue_1;
	int Opt_2ndValue_1;
	int Opt_1stValue_2;
	int Opt_2ndValue_2;
	int Opt_1stValue_3;
	int Opt_2ndValue_3;
	int Opt_1stValue_4;
	int Opt_2ndValue_4;
	int Opt_1stValue_5;
	int Opt_2ndValue_5;
	int Opt_1stValue_6;
	int Opt_2ndValue_6;
	int Opt_1stExIndex;
	int Opt_2ndExIndex;
	int Opt_1stExValue;
	int Opt_2ndExValue;

	int Full_ExIndex;
	int Full_Index_1;
	int Full_Index_2;
	int Full_Index_3;
	int Full_Index_4;
	int Full_Index_5;
	int Full_ExValue;
	int Full_Value_1;
	int Full_Value_2;
	int Full_Value_3;
	int Full_Value_4;
	int Full_Value_5;

	int Unk;

	int DW;
	int DK;
	int FE;
	int MG;
	int DL;
	int SU;
	int RF;
	int GL;
);

//struct ITEM_SET_TYPE
STRUCT(ITEM_SET_TYPE) LAZY
(
	BYTE Tier1;
	BYTE Tier2;
	BYTE Tier3;
	BYTE Tier4;
	BYTE Unk1;
	BYTE Unk2;
);

//struct MAP_CHARACTERS
STRUCT(MAP_CHARACTERS) LAZY
(
	int Map;
	int Count;
);

struct MAP_CHARACTERS_EX
{
	BYTE DontCare[sizeof(MAP_CHARACTERS)];
	int MonsterID[1];
};


//struct EVO_MONSTER_BOX
STRUCT(EVO_MONSTER_BOX) LAZY
(
	BYTE RewardEvoBoxChanceTable;
);

//struct SERVER_LIST	
#pragma pack(1)
STRUCT(SERVER_LIST) LAZY1	//size = 39
(
	short ID;
	char Name[32];
	BYTE PosType;
	BYTE Index;
	BYTE Type;
	WORD MsgLen;
);
#pragma pack()

struct SERVER_LIST_EX
{
	char DontCare[sizeof(SERVER_LIST)];
	char Msg[1];
};

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
	WORD ItemCount;
	WORD TypeCount;
	WORD NPC;
	char QuestName[32];
	QUEST_INFO_ITEM Items[16];
	QUEST_INFO_TYPE Types[16];

	static std::string GetLabel() { return std::string(); };
	static std::string GetFormat() { return std::string(); };
	static std::vector<OffsetInfo> GetOffset() { return std::vector<OffsetInfo>(); };
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