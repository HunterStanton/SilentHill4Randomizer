# Silent Hill 4 Randomizer

A randomizer for Silent Hill 4: The Room, for the *GOG version* of the game. The randomizer offers several features to change up the gameplay of Silent Hill 4 to create brand new gameplay scenarios and challenges that weren't possible in the original game. It also has an option for restoring the "cut" hauntings from the PS2 version of the game.

This is intended for use with the GOG re-release of the game. Support for the older retail version is planned but not yet implemented.

## Features

* Randomized enemy spawns - you never know what is going to be in the next room
* Randomized weapon/consumable item pickups
* Randomized player model - play as Henry, early Henry, Eileen, or Nurse Eileen
* Randomized doors - certain areas now have doors randomized to destroy your muscle memory
* Randomized damage for those who like a challenge
* Deterministic randomness with support for setting a custom seed, so you can share seeds and experience the same randomized version of Silent Hill 4 every time for speedrunning or competition purposes
* New items in the random loot pool from previous Silent Hill games as well as items cut from Silent Hill 4
* Restores the "cut" hauntings from the PS2 version
* Easy configuration via an .ini file or the in-game "Extra Options" menu which now contains all the randomizer settings (and they save to your save file!)

## New Content

The randomizer adds new content *if* "Extra Content" and "Random Items" are both enabled in the options menu and as such are **completely optional**. These items seek to give a function to some previously nonfunctional, cut content in Silent Hill 4 as well as bring back some older weapons from previous Silent Hill titles. Because some like to keep the loot pool in a vanilla state, the new items are not obtainable unless using both of these toggles.

* Gold Pipe (Silent Hill 3)

* Silver Pipe (Silent Hill 3)

* Green Hyper Spray (Silent Hill 2)

* Lord's Prayer (cut from Silent Hill 4)

* Red Chrism (cut from Silent Hill 4)

## Installation

Use the [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) (32-bit version as Silent Hill 4 is a 32-bit game), rename the DLL to dsound.dll, then extract the contents of the [latest release](https://github.com/HunterStanton/SilentHill4Randomizer/releases) into the Silent Hill 4 game directory. You should end up with a /scripts/ folder and a couple new .bin files inside /data/.

If you are only interested in restoring the hauntings, disable all the randomizer settings in the .ini file, but ensure that `RestoreHauntings` is set to 1 or use [Steam006's Silent Hill 4 fix](https://community.pcgamingwiki.com/files/file/1332-silent-hill-4-pc-fix-by-steam006/) which now includes the hauntings fix.

##### Performance Note

The randomizer raises the maximum amount of memory that can be allocated in a room from roughly 67MB to roughly 134MB, meaning the system requirements are slightly higher than the vanilla game. You may run into out-of-memory crashes on minspec systems or virtual machines with 512MB of RAM or less.

## Demo

[![Silent Hill 4 Randomizer demo video](https://img.youtube.com/vi/yhN_v3E4eDw/0.jpg)](https://www.youtube.com/watch?v=yhN_v3E4eDw)

## Known Issues

- During the first encounter with the Sniffer dogs in Subway world, a frozen enemy with no collision might appear
- During the Andrew DeSalvo ghost hallway in the Water Prison, the animations may become very glitchy. This will persist until you leave the room
- Certain enemies (such as Wall Men) do not get randomized due to instability that can occur when randomizing them
- If you do not put the randomizer_x.bin files inside the /data/ directory, you will appear invisible, certain menus will appear white, and the game may be prone to crashing
- If playing as an Eileen model, she will still use Henry's SFX
- Randomized player models inside of cutscenes will appear very corrupted. A future version will have a toggle to disable randomizing player models inside of cutscenes for those who wish to avoid seeing this
- The new weapons can not be charged and make no SFX
- When playing as an Eileen player model, she has no collision with the actual Eileen

## Planned Additions

- More player models (Jasper, etc.)
- Randomization of Eileen/Cynthia's in-game models
- SFX that is correct for each player model
- Additional blood colors for the blood color setting

##### Potential future additions, if determined to be feasible

* Randomized ghost models

* Randomized door codes, water prison puzzle solution

* Random HUD colors (health bar, item outline colors, etc.)

* More weapons from older Silent Hill games

## Contributing

If you have fixed a bug in the code, implemented a new randomization feature, or want to change things for some reason, feel free to submit a pull request and I will give it a review.

For reporting bugs, please make a GitHub issue. Please include the randomizer log (which can be found in `<SH4 Install Directory>/scripts/randomizer.log`) in the issue so I can better identify where/how the issue is occurring.

## Special Thanks

* ThirteenAG, thelink2012, gabime, Thomas Monkman, and contributors to those libraries for creating the libraries used for hooking, logging, and INI parsing used to create this plugin
* roocker666 - doing some research on how the game stores room layouts in the executable and sending it to me
