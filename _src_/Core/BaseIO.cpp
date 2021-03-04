#include "BaseIO.h"

//------------------------------------------------------------------------
//--BaseIO
//------------------------------------------------------------------------

BOOL BaseIO::FileOpen(const char * szSrcFile)
{
	assert(szSrcFile);

	ifstream is(szSrcFile, ios::in | ios::binary);
	if (!is.is_open())
	{
		cout << "Error: Failed to open file: " << szSrcFile << '\n';
		return false;
	}
	is.seekg(0, is.end);
	size_t size = is.tellg();
	is.seekg(0, is.beg);

	_buf.resize(size);
	
	is.read((char *)_buf.data(), size);
	is.close();
	return true;
}

BOOL BaseIO::FileWrite(const char * szDestFile)
{
	assert(_buf.size() && szDestFile);

	fs::path pFile = Utls::BackupPath(szDestFile);
	Utls::CreateParentDir(pFile);

	ofstream os(pFile, ios::out | ios::binary);
	if (!os.is_open())
	{
		cout << "Error: Failed to write file: " << pFile << '\n';
		return false;
	}
	os.write((char*)_buf.data(), _buf.size());
	os.close();

	return true;
}
