#ifndef ITEM_BMD_H
#define ITEM_BMD_H

#define _ITEM_BMD_WKEY_ _COMMON_TXTCONVERTOR_WKEY_

typedef TxtConvertor<ITEM_ATTRIBUTE> ItemBmdConvert;
class ItemBmd : public ItemBmdConvert
{
public:
	ItemBmd() : ItemBmdConvert(_ITEM_BMD_WKEY_) {};
	virtual ~ItemBmd() {};

private:
	int GetKey(ITEM_ATTRIBUTE* ptr);
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif