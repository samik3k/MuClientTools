
#ifndef MASTER_SKILL_TREE_DATA_BMD_H
#define MASTER_SKILL_TREE_DATA_BMD_H

#define _MASTER_SKILL_TREE_DATA_BMD_WKEY_ 0x2BC1

typedef TxtConvertor<MASTER_SKILL_TREE_DATA> MasterSkillTreeDataBmdConvert;
class MasterSkillTreeDataBmd : public MasterSkillTreeDataBmdConvert
{
public:
	MasterSkillTreeDataBmd() : MasterSkillTreeDataBmdConvert(_MASTER_SKILL_TREE_DATA_BMD_WKEY_) { hasCounter = false; };
	virtual ~MasterSkillTreeDataBmd() {};
};

#endif

//==========================================================================================

#ifndef MASTER_SKILL_TOOLTIP_BMD_H
#define MASTER_SKILL_TOOLTIP_BMD_H

#define _MASTER_SKILL_TOOLTIP_BMD_WKEY_ 0x2BC1

typedef TxtConvertor<MASTER_SKILL_TOOLTIP> MasterSkillTooltipBmdConvert;
class MasterSkillTooltipBmd : public MasterSkillTooltipBmdConvert
{
public:
	MasterSkillTooltipBmd() : MasterSkillTooltipBmdConvert(_MASTER_SKILL_TOOLTIP_BMD_WKEY_) { hasCounter = false; };
	virtual ~MasterSkillTooltipBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{		
	//	return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};
};

#endif