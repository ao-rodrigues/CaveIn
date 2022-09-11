# CaveIn
A clone of the game Ores built from scratch using SDL2.

# Running the game
A pre-built version of the game can be found under `\Build`. Just run the executable `CaveIn.exe` inside that folder.

## Controls

- LMB - Select and destroy Ores
- Esc - Pause the game

**Note #1**: The game stores high scores in a file called `high_score.txt` located in the same directory as the executable. Moving or deleting this file will break the game.

**Note #2**: The game requires having the Visual C++ x64 Redistributables for Visual Studio 2019 and will throw an error on startup if they're not found.
Should that happen, here's a link:

https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0

# Building the game
This project was built in Windows using Visual Studio 2019 Community Edition. Just open the `Ores.sln` file and build the solution inside Visual Studio.
