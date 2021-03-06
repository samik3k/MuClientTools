#ifndef QUEST_BMD_H
#define QUEST_BMD_H

typedef TxtConvertor<QUEST_INFO> QuestBmdConvert;
class QuestBmd : public QuestBmdConvert
{
public:
	QuestBmd() : QuestBmdConvert() {};
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
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif