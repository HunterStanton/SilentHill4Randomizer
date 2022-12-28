#include "stdafx.h"
#include "sh4/game/objs/game_objset.h"
#include <plog/Log.h>

void LoadSceneSets()
{
	std::vector<std::wstring> halfSets = { L"3ldk", L"subway", L"forest", L"water", L"building" };
	std::vector<std::wstring> standaloneSets = { L"home", L"hospital", L"pasthome", L"last", L"tunnel", L"spiral" };

	for (int i = 0; i < halfSets.size(); i++)
	{
		std::wstring concatted_stdstr = L".\\randomizer\\scene_sets\\" + halfSets[i] + L"_1sthalf.set";
		LPCWSTR concatted = concatted_stdstr.c_str();
		HANDLE file = CreateFile(concatted, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD fileSize = GetFileSize(file, NULL);
		LPVOID fileBuffer = VirtualAlloc(NULL, fileSize, MEM_COMMIT, PAGE_READWRITE);
		DWORD bytesRead;
		if (!ReadFile(file, fileBuffer, fileSize, &bytesRead, NULL))
		{
			PLOG(plog::error) << "Could not load scene set " << concatted_stdstr;
		}
		else
		{
			CloseHandle(file);
			PLOG(plog::info) << "Successfully loaded scene set " << concatted_stdstr;
			injector::WriteMemory<int>(0x006553a8 + (4 * i), *(int*)&fileBuffer, true);
		}
	}

	for (int i = 0; i < standaloneSets.size(); i++)
	{
		std::wstring concatted_stdstr = L".\\randomizer\\scene_sets\\" + standaloneSets[i] + L".set";
		LPCWSTR concatted = concatted_stdstr.c_str();
		HANDLE file = CreateFile(concatted, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD fileSize = GetFileSize(file, NULL);
		LPVOID fileBuffer = VirtualAlloc(NULL, fileSize, MEM_COMMIT, PAGE_READWRITE);
		DWORD bytesRead;
		if (!ReadFile(file, fileBuffer, fileSize, &bytesRead, NULL))
		{
			PLOG(plog::error) << "Could not load scene set " << concatted_stdstr;
		}
		else
		{
			CloseHandle(file);
			PLOG(plog::info) << "Successfully loaded scene set " << concatted_stdstr;
			injector::WriteMemory<int>(0x006553bc + (4 * i), *(int*)&fileBuffer, true);
		}
	}

	for (int i = 0; i < halfSets.size(); i++)
	{
		std::wstring concatted_stdstr = L".\\randomizer\\scene_sets\\" + halfSets[i] + L"_2ndhalf.set";
		LPCWSTR concatted = concatted_stdstr.c_str();
		HANDLE file = CreateFile(concatted, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD fileSize = GetFileSize(file, NULL);
		LPVOID fileBuffer = VirtualAlloc(NULL, fileSize, MEM_COMMIT, PAGE_READWRITE);
		DWORD bytesRead;
		if (!ReadFile(file, fileBuffer, fileSize, &bytesRead, NULL))
		{
			PLOG(plog::error) << "Could not load scene set " << concatted_stdstr;
		}
		else
		{
			CloseHandle(file);
			PLOG(plog::info) << "Successfully loaded scene set " << concatted_stdstr;
			injector::WriteMemory<int>(0x006553dc + (4 * i), *(int*)&fileBuffer, true);
		}
	}

	for (int i = 0; i < standaloneSets.size(); i++)
	{
		std::wstring concatted_stdstr = L".\\randomizer\\scene_sets\\" + standaloneSets[i] + L".set";
		LPCWSTR concatted = concatted_stdstr.c_str();
		HANDLE file = CreateFile(concatted, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD fileSize = GetFileSize(file, NULL);
		LPVOID fileBuffer = VirtualAlloc(NULL, fileSize, MEM_COMMIT, PAGE_READWRITE);
		DWORD bytesRead;
		if (!ReadFile(file, fileBuffer, fileSize, &bytesRead, NULL))
		{
			PLOG(plog::error) << "Could not load scene set " << concatted_stdstr;
		}
		else
		{
			CloseHandle(file);
			PLOG(plog::info) << "Successfully loaded scene set " << concatted_stdstr;
			injector::WriteMemory<int>(0x006553f0 + (4 * i), *(int*)&fileBuffer, true);
		}
	}

	return;
}



