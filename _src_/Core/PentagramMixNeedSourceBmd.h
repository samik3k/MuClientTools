#ifndef PENTAGRAM_MIX_SOURCE_NEED_BMD_H
#define PENTAGRAM_MIX_SOURCE_NEED_BMD_H

#define _PENTAGRAM_MIX_SOURCE_NEED_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<PENTAGRAM_MIX_SOURCE> PentagramMixSourceNeedBmdConvert;
class PentagramMixNeedSourceBmd : public PentagramMixSourceNeedBmdConvert
{
public:
	PentagramMixNeedSourceBmd() : PentagramMixSourceNeedBmdConvert(_PENTAGRAM_MIX_SOURCE_NEED_BMD_WKEY_) {};
	virtual ~PentagramMixNeedSourceBmd() {};

private:
	void MakeLabel(ofstream& os);
	int GetKey(PENTAGRAM_MIX_SOURCE* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif