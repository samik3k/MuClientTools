
#ifndef MAP_CHARACTERS_BMD_H
#define MAP_CHARACTERS_BMD_H

typedef TxtConvertor<MAP_CHARACTERS> MapCharactersBmdConvert;
class MapCharactersBmd : public MapCharactersBmdConvert
{
public:
	MapCharactersBmd() : MapCharactersBmdConvert() {};
	virtual ~MapCharactersBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{
	//	return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};

private:
	int GetKey(MAP_CHARACTERS* ptr) { return ptr->Map; };
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtOut(ofstream & os);
	void TxtIn(ifstream& is);
};

#endif