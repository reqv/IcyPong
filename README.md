# IcyPong
**Current version: 0.1 beta**

IcyPong is a simple program based on the popular pong game, but include some new stuff.

### Features
- Fully playable game
- 1-Player or 2-Players gameplay
- Simple menu and game result screens
- Messaging system
- Bonuses

### Dependencies
SFML library version 2.0 or later. You cen get it from [Official Site](https://www.sfml-dev.org/).

### How to use this application

##### Compile
Use MingW C++ compiler to compile code.
1. `g++ -c message.cpp message.hpp obiekty.cpp obiekty.hpp core.cpp core.hpp main.cpp -I<sfml-install-path>/include`.
2. `g++ message.o obiekty.o core.o main.o -o IcyPong.exe -L<sfml-install-path>/lib -lsfml-graphics`.

In both steps `<sfml-install-path>` means path to your SFML folder installation.

##### Run
Open compiled binary file (make sure all other files like pictures are in the folder) and enjoy the game.

<img src="screenshot.png" alt="IcyPong"/>