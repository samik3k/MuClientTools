#ifndef SOCKET_ITEM_BMD_H
#define SOCKET_ITEM_BMD_H

typedef TxtConvertor<SOCKET_ITEM_INFO> SocketItemBmdConvert;
class SocketItemBmd : public SocketItemBmdConvert
{
public:
	SocketItemBmd() : SocketItemBmdConvert() {};
	virtual ~SocketItemBmd() {};

	//BOOL Unpack(const char *szSrcBmd, const char *szDestTxt)
	//{
	//	return FileOpen(szSrcBmd)
	//		&& Decrypt()
	//		&& FileWrite(fs::path(szSrcBmd).replace_extension(".debug").string().c_str());
	//};

private:
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtIn(ifstream& is);
};

#endif