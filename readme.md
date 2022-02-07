# Silent Hill 4 Randomizer

A randomizer for Silent Hill 4: The Room, for the *GOG version* of the game. This does not work for the old PC port and probably never will, there is not really a reason to play the old port these days.

Automagically randomizes all enemies so you can encounter nurses on Forest world and other wacky things. Also randomly gives you one of three player models, default Henry, nurse Eileen, or regular Eileen.

## Installation
Use the Ultimate ASI Loader, rename the DLL to dsound.dll, then extract the contents of the .7z into the Silent Hill 4 game directory. You should end up with a /scripts/ folder and a couple new files inside /data/.

## Demo
[![Silent Hill 4 Randomizer demo video](https://img.youtube.com/vi/yhN_v3E4eDw/0.jpg)](https://www.youtube.com/watch?v=yhN_v3E4eDw)

## Known Issues
- Leaving a room and re-entering it will shuffle the enemies that are in that room, unless they are already dead
- If they are dead, they might appear as a standing enemy that does not move, cannot move, and will not attack you
- If you do not put the randomizer_x.bin files inside the /data/ directory, you will appear invisible
- If playing as Eileen, she will still use Henry's SFX
- I have not gone through the entire game with this, so there may be cases where it crashes on certain stages. If so please let me know!

## Planned Additions
- Randomize common, non-quest items
- More player models
- Randomization of Eileen/Cynthia's in-game models
- Random models in cutscenes
- SFX that is correct for each player model

## Special Thanks
* roocker666 - doing some research on how the game stores room layouts in the executable and sending it to me

Got any suggestions for what you'd like to see here? Found a bug? Speedran this and want to show me? Reach out to me on Twitter @hun10sta and I'd be happy to take a look or answer a question :) 
