#ifndef MUUN_OPTION_BMD_H
#define MUUN_OPTION_BMD_H

#define _MUUN_OPTION_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<MUUN_OPTION> MuunOptionBmdConvert;
class MuunOptionBmd : public MuunOptionBmdConvert
{
public:
	MuunOptionBmd() : MuunOptionBmdConvert(_MUUN_OPTION_BMD_WKEY_) {};
	virtual ~MuunOptionBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt);

private:
	int GetKey(MUUN_OPTION* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif