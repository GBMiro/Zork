# Zork
Game Zork for the access test to the UPC's Masters Advanced Programming for AAA video games.

# About the game
This is an implementation of the well-known Zork videogame. It is a text-based video game where the player has to enter commands in order to advance in the game and win.  
This implementation plays through the journey of our hero Link, who is in the dragons' castle, to slay the dragon and free his village from their tirany.

# Author
Guillem Burgués Miró

# Source Code
You can find the code in the following link: https://github.com/GBMiro/Zork

# Comments

After a while not programming in C++, it's good to be back into it doing this text-based videogame. I had a joyful time.

# License

MIT License

Copyright (c) 2020 Guillem Burgués Miró

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

# How to play and a guide to finish the game

Available commands for the player:

- **look** -> Show room information
- **look X** -> Show information of X
- **take X** -> Take an item from the room into your inventory
- **take X from Y** -> Take item X from inside item Y
- **drop X** -> Drop on the floor the item X from your inventory
- **drop X into Y** -> Put item X inside item Y. Not all items can have another one inside
- **drink X** -> Drink item X
- **north** -> Go north if possible
- **south** -> Go south if possible
- **east** -> Go east if possible
- **west** -> Go west if possible
- **talk to X** -> Talk to NPC X
- **answer X with Y** -> Answer NPC X with Y
- **open X with Y** -> Open door blocking direction X (north, south, east, west) with Y
- **close X with Y** -> Close door of X (north, south, east, west) with Y 
- **equip X** -> Equip item X 
- **unequip X** -> Unequip item X
- **attack X** -> Attack creature X
- **loot X** -> Loot creature X to get its items
- **inventory** -> Show your inventory
- **stats** -> Show your stats
- **stats X** -> Show stats of X
- **help** -> Show available commands

## Guide

NOTE: The creatures in this game will attack you the moment you enter their room.

- In the entrance, attack the rat and then loot it to get an old key. Use this key to open the west and east door. Go west.

- You will be in the Sphinx's room. If you talk to it, it will tell you a riddle. You need to figure out the answer (you have three guesses) to have the sphinx unlock the door, leading to the north. Once the riddle is answered, go north. Get the right answer the first try or otherwise your game will be over sooner than later.

<details>
  <summary>Click to see the Riddle's answer</summary>
  
  - The answer is the letter **e**
</details>

- Now you are in the library. You will find a dagga and a box. If you take a look into the box, you will see it has a note and a key. Take the key, take the dagga, equip the dagga and go south.

- You will be back in the Sphinx's room. Go east. 

- You will be back in the entrance. If you didn't unlock the east door with the old key, do it now. Go east.

- You are now in the armory. Take the potion and go north. Remember to equip the dagga before going north if you didn't do it before

- You will be attack by a troll. Fight back until it's dead. Loot the troll and equip the sword and the shield. Drink the potion to restore your health, go south and then west to arrive at the entrance.

- Unlock the north door with the key (not the old key) and go north to enter the courtyard.

- The dragon will attack until you either kill it or kills you. If you kill the dragon you will have beaten the game.

## List of commands to finish the game

<details>
  <summary>Show</summary>
  
attack rat  
loot rat  
open west with old-key  
west  
answer sphinx with e  
north  
take key from box  
take dagga  
equip dagga  
south  
east  
open east with old-key  
east  
take potion  
north  
attack troll  
attack troll  
attack troll  
attack troll  
loot troll  
equip sword  
equip shield  
drink potion  
south  
west  
open north with key  
north  
attack dragon  
attack dragon  
attack dragon  
</details>
