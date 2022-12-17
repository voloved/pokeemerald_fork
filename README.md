# Pokémon Emerald Gift

This is a fork of the [decompilation of Pokémon Emerald](https://github.com/pret/pokeemerald).  
Made as a 2022 Christmas gift for a friend, where the character sprites are made to look like him.  
To set up the repository, see [INSTALL.md](INSTALL.md).

## NB_Sprite Additions
- Added graphics for Nick's front, back, intro scene, and overworld sprites
- Changed character's house to match Nick's
- Added secret base as garage (Secret Power TM is in PC and 2 straight boards are added as decorations when a new game is made)
- Added a basketball hoop
- Changed hometown name
- Added message on copyright screen
- Made 'Nick' be the default name to use if no name is set for a new character
- Add Jaime...kind of

## Dev Additions
- Toggle running
  - Created before finding [this](https://www.pokecommunity.com/showpost.php?p=10161076&postcount=72), but it had the same idea
- Made running indoors possible 
  - Created before finding [this](https://github.com/pret/pokeemerald/wiki/Allow-running-indoors), but it's the same idea
- [Holding L is now turbo A](https://github.com/pret/pokeemerald/wiki/Make-L-Button-Be-Turbo-A-When-L=A-Option-Is-Set)
- No battery run dry message appears
- [Removing Badge Checks for HMs](https://www.pokecommunity.com/showpost.php?p=10036664)
- [White Out money calculation to match future gens and displays money lost amount](https://github.com/pret/pokeemerald/wiki/Better-White-Out-Money-Calculation)
- [Remove the extra save confirmation](https://github.com/pret/pokeemerald/wiki/Remove-the-extra-save-confirmation)
- [Increase Text Speed Beyond Fast](https://www.pokecommunity.com/showpost.php?p=10400198)
- [Return and Frustration show power in summary screen](https://www.pokecommunity.com/showpost.php?p=10575976&postcount=420)
- [Pushing R when looking at the clock allows for the time to be changed](https://www.pokecommunity.com/showpost.php?p=10481737)
  - Tilemap for clock now includes mention of R to reset
- Faster Pokémon Center healing
  - Created before finding [this](https://github.com/pret/pokeemerald/wiki/Speedy-Nurse-Joy), but same idea
- Party now gets healed after winning a gym badge (and when receiving your Pokédex completion diploma at the Lilycove Motel)
- [Set L=A and fast scroll text as the default](https://www.pokecommunity.com/showpost.php?p=9967853&postcount=5)
- [Prompt for reusing Repels](https://github.com/pret/pokeemerald/wiki/Prompt-for-reusing-Repels)
- [Simplistic Battle Intro](https://www.pokecommunity.com/showpost.php?p=10473117)
- [Added type color that shows battle effectiveness and added ability to toggle this feature in the option menu.](https://github.com/pret/pokeemerald/wiki/Show-Type-Effectiveness-In-Battle-Using-Pre-Existing--Function-and-Disable-in-Option-Menu)
  - Used [this](https://www.pokecommunity.com/showpost.php?p=10167016&postcount=83), but the vanilla code needed modification for it to work well.
- [Added debug menu](https://www.pokecommunity.com/showpost.php?p=10220970&postcount=175) (turned off by default)
- [Faster HP Drain](https://github.com/pret/pokeemerald/wiki/Faster-HP-Drain)
- [Wrong Save File Error Message](https://www.pokecommunity.com/showpost.php?p=10449518)
- [Surfing Dismount Ground Effects](https://github.com/pret/pokeemerald/wiki/Surfing-Dismount-Ground-Effects)
- [Improving the WaitForVBlank function](https://github.com/pret/pokeemerald/wiki/Improving-the-WaitForVBlank-function)
- [Lower case after first input in the naming screen](https://www.pokecommunity.com/showpost.php?p=10199896&postcount=139)
- [Let a Pokémon forget any move they know](https://www.pokecommunity.com/showpost.php?p=10182839&postcount=119)
- Default Options are now fast text speed and L=A by default
  - Made before finding [this](https://www.pokecommunity.com/showpost.php?p=9967853&postcount=5), but same idea
- Turned off getting match calls from trainers who are not looking to battle.
- Intro now shows the biking trainer as the gender of the save file (defualts to male)
- Made Cleanse Tag turn the off all wild encounters and made it's held ability work if held by any Pokémon in the party
- Made Poké Doll cause no trainers to see you. You can still go up and talk with them.
- Added Beldom in Meteor Falls and Mareep in Route 110
- Removed small bugs with *#define BUGFIX* in *config.h*
