#ifndef OZJ_H
#define OZJ_H

class OZJ : public BaseIO
{
public:
	OZJ() {};
	virtual ~OZJ() {};

	BOOL Unpack(const char *szSrcOjz, const char *szDestJpg);
	BOOL Pack(const char *szSrcJpg, const char *szDestOjz);
private:
	BOOL Decrypt();
	BOOL Encrypt();
};

#endif // !OZJ_H
