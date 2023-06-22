#pragma once

extern injector::hook_back<unsigned short* (__cdecl*)(int, int)> MessageAddress;
unsigned short* MessageAddressHook(int packid, int num);

/// <summary>
/// Encodes a string of text into the SH4 encoded text format.
/// Only tested with basic Latin chars, punctuation, and numerals, JP/KOR characters and characters with diacritics may not work
/// </summary>
/// <param name="text">The text to encode</param>
/// <returns>The encoded text</returns>
char* convertMessage(const char* text);