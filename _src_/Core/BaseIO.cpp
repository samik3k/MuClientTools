#include "BaseIO.h"

//------------------------------------------------------------------------
//--BaseIO
//------------------------------------------------------------------------

BOOL BaseIO::FileOpen(const char * szSrcFile)
{
	if(!szSrcFile) return FALSE;

	std::ifstream is(szSrcFile, std::ios::in | std::ios::binary);
	if (!is.is_open())
	{
		std::cout << "Error: Failed to open file: " << szSrcFile << '\n';
		return FALSE;
	}
	is.seekg(0, is.end);
	size_t size = is.tellg();
	is.seekg(0, is.beg);

	_buf.resize(size);
	
	is.read((char *)_buf.data(), size);
	is.close();
	return TRUE;
}

BOOL BaseIO::FileWrite(const char * szDestFile)
{
	if(!_buf.size() || !szDestFile) return FALSE;

	fs::path pFile = Utls::BackupPath(szDestFile);
	Utls::CreateParentDir(pFile);

	std::ofstream os(pFile, std::ios::out | std::ios::binary);
	if (!os.is_open())
	{
		std::cout << "Error: Failed to write file: " << pFile << '\n';
		return FALSE;
	}
	os.write((char*)_buf.data(), _buf.size());
	os.close();

	return TRUE;
}
