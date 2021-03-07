#ifndef QUEST_BMD_H
#define QUEST_BMD_H

typedef TxtConvertor<QUEST_INFO> QuestBmdConvert;
class QuestBmd : public QuestBmdConvert
{
public:
	QuestBmd() : QuestBmdConvert() {};
	virtual ~QuestBmd() {};
	
private:
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif