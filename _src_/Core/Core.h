#ifndef CORE_PCH_H
#define CORE_PCH_H

#define MU_SEASON	13
#define MU_EP		1

#pragma warning(disable: 4018)
#pragma warning(disable: 4244)
#pragma warning(disable: 4996)

#include <assert.h>
#include <iostream>
#include <fstream>
#include <filesystem> // C++17
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include "7z/include/bit7z.hpp"

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

namespace fs = std::filesystem;
using namespace  std;


#include "Utls.h"
#include "LazyStruct.h"
#include "SingletonInstance.h"
#include "MuCommon.h"
#include "ClientStructures.h"

class MuCrypto;
class BaseIO;

#include "MuCrypto.h"
#include "BaseIO.h"
#include "TxtConvertor.h"
#endif // !CORE_PCH_H