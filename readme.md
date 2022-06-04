# Silent Hill 4 Randomizer

A randomizer for Silent Hill 4: The Room, for the *GOG version* of the game. The randomizer offers several features to change up the gameplay of Silent Hill 4 to create brand new gameplay scenarios and challenges that weren't possible in the original game. It also has an option for restoring the "cut" hauntings from the PS2 version of the game.

This is intended for use with the GOG re-release of the game, and does not work for the old PC port and probably never will, as there is not really a reason to bother with the old port these days.

## Features
* Randomized enemy spawns - you never know what is going to be in the next room
* Randomized weapon/consumable item pickups (the Torch is unaffected due to being tied to story progression)
* Randomized player model, play as Henry, Eileen, or Nurse Eileen, with more coming soon
* Restores the "cut" hauntings from the PS2 version
* Easy configuration via an .ini file

## Installation
Use the [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases) (32-bit version as Silent Hill 4 is a 32-bit game), rename the DLL to dsound.dll, then extract the contents of the .7z into the Silent Hill 4 game directory. You should end up with a /scripts/ folder and a couple new .bin files inside /data/.

If you are only interested in restoring the hauntings, disable all the randomizer settings in the .ini file, but ensure that `RestoreHauntings` is set to 1.

## Demo
[![Silent Hill 4 Randomizer demo video](https://img.youtube.com/vi/yhN_v3E4eDw/0.jpg)](https://www.youtube.com/watch?v=yhN_v3E4eDw)

## Known Issues
- Leaving a room and re-entering it will shuffle the enemies that are in that room, unless they are already dead
- If they are dead, they might appear as a standing enemy that does not move, cannot move, and will not attack you
- If you do not put the randomizer_x.bin files inside the /data/ directory, you will appear invisible
- If playing as Eileen, she will still use Henry's SFX

## Planned Additions
- More player models
- Randomization of Eileen/Cynthia's in-game models
- Random models in cutscenes
- SFX that is correct for each player model
- An extension to the in-game options menu for changing randomizer settings
- Randomized damage

## Contributing
If you have fixed a bug in the code, implemented a new randomization feature, or want to change things for some reason, feel free to submit a pull request and I will give it a review.

For reporting bugs, please make a GitHub issue. Please include the randomizer log (which can be found in `<SH4 Install Directory>/scripts/randomizer.log`) in the issue so I can better identify where/how the issue is occurring.

## Special Thanks
* roocker666 - doing some research on how the game stores room layouts in the executable and sending it to me
