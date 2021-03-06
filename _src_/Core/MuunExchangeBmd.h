#ifndef MUUN_EXCHANGE_BMD_H
#define MUUN_EXCHANGE_BMD_H

#define _MUUN_EXCHANGE_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<MUUN_EXCHANGE> MuunExchangeConvert;
class MuunExchangeBmd : public MuunExchangeConvert
{
public:
	MuunExchangeBmd() : MuunExchangeConvert(_MUUN_EXCHANGE_BMD_WKEY_) {};
	virtual ~MuunExchangeBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt);

private:
	BOOL Decrypt();
	BOOL Encrypt();

	int GetKey(MUUN_EXCHANGE* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif