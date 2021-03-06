#include "Core.h"
#include "SocketItemBmd.h"

BOOL SocketItemBmd::Decrypt()
{
	assert(_buf.size() > 0);

	int size = sizeof(SOCKET_ITEM_INFO);
	int kind = 3;
	int count = 50;

	if (_buf.size() != (kind * count * size))
	{
		cout << "Warning: InputFile size check failed. (may be a wrong file) \n";
#ifdef STRICT_SIZE_CHECK
		return FALSE;
#endif
	}

	_map.clear();

	int pos = 0;

	for (int i = 0; i < kind; i++)
	{
		for (int j = 0; j < count; j++)
		{
			Xor3Byte(&_buf[pos], size);
			SOCKET_ITEM_INFO* ptr = (SOCKET_ITEM_INFO*)&_buf[pos];

			int key = (i << 8) | j;
			_map.insert(make_pair(key, ptr));

			pos += size;
		}
		
	}

	return TRUE;
}

BOOL SocketItemBmd::Encrypt()
{
	assert(_buf.size() > 0);

	int size = sizeof(SOCKET_ITEM_INFO);
	for (int p = 0; p + size <= _buf.size(); p += size)
		Xor3Byte(&_buf[p], size);

	_map.clear(); // T* now -> encrypted data
	return TRUE;
}

void SocketItemBmd::TxtIn(ifstream & is)
{
	assert(is);

	static const vector<OffsetInfo> OFFSET = SOCKET_ITEM_INFO::GetOffset();

	string line;
	size_t size = sizeof(SOCKET_ITEM_INFO);
	size_t kind = 3;
	size_t count = 50;

	_buf.resize(size * kind * count);

	_map.clear();

	int n = 0;
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;

		SOCKET_ITEM_INFO* ptr = (SOCKET_ITEM_INFO*)&_buf[n * size];
		memset(ptr, 0x00, size);

		line += '\t';
		size_t a = 0;
		size_t b = line.find('\t', a);
		size_t i = 0;
		do
		{
			if (b > a)
			{
				string s = line.substr(a, b - a);
				size_t pos = OFFSET[i].Offset + (size_t)ptr;
				sscanf(s.c_str(), OFFSET[i].Format.c_str(), (void*)pos);
			}

			i++;
			a = b + 1;
			b = line.find('\t', a);
		} while (b != string::npos && i < OFFSET.size());

		// No need
		//int key = GetKey(ptr);
		//_map.insert(make_pair(key, ptr));
		n++;
	}
}
