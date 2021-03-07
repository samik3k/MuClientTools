#include "Core.h"
#include "EvoMonsterBoxBmd.h"

BOOL EvoMonsterBoxBmd::Decrypt()
{
	assert(_buf.size() == 164);

	//int size = *(int*)&_buf[0];
	int size = 156;

	_map.clear();

	Xor3Byte(&_buf[4], size);
	for (int i = 0; i < size; i++)
	{
		EVO_MONSTER_BOX* ptr = (EVO_MONSTER_BOX*)&_buf[4 + i];
		int key = GetKey(ptr);
		_map.insert(make_pair(key, ptr));
	}

	return TRUE;
}

BOOL EvoMonsterBoxBmd::Encrypt()
{
	assert(_buf.size() == 164);

	//int size = *(int*)&_buf[0];
	int size = 156;

	*(DWORD*)&_buf[0] = size;
	Xor3Byte(&_buf[4], size);
	*(DWORD*)&_buf[_buf.size()-4] = CalculateCRC(&_buf[4], size, _wkey);
	_map.clear();
	return TRUE;
}

void EvoMonsterBoxBmd::MakeLabelEx(ofstream & os)
{
	assert(os);
	os << "//This table relates to some chance of EvoMonster Reward." << endl;
	os << "//(the Drawing Cards Frame when using the box from killing golden evo monster)" << endl;
	os << "//I didn't check what it's used for. What if we set it all to 1 ???" << endl;
	os << "//www.youtube.com/watch?v=cvtJXclmj6E" << endl;

}
