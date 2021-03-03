#ifndef MUUN_INFO_BMD_H
#define MUUN_INFO_BMD_H

#define _MUUN_INFO_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<MUUN_INFO> MuunInfoBmdConvert;
class MuunInfoBmd : public MuunInfoBmdConvert
{
public:
	MuunInfoBmd() : MuunInfoBmdConvert(_MUUN_INFO_BMD_WKEY_) {};
	virtual ~MuunInfoBmd() {};

private:
	int GetKey(MUUN_INFO* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif