
#ifndef ITEM_ADD_OPTION_BMD_H
#define ITEM_ADD_OPTION_BMD_H

typedef TxtConvertor<ITEM_ADD_OPTION> ItemAddOptionBmdConvert;
class ItemAddOptionBmd : public ItemAddOptionBmdConvert
{
public:
	ItemAddOptionBmd() : ItemAddOptionBmdConvert() { hasCounter = false; hasCRC = false; };
	virtual ~ItemAddOptionBmd() {};

private:
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif