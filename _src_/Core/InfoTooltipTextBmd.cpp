#include "InfoTooltipTextBmd.h"

int InfoTooltipTextBmd::GetKey(INFO_TOOLTIP_TEXT * ptr)
{
	return 0;
}

void InfoTooltipTextBmd::TxtOut(ofstream & os)
{
	assert(os);

	static const char* LABEL =
		"//ID\tText";
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		INFO_TOOLTIP_TEXT* ptr = it->second;
		os << ptr->ID << '\t';
		os << ptr->Text << '\t';

		os << endl;
	}
}

void InfoTooltipTextBmd::TxtIn(ifstream & is)
{
	assert(is);

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
			"%hd\t%[^\t]%*c"
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
