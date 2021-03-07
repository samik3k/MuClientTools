#ifndef SERVER_LIST_BMD_H
#define SERVER_LIST_BMD_H

typedef TxtConvertor<SERVER_LIST> ServerListBmdConvert;
class ServerListBmd : public ServerListBmdConvert
{
public:
	ServerListBmd() : ServerListBmdConvert() {};
	virtual ~ServerListBmd() {};

private:
	vector<string> _msg;
	BOOL Decrypt();
	BOOL Encrypt();
	void TxtOut(ofstream& os);
	void TxtIn(ifstream& is);
};

#endif