#include "InfoTooltipBmd.h"

int InfoTooltipBmd::GetKey(INFO_TOOLTIP * ptr)
{
	return ptr->ID;
}

void InfoTooltipBmd::TxtOut(ofstream & os)
{
	assert(os);

	os << "//ID";
	for (int i = 0; i < 10; i++)
	{
		char temp[64];
		sprintf(temp, "\tType_%d\tValue_%d", i + 1, i + 1);
		os << temp;
	}
	os << endl;


	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		INFO_TOOLTIP* ptr = it->second;
		os << ptr->ID << '\t';
		for (int i = 0; i < 10; i++) {
			os << ptr->Info[i].Type << '\t';
			os << ptr->Info[i].Value << '\t';
		}

		os << endl;
	}
}

void InfoTooltipBmd::TxtIn(ifstream & is)
{
	assert(is);

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
			"%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd\t%hd"
			, &ptr->ID, &ptr->Info[0].Type, &ptr->Info[0].Value, &ptr->Info[1].Type, &ptr->Info[1].Value
			, &ptr->Info[2].Type, &ptr->Info[2].Value, &ptr->Info[3].Type, &ptr->Info[3].Value
			, &ptr->Info[4].Type, &ptr->Info[4].Value, &ptr->Info[5].Type, &ptr->Info[5].Value
			, &ptr->Info[6].Type, &ptr->Info[6].Value, &ptr->Info[7].Type, &ptr->Info[7].Value
			, &ptr->Info[8].Type, &ptr->Info[8].Value, &ptr->Info[9].Type, &ptr->Info[9].Value
		);

		//Won't check duplicated key. Assuming ppl know what they do
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
		n++;
	}
	*(DWORD*)&_buf[0] = n;
	_buf.resize(4 + (n * size) + 4);	//last 4 BYTES for CRC
}
