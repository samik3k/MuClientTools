#ifndef QUEST_BMD_H
#define QUEST_BMD_H

#define _QUEST_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<QUEST_INFO> QuestBmdConvert;
class QuestBmd : public QuestBmdConvert
{
public:
	QuestBmd() : QuestBmdConvert(_QUEST_BMD_WKEY_) {};
	virtual ~QuestBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{
	//	return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};

private:
	BOOL Decrypt();
	BOOL Encrypt();

	int GetKey(QUEST_INFO* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif