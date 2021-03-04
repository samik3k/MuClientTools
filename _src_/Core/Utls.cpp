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

	int ParseMember(string & member, string & member_type, string & member_name)
	{
		assert(member.find('*') & member.find('&') == string::npos );	//no using of ptr/ref

		int count = 0;
		size_t _ = 0;

		//compiler will automatically change multiple spaces or tab '\t' to a single space 
		if (member[_] == ' ') _++;

		size_t pos = min(member.find(' ', _), member.find('\t', _));
		if (pos == string::npos)
			return 0;

		member_type = member.substr(_, pos - _);

		if (member[pos] == ' ') pos++;

		size_t a = member.find('[', pos);
		size_t s = member_type.find("char");
		bool is_arr = a != string::npos;
		bool is_str = is_arr ? s != string::npos : false;
		if (is_str)
			member_type.replace(s, 4, "char*");	

		if (is_str || !is_arr)
		{
			member_name = is_str ? member.substr(pos, a - pos) : member.substr(pos);
			count = 1;
		}
		else if(is_arr)
		{
			member_name = member.substr(pos, a - pos);
			a++;
			count = atoi(member.data() + a);
		}

		if (member_name.empty())
			return 0;

		if (*(member_name.end() - 1) == ' ')
			member_name.pop_back();	

		return count;
	}

	string ParseMemberType(string & member_type)
	{
		static const unordered_map<string, string> TYPE =
		{	{"int" ,"%d"},{"DWORD" ,"%d"},			//Find DWORD before WORD
			{"short" ,"%hd"},{"WORD" ,"%hd"},
			{ "char" ,"%hhd"},{"BYTE" ,"%hhd"}	};

		if (member_type.find("char*") != string::npos)
			return "%[^\t]%*c";
		else
			for (auto it = TYPE.begin(); it != TYPE.end(); it++)
				if (member_type.find(it->first) != string::npos)
					return it->second;

		return string();
	}

	string ParseMembersToLabel(string && members)
	{
		string label = "/";
		size_t pos = 1;
		size_t a = 0;
		size_t b = members.find(';', a);

		while (b != string::npos)
		{
			if (b > a)
			{
				string member, member_type, member_name;
				member = members.substr(a, b - a);

				int count = ParseMember(member, member_type, member_name);
				//count < 1 skip it
				if (count == 1)
					label += '\t' + member_name;
				else if (count > 1)
					for (int i = 0; i < count; i++)
						label += '\t' + member_name + "[" + to_string(i) + "]";
			}
			a = b + 1;
			b = members.find(';', a);
		}
		if(label.length() > 2)
			label[1] = '/';	//put comment slashs at front

		return label;
	}

	string ParseMembersToFormat(string && members)
	{
		string format = "";
		size_t pos = 0;
		size_t a = 0;
		size_t b = members.find(';', a);

		while (b != string::npos)
		{
			if (b > a)
			{
				string member, member_type, member_name;
				member = members.substr(a, b - a);

				int count = ParseMember(member, member_type, member_name);
				if (count == 1)
					format += "\t" + ParseMemberType(member_type);
				else if (count > 1)
					for (int i = 0; i < count; i++)
						format += "\t" + ParseMemberType(member_type);
			}
			a = b + 1;
			b = members.find(';', a);
		}

		if (format.length() > 1)
			format = format.substr(1);	//remove "\t" at the front

		return format;
	}
}



