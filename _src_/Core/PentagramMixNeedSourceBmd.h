
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
	void MakeLabelEx(ofstream& os) 
	{
		assert(os);
		os << "// Cat0: Material Combination" << endl;
		os << "// Cat1: Errtel" << endl;
		os << "// Cat2 : Errtel Level Upgrade" << endl;
		os << "// Cat3 : Errtel Rank Upgrade" << endl;
		os << "// Cat6: Wing Add Option" << endl;
		os << "// Cat7: Wing Option Level Upgrade" << endl;
	};
	int GetKey(PENTAGRAM_MIX_SOURCE* ptr) { return (ptr->Category << 8) | ptr->Index; };
};

#endif