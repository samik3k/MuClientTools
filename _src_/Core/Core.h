#ifndef COMMON_PCH_H
#define COMMON_PCH_H

#define MU_SEASON	13
#define MU_EP		1

#pragma warning(disable: 4018)
#pragma warning(disable: 4244)
#pragma warning(disable: 4996)

#include <assert.h>
#include <iostream>
#include <fstream>
#include <filesystem> // C++17
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
#include "SingletonInstance.h"
#include "ClientStructures.h"

class MuCrypto;
class BaseIO;

#include "MuCrypto.h"
#include "BaseIO.h"
#include "TxtConvertor.h"
#endif // !COMMON_PCH_H