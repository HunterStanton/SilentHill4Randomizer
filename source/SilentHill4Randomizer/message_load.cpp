#include "stdafx.h"
#include "sh4/game/message/message_load.h"
#include <plog/Log.h>

// new options menu text

const char* randomEnemies = convertMessage("Random Enemies");
const char* randomItems = convertMessage("Random Items");
const char* randomModels = convertMessage("Random Models");
const char* randomDamage = convertMessage("Random Damage");
const char* extraContent = convertMessage("Extra Content");
const char* theFogApproaches = convertMessage("The Fog Approaches");
const char* randomEnemiesExpl = convertMessage("Randomizes the enemies encountered\r\nin each room. Can cause crashes, so\r\ndon't forget to save often.");
const char* randomItemsExpl = convertMessage("Randomizes the weapons and consumable items\r\npicked up. Does not randomize quest\r\nitems or the Torch to prevent softlocks.");
const char* randomModelsExpl = convertMessage("Randomizes the player model.");
const char* randomDamageExpl = convertMessage("Randomizes the amount of damage\r\nHenry and Eileen take.\x01\xFE Only recommended\r\nfor experienced players.\x01\x20");
const char* extraContentExpl = convertMessage("Enables extra items/weapons in the loot pool.\r\nOnly effective if \"Random Items\" is enabled.");
const char* theFogApproachesExpl = convertMessage("Adds thick white fog everywhere.");

// custom weapons

const char* goldPipe = convertMessage("Golden Pipe");
const char* goldPipeDescription = convertMessage("\x01\xFFGolden Pipe [weapon]\x01\x20\r\nA pipe made of solid gold. It feels like\r\nit would do some serious damage.");

// text replacements

const char* newStartMessage = convertMessage("Some parts of this game may be\r\nconsidered violent or cruel.\r\n\r\nSilent Hill 4 Randomizer is active.");

std::map<int, const char *> textMap = {
	{ 2000, randomEnemies},
	{ 2001, randomItems },
	{ 2002, randomModels},
	{ 2003, extraContent },
	{ 2004, randomDamage},
	{ 2005, theFogApproaches},
	{ 2100, randomEnemiesExpl },
	{ 2101, randomItemsExpl},
	{ 2102, randomModelsExpl },
	{ 2103, extraContentExpl},
	{ 2104, randomDamageExpl },
	{ 2105, theFogApproachesExpl },
	{ 2020, goldPipe},
	{ 2021, goldPipeDescription },
};

/// <summary>
/// Encodes a string of text into the SH4 encoded text format.
/// </summary>
/// <param name="text">The text to encode</param>
/// <returns>The encoded text</returns>
char* convertMessage(const char* text)
{
	int len = strlen(text);
	char* encodedString = new char[len + 0x6]; // length of string + 6 msg control chars

	// control chars for beginning-of-message
	encodedString[0] = 0x00;
	encodedString[1] = 0x80;

	for (int i = 0; i < strlen(text); i++)
	{
		if (text[i] == 0x20)
		{
			// spaces are 0x00
			encodedString[i + 2] = 0x00;
			continue;
		}

		// handle line breaks
		if (text[i] == 0xA)
		{
			encodedString[i + 2] = 0xFD;
			continue;
		}
		if (text[i] == 0xD)
		{
			encodedString[i + 2] = 0xFF;
			continue;
		}

		if (text[i] == 0xF7)
		{
			encodedString[i + 2] = 0x00;
			continue;
		}


		encodedString[i + 2] = 0x100 - text[i];
	}

	// control chars indicating end-of-message
	encodedString[len + 2] = 0xFF;
	encodedString[len + 3] = 0xFF;
	encodedString[len + 4] = 0x00;
	encodedString[len + 5] = 0x80;

	return encodedString;
}


injector::hook_back<unsigned short* (__cdecl*)(int, int)> MessageAddress;
unsigned short* MessageAddressHook(int packid, int num)
{
	// splash screen text
	if (packid == 0 && num == 0xc5)
	{
		return (unsigned short*)newStartMessage;
	}

	if (num > 1999)
	{
		if (textMap.find(num) != textMap.end())
		{
			return (unsigned short*)textMap[num];
		}
	}

	return MessageAddress.fun(packid, num);
}
