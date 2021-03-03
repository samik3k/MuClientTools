//------------------------------------------------------------------------
//--Utls
//------------------------------------------------------------------------
void CreateParentDir(fs::path pPath)
{
	fs::path pParent = fs::_Parse_parent_path(pPath.wstring());
	if (!pParent.empty() && !fs::exists(pParent))
	{
		CreateParentDir(pParent);
		fs::create_directory(pParent);
	}
}

fs::path RemoveSlashEnd(fs::path path)
{
	if (path.empty())
		return path;

	auto l = path.wstring().length();
	wchar_t* szPath = (wchar_t*)path.wstring().c_str();
	if (szPath[l - 1] == L'/' || szPath[l - 1] == L'\\')
		szPath[l - 1] = 0;
	return szPath;
}

fs::path BackupPath(fs::path pFile)
{
	fs::path pBak;
	if (fs::exists(pFile))
	{
		int i = 0;
		wstring temp = pFile.wstring() + L"_bak_";
		while (++i)
		{
			if (!fs::exists(temp + to_wstring(i)))
			{
				pBak = temp + to_wstring(i);
				break;
			}
		}

		try 
		{
			fs::rename(pFile, pBak);
		}
		catch(exception ex)
		{
			cout << ex.what() << '\n';
			char msg[256];
			printf(msg, "Write to '%s' instead. \n", pBak);
			cout << msg;
			//MessageBox(NULL, msg, "Warning", MB_OK);
			return pBak;
		}
	}
	return pFile;
}