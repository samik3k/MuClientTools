#include "InfoTooltipBmd.h"

int InfoTooltipBmd::GetKey(INFO_TOOLTIP * ptr)
{
	return ptr->ID;
}

void InfoTooltipBmd::TxtOut(ofstream & os)
{
	assert(os);

	static const string LABEL = INFO_TOOLTIP::GetLabel();
	os << LABEL << endl;

	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		INFO_TOOLTIP* ptr = it->second;
		os << ptr->ID << '\t';
		auto x = (&ptr->Type_1)[2];
		for (int i = 0; i < 10; i++) {
			os << (&ptr->Type_1)[2*i] << '\t';
			os << (&ptr->Value_1)[2 * i] << '\t';
		}

		os << endl;
	}
}

void InfoTooltipBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const string FORMAT = INFO_TOOLTIP::GetFormat();

	string line;
	int size = sizeof(INFO_TOOLTIP);
	int n = 0;
	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(4 + ((n + 1) * size));

		INFO_TOOLTIP* ptr = (INFO_TOOLTIP*)&_buf[4 + (n * size)];
		sscanf(line.c_str(),
			//"%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd"
			FORMAT.c_str()
			, &ptr->ID
			, &ptr->Type_1, &ptr->Value_1, &ptr->Type_2, &ptr->Value_2, &ptr->Type_3, &ptr->Value_3, &ptr->Type_4, &ptr->Value_4
			, &ptr->Type_5, &ptr->Value_5, &ptr->Type_6, &ptr->Value_6, &ptr->Type_7, &ptr->Value_7, &ptr->Type_8, &ptr->Value_8
			, &ptr->Type_9, &ptr->Value_9, &ptr->Type_10, &ptr->Value_10
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
