#include "Core.h"
#include "MapCharactersBmd.h"

BOOL MapCharactersBmd::Decrypt()
{
	assert(_buf.size() > 0);

	size_t size = sizeof(MAP_CHARACTERS);
	size_t pos = 0;

	_map.clear();

	while (pos + size <= _buf.size())
	{
		Xor3Byte(&_buf[pos], 4);
		Xor3Byte(&_buf[pos + 4], 4);

		MAP_CHARACTERS* ptr = (MAP_CHARACTERS*)&_buf[pos];

		int m = ptr->Map;
		int c = ptr->Count;
		pos += size;
		for (int i = 0; i < c; i++)
		{
			if (pos < _buf.size())
			{
				Xor3Byte(&_buf[pos], 4);
			}
			else
			{
				cout << "Error: MapCharactersBmd::Decrypt(). Check size failed." << endl;
				return FALSE;
			}
			pos += 4;
		}

		int key = GetKey(ptr);
		InsertToMap(key, ptr);
	}

	return TRUE;
}

BOOL MapCharactersBmd::Encrypt()
{
	assert(_buf.size() > 0);

	size_t size = sizeof(MAP_CHARACTERS);
	size_t pos = 0;

	while (pos + size <= _buf.size())
	{
		MAP_CHARACTERS* ptr = (MAP_CHARACTERS*)&_buf[pos];

		int m = ptr->Map;
		int c = ptr->Count;

		Xor3Byte(&_buf[pos], 4);
		Xor3Byte(&_buf[pos + 4], 4);
		pos += size;

		for (int i = 0; i < c; i++)
		{
			if (pos < _buf.size())
			{
				Xor3Byte(&_buf[pos], 4);
			}
			else
			{
				cout << "Error: MapCharactersBmd::Encrypt(). Check size failed." << endl;
				return FALSE;
			}
			pos += 4;
		}
	}
	return TRUE;
}

void MapCharactersBmd::TxtOut(ofstream & os)
{
	assert(os);

	os << "//Map" << endl;
	os << "//Monster/NPC ID List:" << endl;
	os << "//=======================================" << endl;
	
	for (auto it = _map.begin(); it != _map.end(); it++)
	{
		MAP_CHARACTERS* ptr = it->second;
		int count = ptr->Count;

		if (count > 0)
		{
			os << "//Map : " << ptr->Map << " , Count : " << ptr->Count << endl;
			os << ptr->Map << endl;

			int* pID = ((MAP_CHARACTERS_EX*)ptr)->MonsterID;

			for (int i = 0; i < count; i++)
			{
				os << pID[i];
				if (i < count - 1)
					os << '\t';
			}
			os << endl;
		}
	}
}

void MapCharactersBmd::TxtIn(ifstream & is)
{
	assert(is);

	string line;
	size_t size = sizeof(MAP_CHARACTERS);
	size_t pos = 0;

	_map.clear();
	while (getline(is, line))
	{
		if (line[0] == '/' && line[1] == '/')
			continue;
		_buf.resize(pos + size);

		MAP_CHARACTERS* ptr = (MAP_CHARACTERS*)&_buf[pos];
		sscanf(line.c_str(), "%d", &ptr->Map);
		ptr->Count = 0;
		pos += size;
		if (getline(is, line))
		{
			line += '\t';
			size_t a = 0;
			size_t b = line.find('\t', a);
			vector<int> ids;

			do
			{
				if (b > a)
				{
					string s = line.substr(a, b - a);
					int id;
					if (!s.empty())
					{
						sscanf(s.c_str(), "%d", &id);
						ids.push_back(id);
					}
				}
				a = b + 1;
				b = line.find('\t', a);
			} while (b != string::npos);

			ptr->Count = ids.size();	//must assign Count before resize(). After resizing, data location may change.

			size_t data_size = 4 * ids.size();
			_buf.resize(pos + data_size);
			memcpy(&_buf[pos], ids.data(), data_size);
			pos += data_size;
		}
	}
}
