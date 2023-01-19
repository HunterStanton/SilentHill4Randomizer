#pragma once

/// <summary>
/// Shows a message at the specified X/Y coords
/// </summary>
extern injector::hook_back<void(__cdecl*)(int, int, int, int)> MessagePut;

/// <summary>
/// Shows a message in the subtitles style
/// </summary>
extern injector::hook_back<void(__cdecl*)(int, int)> MessageSubtitlesPut;

/// <summary>
/// Shows a message and needs to be cleared by using MessageClear
/// </summary>
extern injector::hook_back<void(__cdecl*)(int, int)> MessageDemoSubtitlesPut;

/// <summary>
/// Shows a message and requires pressing the Use button/Mouse click to dismiss
/// </summary>
extern injector::hook_back<void(__cdecl*)(int, int)> MessageMemoPut;

/// <summary>
/// Shows a message and requires pressing the Use button/Mouse click to dismiss
/// </summary>
extern injector::hook_back<void(__cdecl*)(int, int)> MessageExplanationPut;

void InitializeMessageHandleFunctions();