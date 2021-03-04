#include "InfoTooltipTextBmd.h"

int InfoTooltipTextBmd::GetKey(INFO_TOOLTIP_TEXT * ptr)
{
	return ptr->ID;
}

void InfoTooltipTextBmd::TxtOut(ofstream & os)
{
	assert(os);
	
	//	"//ID\tText";
	static const string LABEL = INFO_TOOLTIP_TEXT::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		INFO_TOOLTIP_TEXT* ptr = it->second;
		os << ptr->ID << '\t';
		os << (Utls::IsEmptyCStr(ptr->Text) ? "[NULL]" : ptr->Text) << '\t';

		os << endl;
	}
}

void InfoTooltipTextBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = INFO_TOOLTIP_TEXT::GetFormat();

	string line;
	int size = sizeof(INFO_TOOLTIP_TEXT);
	int n = 0;
	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		INFO_TOOLTIP_TEXT* ptr = (INFO_TOOLTIP_TEXT*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			//"%hd\t%[^\t]%*c"
			FORMAT.c_str()
			, &ptr->ID, &ptr->Text
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
