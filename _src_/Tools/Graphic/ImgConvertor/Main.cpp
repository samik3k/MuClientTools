// This file contains the 'main' function. Program execution begins and ends there.
// Requirement: C++17, bit7z library, 7z.dll
#include "Core.h"
#include "ImgConvertor.h"
#include "OZJ.h"
#include "OZT.h"
#include "OZB.h"
#include "OZD.h"

using namespace std;

BOOL UnpackFile(const char* szInputPath, const char* szOutputPath = nullptr)
{
	DWORD N = Ext2Int(fs::path(szInputPath).extension().string().c_str());
	switch (N)
	{
	case INT_OZJ:
		return sInstance(OZJ)->Unpack(szInputPath, szOutputPath);
	case INT_OZT:
		return sInstance(OZT)->Unpack(szInputPath, szOutputPath);
	case INT_OZB:
		return sInstance(OZB)->Unpack(szInputPath, szOutputPath);
	case INT_OZD:
		return sInstance(OZD)->Unpack(szInputPath, szOutputPath);
	default:
		return FALSE;
	}
}

BOOL PackFile(const char* szInputPath, const char* szOutputPath = nullptr)
{
	DWORD N = Ext2Int(fs::path(szInputPath).extension().string().c_str());
	switch (N)
	{
	case INT_JPG:
		return sInstance(OZJ)->Pack(szInputPath, szOutputPath);
	case INT_TGA:
		return sInstance(OZT)->Pack(szInputPath, szOutputPath);
	case INT_BMP:
		return sInstance(OZB)->Pack(szInputPath, szOutputPath);
	case INT_DDS:
		return sInstance(OZD)->Pack(szInputPath, szOutputPath);
	default:
		return FALSE;
	}
}

int main(int argc, char** argv)
{
	const char* szInputPath = "SkillTree4th_I1.dds";
	const char* szOutputPath = nullptr;

	if (argc >= 2)
		szInputPath = argv[1];
	if (argc >= 3)
		szOutputPath = argv[2];

	if (!szInputPath)
	{
		cout << "\t Drag & Drop the Lang file/folder \n";
		cout << "\t  or use console command to execute with the file path. \n";
		return EXIT_FAILURE;
	}

	if (!fs::exists(szInputPath))
	{
		cout << "Error: Input file/folder does not exist.\n" << endl;
		return EXIT_FAILURE;
	}

	if (fs::is_regular_file(szInputPath))
	{
		if (!UnpackFile(szInputPath, szOutputPath) && !PackFile(szInputPath, szOutputPath))
		{
			return EXIT_FAILURE;	
		}
	}
	else if (fs::is_directory(szInputPath))
	{
		// Recursively converting files in a folder
		// Will do it later
	}
	else
	{
		cout << "Error: Invalid file/folder path.\n" << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}