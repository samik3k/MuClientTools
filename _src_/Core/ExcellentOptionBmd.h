#ifndef EXC_OPT_BMD_H
#define EXC_OPT_BMD_H

#define _EXC_OPT_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<EXCELLENT_OPTION> ExcOptConvert;
class ExcellentOptionBmd : public ExcOptConvert
{
public:
	ExcellentOptionBmd() : ExcOptConvert(_EXC_OPT_BMD_WKEY_) {};
	virtual ~ExcellentOptionBmd() {};

private:
	int GetKey(EXCELLENT_OPTION* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif