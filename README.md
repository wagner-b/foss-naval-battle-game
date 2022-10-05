# foss-naval-battle-game
Free and Open-Source naval battle game that runs on the terminal (or cmd). Three difficulties to choose (easy, normal, and hard).

The goal in the game is to hit (shoot) every part of every ship, in an 8 x 8 grid. Ship size varies, but is always at least 2 blocks long (in vertical or horizontal position). The computer places the ships automatically and (pseudo) randomly in the grid for you. The harder the difficulty, less ammo you have, and more ships the computer places for you in the grid. Beware not to waste shots on blocks you've shot previously. There are more instructions in the game itself, if you need.

I've included binary releases for Linux and Windows systems (x86_64 CPU architecture). If you use a different system / CPU architecture, compile the program yourself. Compilation example: `gcc foss-naval-battle.c -o foss-naval-battle`.
