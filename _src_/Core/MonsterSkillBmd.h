
#ifndef MONSTER_SKILL_BMD_H
#define MONSTER_SKILL_BMD_H

typedef TxtConvertor<MONSTER_SKILL> MonsterSkillBmdConvert;
class MonsterSkillBmd : public MonsterSkillBmdConvert
{
public:
	MonsterSkillBmd() : MonsterSkillBmdConvert() { hasCRC = false; };
	virtual ~MonsterSkillBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{		return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};
};

#endif