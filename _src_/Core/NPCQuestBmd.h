
#ifndef NPC_DIALOGUE_BMD_H
#define NPC_DIALOGUE_BMD_H

typedef TxtConvertor<NPC_DIALOGUE> NPCDialogueBmdConvert;
class NPCDialogueBmd : public NPCDialogueBmdConvert
{
public:
	NPCDialogueBmd() : NPCDialogueBmdConvert() { hasCounter = false; hasCRC = false; };
	virtual ~NPCDialogueBmd() {};
private:
	void MakeLabelEx(ofstream& os) 
	{
		os << "//NPCQuest texts are in the QuestWords file." << endl;
	};
};

#endif

//================================================================

#ifndef QUEST_PROGRESS_BMD_H
#define QUEST_PROGRESS_BMD_H

typedef TxtConvertor<QUEST_PROGRESS> QuestProgressBmdConvert;
class QuestProgressBmd : public QuestProgressBmdConvert
{
public:
	QuestProgressBmd() : QuestProgressBmdConvert() { hasCounter = false; hasCRC = false; };
	virtual ~QuestProgressBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{
	//	return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};
private:
	void MakeLabelEx(ofstream& os)
	{
		os << "//NPCQuest texts are in the QuestWords file." << endl;
	};
};

#endif

//================================================================

#ifndef QUEST_WORDS_BMD_H
#define QUEST_WORDS_BMD_H

typedef TxtConvertor<QUEST_WORDS> QuestWordsBmdConvert;
class QuestWordsBmd : public QuestWordsBmdConvert
{
public:
	QuestWordsBmd() : QuestWordsBmdConvert() {};
	virtual ~QuestWordsBmd() {};

private:
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif