#include "LazyStruct.h"

//------------------------------------------------------------------------
//--LazyStruct
//------------------------------------------------------------------------

namespace LazyStruct
{
	size_t ParseType(string& type)
	{
		static const unordered_map<string, int> TYPES =
		{
			{"cstr",	LAZY_TYPE_FLAG::_CSTR_},
			{"double",	LAZY_TYPE_FLAG::_DOUBLE_},
			{"float",	LAZY_TYPE_FLAG::_FLOAT_},
			//{"DWORD",	LAZY_TYPE_FLAG::_4BYTE_},
			{"WORD",	LAZY_TYPE_FLAG::_2BYTE_},
			{"BYTE",	LAZY_TYPE_FLAG::_1BYTE_},
			{"int",		LAZY_TYPE_FLAG::_4BYTE_ | LAZY_TYPE_FLAG::_SIGNED_},
			{"short",	LAZY_TYPE_FLAG::_2BYTE_ | LAZY_TYPE_FLAG::_SIGNED_},
			{"char",	LAZY_TYPE_FLAG::_1BYTE_ | LAZY_TYPE_FLAG::_SIGNED_}
		};

		if (type.find("DWORD") != string::npos)
		{
			return LAZY_TYPE_FLAG::_4BYTE_;
		}

		for (auto it = TYPES.begin(); it != TYPES.end(); it++)
		{
			if (type.find(it->first) != string::npos)
			{
				return it->second;
			}
		}

		return LAZY_TYPE_FLAG::_UNK_;
	}

	size_t ParseMember(string & member, string & member_type, string & member_name)
	{
		assert(member.find('*') & member.find('&') == string::npos);	//no using of ptr/ref

		int count = 0;
		size_t _ = 0;

		//compiler will automatically change multiple spaces or tab '\t' to a single space 
		if (member[_] == ' ') _++;	// " int..."

		size_t pos = min(member.find(' ', _), member.find('\t', _));
		if (pos == string::npos)
			return 0;

		member_type = member.substr(_, pos - _);

		if (member[pos] == ' ') pos++;	// "int a..."

		size_t a = member.find('[', pos);
		size_t s = member_type.find("char");
		bool is_arr = a != string::npos;
		bool is_cstr = is_arr ? s != string::npos : false;
		if (is_cstr)
			member_type.replace(s, 4, "cstr");	//define cstr := char[]

		if (!is_arr)
		{
			member_name = member.substr(pos);
			count = 1;
		}
		else if (is_arr)	//included cstr
		{
			member_name = member.substr(pos, a - pos);
			a++;
			if (member[pos] == ' ') pos++;	//	"[ 1]"
			count = atoi(member.data() + a);
		}

		if (member_name.empty())
			return 0;

		if (*(member_name.end() - 1) == ' ')	// "a [1]"->"a "
			member_name.pop_back();

		return count;
	}

	int ParseMemberType(string& member_type, string& format)
	{
		static const unordered_map<string, string> FORMATS =
		{ {"double" ,"%lf"},{"float" ,"%f"},
			{"int" ,"%d"},	//{"DWORD" ,"%d"},	//conflict DWORD vs WORD
			{"short" ,"%hd"},{"WORD" ,"%hd"},
			{ "char" ,"%hhd"},{"BYTE" ,"%hhd"} };

		static const unordered_map<string, int> SIZES =
		{ {"double", 8},{"float", 4},
			{"int", 4},		//{"DWORD", 4},		//conflict DWORD vs WORD
			{"short", 2},{"WORD", 2},
			{ "char", 1},{"BYTE", 1} };

		if (member_type.find("cstr") != string::npos)
		{
			format = "%[^\t]%*c";
			return -1;	//Unk size
		}
		else if (member_type.find("DWORD") != string::npos)
		{
			format = "%d";
			return 4;
		}
		else
		{
			for (auto it = FORMATS.begin(); it != FORMATS.end(); it++)
			{
				if (member_type.find(it->first) != string::npos)
				{
					format = it->second;
					return SIZES.at(it->first);
				}
			}
		}

		format.clear();
		return 0;
	}

	void CalculateOffset(vector<OffsetInfo>& offset,int pack)
	{
		// vector saves members' sizes at the initial
		// we have to calculate the offset positions (with padding) then replace it.
		// for now only use pack 0 (default #pragma pack()) and pack 1

		size_t pos = 0;
		for (int i = 0; i < offset.size(); i++)
		{

			size_t& member_offset = offset[i].Offset;	//ref
			size_t member_size = member_offset;			//value
			int member_type = offset[i].Type;

			if (pack == 0)
			{
				if (member_type != LAZY_TYPE_FLAG::_CSTR_)
					while (pos % member_size)
						pos++;
			}
			else if (pack == 1)
			{
				//do nothing
			}

			member_offset = pos;
			pos += member_size;
		}
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

				if (count == 1)
					label += '\t' + member_name;
				else if (count > 1)
				{
					if (member_type.find("cstr") != string::npos)
					{
						label += '\t' + member_name;
					}
					else
					{
						for (int i = 0; i < count; i++)
							label += '\t' + member_name + "[" + to_string(i) + "]";
					}
				}
			}
			a = b + 1;
			b = members.find(';', a);
		}
		if (label.length() > 2)
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
				{
					string temp;
					int size = ParseMemberType(member_type, temp);
					if (size > 0)
						format += "\t" + temp;
				}
				else if (count > 1)
				{
					string temp;
					int size = ParseMemberType(member_type, temp);
					if (size == -1)	//cstr
					{
						format += "\t" + temp;
					}
					else if (size > 0)
					{
						for (int i = 0; i < count; i++)
							format += "\t" + temp;
					}
				}
			}
			a = b + 1;
			b = members.find(';', a);
		}

		if (format.length() > 1)
			format = format.substr(1);	//remove "\t" at the front

		return format;
	}

	vector<OffsetInfo> ParseMembersToOffset(string && members, int pack)
	{
		vector<OffsetInfo> offset;
		size_t pos = 0;
		size_t a = 0;
		size_t b = members.find(';', a);

		while (b != string::npos)
		{
			if (b > a)
			{
				string member, member_type, member_name;
				member = members.substr(a, b - a);

				size_t count = ParseMember(member, member_type, member_name);
				size_t type = ParseType(member_type);
				if (count == 1)
				{
					string format;
					int size = ParseMemberType(member_type, format);

					if (size > 0)
						offset.push_back({ type, (size_t)size, format });
				}
				else if (count > 1)
				{
					string format;
					int size = ParseMemberType(member_type, format);

					if (size == -1)	//cstr
						offset.push_back({ type, count, format });
					else if (size > 0)
						for (int i = 0; i < count; i++)
							offset.push_back({ type, (size_t)size, format });
				}
			}
			a = b + 1;
			b = members.find(';', a);
		}

		CalculateOffset(offset, pack);

		return offset;
	}
}
