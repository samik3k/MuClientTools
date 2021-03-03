#include "LangMpr.h"
using namespace  bit7z;

//------------------------------------------------------------------------
//--LangMpr
//------------------------------------------------------------------------

BOOL LangMpr::Unpack(const char * szSrcFile, const char *szDestDir)
{
	return FileOpen(szSrcFile) 
		&& Decrypt() 
		&& UnZip(szDestDir ? szDestDir : fs::path(szSrcFile).replace_extension("").string().append("_out").c_str());
}

BOOL LangMpr::Pack(const char * szSrcDir, const char *szDestFile)
{
	return Zip(szSrcDir) 
		&& Encrypt() 
		&& FileWrite(szDestFile ? szDestFile : fs::path(szSrcDir).replace_extension(".out.mpr").string().c_str());
}

BOOL LangMpr::FileOpen(const char * szSrcFile)
{
	assert(szSrcFile);

	ifstream is(szSrcFile, ios::in | ios::binary);
	if (!is.is_open())
	{
		cout << "Failed to open file: " << szSrcFile << '\n';
		return false;
	}
	is.seekg(0, is.end);
	size_t size = is.tellg();
	is.seekg(0, is.beg);

	if (size < 4)
	{
		cout << "Incorrect filesize: " << size << '\n';
		return false;
	}
	size -= 4;		//CRC is the last 4 BYTEs
	_buf.resize(size);

	is.read((char *)_buf.data(), size);
	DWORD CRC = 0;
	is.read((char *)&CRC, 4);
	is.close();
	if (CRC != CalculateCRC(_buf.data(), _buf.size(), _wkey))
	{
		cout << "Warning: InputFile CRC check failed. \n";
#ifdef STRICT_CRC_CHECK
		return false;
#endif
	}

	return true;
	return 0;
}

BOOL LangMpr::FileWrite(const char * szDestFile)
{
	assert(_buf.size() && szDestFile);

	fs::path pFile = BackupPath(szDestFile);
	CreateParentDir(pFile);

	DWORD CRC = CalculateCRC(_buf.data(), _buf.size(), _wkey);
	ofstream os(pFile, ios::out | ios::binary);
	if (!os.is_open())
	{
		cout << "Error: Failed to write file: " << pFile << '\n';
		return false;
	}
	os.write((char*)_buf.data(), _buf.size());
	os.write((char*)&CRC, sizeof(DWORD));
	os.close();

	return true;
}


BOOL LangMpr::Decrypt()
{
	assert(_buf.size());

	for (size_t i = 0; i < _buf.size(); ++i)
	{
		_buf[i] ^= _xor3key[i % 3];
		_buf[i] ^= _wkey & 0xFF;
	}
	return true;
}

BOOL LangMpr::Encrypt()
{
	return Decrypt();
}

BOOL LangMpr::UnZip(const char *szDestDir)
{
	assert(_buf.size() && szDestDir);
	const wstring wsPassword = _LANG_ZIP_PASSWORD_;
	const fs::path pDir = BackupPath(RemoveSlashEnd(szDestDir));
	CreateParentDir(pDir);
	if (!fs::exists(pDir))
		fs::create_directory(pDir);

	try {
		Bit7zLibrary lib{ L"7z.dll" };
		BitMemExtractor extractor{ lib, BitFormat::Zip };
		extractor.setPassword(wsPassword);
		extractor.extract(_buf, pDir);
	}
	catch (const BitException& ex) {
		cout << "Error: " << ex.what() << '\n';
		cout << "\tCheck _LANG_WKEY_ / _LANG_XOR3KEY_ / _LANG_ZIP_PASSWORD_ \n";

#ifdef WRITE_ZIP_FILE
		ofstream os("error.zip", ios::out | ios::binary);
		os.write((char*)_buf.data(), _buf.size());
		os.close();
		cout << "File 'error.zip' saved. \n";
#endif
		return false;
	}

#ifdef WRITE_ZIP_FILE
	ofstream os("unpack.zip", ios::out | ios::binary);
	os.write((char*)_buf.data(), _buf.size());
	os.close();
	cout << "File 'unpack.zip' saved. \n";
#endif

	return true;
}

BOOL LangMpr::Zip(const char *szSrcDir)
{
	assert(szSrcDir);
	fs::path pDir = RemoveSlashEnd(szSrcDir);
	const wstring wsPassword = _LANG_ZIP_PASSWORD_;

	try {
		Bit7zLibrary lib{ L"7z.dll" };
		BitCompressor compressor{ lib, BitFormat::Zip };
		compressor.setPassword(wsPassword);
		_buf.clear();
		compressor.compressDirectoryToBuffer(pDir, _buf);
	}
	catch (const BitException& ex) {
		cout << "Error: " << ex.what() << '\n';
		return false;
	}

#ifdef WRITE_ZIP_FILE
	ofstream os("pack.zip", ios::out | ios::binary);
	os.write((char*)_buf.data(), _buf.size());
	os.close();
	cout << "File 'pack.zip' saved. \n";
#endif

	return true;
}