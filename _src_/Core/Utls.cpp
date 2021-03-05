#include "Utls.h"
//------------------------------------------------------------------------
//--Utls
//------------------------------------------------------------------------
namespace Utls {
	void CreateParentDir(fs::path pPath)
	{
		fs::path pParent = fs::_Parse_parent_path(pPath.wstring());
		if (!pParent.empty() && !fs::exists(pParent))
		{
			Utls::CreateParentDir(pParent);
			fs::create_directory(pParent);
		}
	}
	
	fs::path RemoveSlashEnd(fs::path&& path)
	{
		if (path.empty())
			return path;

		auto& s = path.string();
		auto& c = s[s.length() - 1];
		if (c == '/' || c == '\\')
			c = '\0';

		return fs::path(s);
	}

	fs::path BackupPath(fs::path&& pFile)
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
			catch (exception ex)
			{
				cout << ex.what() << '\n';
				char msg[256];
				printf(msg, "Use '%s' instead. \n", pBak);
				cout << msg;
				//MessageBox(NULL, msg, "Warning", MB_OK);
				return pBak;
			}
		}
		return pFile;
	}

	bool IsEmptyCStr(const char * str)
	{
		assert(str);
		return str[0] == '\0';
	}

	void RemoveAllStringSpaces(string& s)
	{
		int count = 0;
		for (int i = 0; i < s.length(); i++)
			if (s[i] != ' ' && s[i] != '\t')
				s[count++] = s[i];
		s.resize(count);
	}
}



