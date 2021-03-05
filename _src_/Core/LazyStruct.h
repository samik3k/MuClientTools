#ifndef LAZY_STRUCT_H
#define LAZY_STRUCT_H

struct OffsetInfo
{
	size_t Type;
	size_t Offset;
	string Format;
};

enum LAZY_TYPE_FLAG
{
	_UNK_ = 0,
	_1BYTE_ = 1,
	_2BYTE_ = 2,
	_4BYTE_ = 4,
	//_8BYTE_ = 8,	//ONLY x86
	_FLOAT_ = 8,
	_DOUBLE_ = 16,
	_SIGNED_ = 32,
	_CSTR_ = 64,
};

namespace LazyStruct
{

	size_t ParseType(string& type);
	size_t ParseMember(string& member, string& member_type, string& member_name);
	int ParseMemberType(string& member_type, string& format);
	void CalculateOffset(vector<OffsetInfo>& offset);
	string ParseMembersToLabel(string&& members);
	string ParseMembersToFormat(string&& members);
	vector<OffsetInfo> ParseMembersToOffset(string && members);
}

#define STRUCT(_) struct _
#define LAZY(Members)										\
{															\
	Members													\
	static string GetLabel()								\
	{														\
		static const string LABEL							\
			= LazyStruct::ParseMembersToLabel(#Members);	\
		return LABEL;										\
	};														\
	static string GetFormat()								\
	{														\
		static const string FORMAT							\
			= LazyStruct::ParseMembersToFormat(#Members);	\
		return FORMAT;										\
	};														\
	static vector<OffsetInfo> GetOffset()					\
	{														\
		static const vector<OffsetInfo> OFFSET				\
			= LazyStruct::ParseMembersToOffset(#Members);	\
		return OFFSET;										\
	}														\
}

#endif // LAZY_STRUCT_H