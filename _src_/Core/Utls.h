#ifndef UTLS_H
#define UTLS_H

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

namespace Utls
{
	void CreateParentDir(fs::path path);
	fs::path RemoveSlashEnd(fs::path&& path);
	fs::path BackupPath(fs::path&& path);
	bool IsEmptyCStr(const char* str);
	void RemoveAllStringSpaces(string& s);

}

namespace LazyStruct
{
	int ParseMember(string& member, string& member_type, string& member_name);
	string ParseMemberType(string& member_type);
	string ParseMembersToLabel(string&& members);
	string ParseMembersToFormat(string&& members);
}

#define STRUCT(_) struct _
#define LAZY(Members)															\
{																				\
	Members																		\
	static string GetLabel()													\
	{																			\
		static const string LABEL = LazyStruct::ParseMembersToLabel(#Members);	\
		return LABEL;															\
	};																			\
	static string GetFormat()													\
	{																			\
		static const string FORMAT = LazyStruct::ParseMembersToFormat(#Members);\
		return FORMAT;															\
	};																			\
}

#endif // !UTLS_H
