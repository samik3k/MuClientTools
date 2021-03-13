#include "Core.h"
#include "OZJ.h"

BOOL OZJ::Unpack(const char * szSrcOjz, const char * szDestJpg)
{
	return FileOpen(szSrcOjz)
		&& Decrypt()
		&& FileWrite(szDestJpg ? szDestJpg : fs::path(szSrcOjz).replace_extension(".jpg").string().c_str());
}

BOOL OZJ::Pack(const char * szSrcJpg, const char * szDestOjz)
{
	return FileOpen(szSrcJpg)
		&& Encrypt()
		&& FileWrite(szDestOjz ? szDestOjz : fs::path(szDestOjz).replace_extension(".ojz").string().c_str());
}

BOOL OZJ::Decrypt()
{
	if (_buf.size() < 24) return FALSE;

	_buf.erase(_buf.begin(), _buf.begin() + 24);

	return TRUE;
}

BOOL OZJ::Encrypt()
{
	if (_buf.size() < 24) return FALSE;
	
	BYTE dummy[24];
	memcpy(dummy, &_buf[0], 24);

	_buf.insert(_buf.begin(), std::begin(dummy), std::end(dummy));

	return TRUE;
}
