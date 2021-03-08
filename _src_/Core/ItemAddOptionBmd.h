
#ifndef ITEM_ADD_OPTION_BMD_H
#define ITEM_ADD_OPTION_BMD_H

typedef TxtConvertor<ITEM_ADD_OPTION> ItemAddOptionBmdConvert;
class ItemAddOptionBmd : public ItemAddOptionBmdConvert
{
public:
	ItemAddOptionBmd() : ItemAddOptionBmdConvert() { hasCounter = false; hasCRC = false; };
	virtual ~ItemAddOptionBmd() {};

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