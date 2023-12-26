# Battlers-Game-Project
This project takes inspiration from Pokemon to create a battler simulator to practice using C++ concepts, i.e.: 
 * batch processing functions
 * dynamic memory
 * pointers
 * classes.

My first project utilizes what I learned in Texas A&M's Introduction to Program Design and Concepts class to Pokemon, a game franchise I grew up with.

Quick Overview of how the game runs:
 1. Enter 'helper.txt' as the helper file (you can create your own with the guidelines defined below) to load characters to battler with
 2. Pick the number of local players
 3. Pick moves to try to defeat the other battler
 4. Choose to play again or stop playing

Helper File / Battler Creation Rules:
 - //the format of the helper file creation is important, please follow these rules accordingly to ensure smooth loading and gameplay
 - Lines 1-10: Create the image that will represent your battler, ensuring each line has 15 characters (use spaces to fill in blank space)
 - Line 11: Enter the name of the battler as one word (can use underscores as a space)
 - Line 12: Enter the type of the battler (i.e. Fire)
 - Line 13: Enter what type the battler is strong against (i.e. Grass - Fire types are strong against Grass types)
 - Line 14: Enter what type is strong against the battler's type (i.e. Water)
 - Line 15: Enter the HP of the battler (can include decimal values)
 - Line 16: Enter the 4 stats of the battler (physical attack & defense and special attack & defense)
 - Line 17-19: Enter the 3 moves for your battler, giving the move's name (as one word), type, damage type ('p' or 's'), and damage multiplier
 - Start the next battlers' info immediately in the next line 

Note:
In the given helper file, you may notice that there are null types. In this version of the game, null types will be strong against other null types.
Also, there is the special move 'Transform' by Shapesitto. Special moves can cause certain effects to occur other than simple damage to the opponent. For example, 'Transform' changes the user's battler data into the opponent's battler data, causing a doppelganger situation. It is possible that, in future updates, a new move could change the stats of any battler for several turns or change the type of any battler for the duration of the battler.
