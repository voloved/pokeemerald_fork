# Pokémon Emerald Gift

This is a fork of the [decompilation of Pokémon Emerald](https://github.com/pret/pokeemerald).  
Made as a 2022 Christmas gift for a friend, where the character sprites are made to look like him.  
To set up the repository, see [INSTALL.md](INSTALL.md).

Link to [Patch File is Here](https://drive.google.com/drive/folders/1GFChFDEmOJHn6WBoZAN-GRA9a2UXGeu_?usp=sharing).  
To build it, use [LunarIPS](https://fusoya.eludevisibility.org/lips/) and your legally obtained copy of Pokémon Emerald (those devs who made the game 20 years ago gotta eat too).  

 ![Example](https://i.imgur.com/KSMvc0h.png)  

## Not Yet Versioned
 - [Added Eon Flute](https://www.pokecommunity.com/showthread.php?t=422107) [Credit: camthesaxman and paccy for the Emerald Port]
 - [Go-Goggles can be Used to and a Sandstorm in Battles](https://gitlab.com/devolov/pokeemerald_fork/-/commit/00c938536e5abfe4db4e89fd3e93b2c6ac1a450c)
 - [Added Ability to See Zigzagoon on Cable Car](https://www.youtube.com/watch?v=7xdcbbfwEto) [Credit: Goppier]
 - All Battle Frontier Pokémon are fully-evolved.
 - Player's icon shown and them raising their Poké Ball not shown when performing a field move that the party does not known.
 - Sped up slow and medium text speed.
 - [Arrows show that cycling balls can be done.](https://github.com/rh-hideout/pokeemerald-expansion/pull/3039)
 - Thief Ball option only shows if the Pokémon's catch rate is low enough (proxy for its rarity).
 - Register icon for Cleanse Tag and Poké Doll aligned.
 - Repels can now be registered items.
 - Added a Mean Zigzagoon in Petalberg Woods.
 - Bug fix where player is not properly shown when using Surf or Dive.

## v2.1.0
 - [Added last used ball in battle menu.](https://github.com/rh-hideout/pokeemerald-expansion/commit/c06029bc721119b0efd6e26c24a3f77772dfd77b) [Credit: Ghoulslash]
   - This defaults to a Thief ball if in a trainer battle.
   - Gives suggested ball on the first turn (and the Timer Ball aftewr enough turns)
 - [Added Second Page to Options Menu.](https://github.com/pret/pokeemerald/wiki/Multipage-Options-Menu)
   - Includes: Show Follower, Show Ball Suggestion, Ball Suggestion Preferences, Difficulty.
 - [Holding Select Allows For A Second Register Item](https://github.com/pret/pokeemerald/wiki/Holding-Select-Allows-For-A-Second-Register-Item)
 - Entering the Konami Code at the Main Menu Screen Allows for the Debug Menu in the Start Menu.
 - Truck That Player Comes To Hometown In Is Now A UHaul.
 - Added 'Add All HMs' To Debug Menu.
 - Wally opens correct pocket for Poké Ball.
 - A trainer you've already battled can no longer reset FLAG_RAN_FROM_TRAINER.
 - Cleanse Tag and Poké Doll can be registered in place of being tossed.
 - Cannot run from Double Battles.
 - Added a Mew under the truck in Lilycove, where Strength is needed to move the truck.
   - After it's moved, there is a Thief Ball in the back of the Truck.
 - Bug fix to allow stolen Pokémon to count towards Pokédex.

## v2.0.0
 - Secret Bases Able to Have 36 Decorations (Was 16), But Only a Max Base count of 16 (Was 20).
   - This breaks compatability with sharing Secret Bases with the vanilla game.

## v1.6.0
 - [Make Multiple Secret Bases](https://github.com/pret/pokeemerald/wiki/Make-Multiple-Secret-Bases)
 - When putting a Pokémon into a new ball, the old ball gets put back into the bag if it's not a Thief Ball nor Master Ball.
 - [Allow Move Relearner to Teach Moves that Pre Evolutions Know](https://github.com/pret/pokeemerald/wiki/Allow-Move-Relearner-to-Teach-Moves-that-Pre-Evolutions-Know)
 - Animated Missingno follower sprite.
 - [Pressing Start in a Battle Will Show the Description of the Move.](https://github.com/pret/pokeemerald/wiki/Add-Description-Submenu)
 - [Allow Running From Trainer Battles](https://github.com/pret/pokeemerald/wiki/Allow-Running-From-Trainer-Battles)
   - This will not work when running the Nuzlocke challenge.
 - [Key Items With No Field Effect Will No Longer Be Register-able Nor Usable](https://github.com/pret/pokeemerald/wiki/Make-Key-Items-That-Cannot-Be-Used-In-The-Field-Not-Show-A-Use-or-Register-Option)
 - [Added BetterBag. This makes the bag be able to hold 78 more items.](https://github.com/pret/pokeemerald/wiki/Feature-Branches#BetterBag) [Credit: AsparagusEduardo]
   - This will keep compatability with an vanilla Emerald save file, but going back to the vanilla game saving in this game will cause battle items, treasures, and medicine to disappear.
 - Made Poké Doll a toggle-able item, like Cleanse Tag.
 - Bug fix on an endless loop if an Eeveelution is bred.
 - Holding R when starting a wild encounter will not allow running if escaping isn't possible.
 - Text Scroll is Mildly Faster.

## v1.5.4
 - Gen 4 Pokémon are Added as Followers.
 - Berry Pick-up Text On New Berry Now Works.
 
## v1.5.3
 - [Loading the game now ages the berries by 12 hours and iterates daily events by a day.](https://github.com/pret/pokeemerald/wiki/Get-Rid-of-Battery-Run-Dry-Error-Message#extra-update-daily-events-and-berries-still-grow-when-playing-without-a-rtc)
 - Berries that are fully-grown do not continue the cycle if the RTC is dead.
 - Overlevel check turns off if Nuzlocke setting is off.

## v1.5.2
 - Readded Nuse Joy chime when healing.
 - No longer shows Nuzlocke cap if player is champion.

## v1.5.1
 - Got rid of item description window on first berry picked due to it being buggy.
 - Nurse Joy now tells you what the level cap for Nuzlocke is.
 - Resetting wallclock ages the berry growth by 24 hours and iterates daily events by a day.
 - PokéVial renamed to POKéVIAL.
 - Fury Cutter based power changed to 40.
 - Able to buy Thief Ball in Petalburg Mart after 6 badges.
 - Biking indoors is now allowed.
 - Fire-type cannot be frozen.
 - Player PC now has 10 Thief Balls in it rather than 5.
 - Some rocks can permanently be smashed.

 ## v1.5.0
 - [Added PokéVial](https://github.com/pret/pokeemerald/wiki/Add-A-PokeVial-Item)
 - [Fish Will Now Always Get on Hook](https://github.com/pret/pokeemerald/wiki/Fish-Will-Now-Always-Get-on-Hook)
 - [Field Move Logic Cleaned Up and Flash Now Automatically Runs When Entering a Cave](https://github.com/pret/pokeemerald/wiki/Use-HMs-Without-Any-Pokemon-in-your-Party-Knowing-Them#any-pokemon-can-use-field-move-so-long-as-hm-is-in-bag)
 - [Item Descriptions On First Obtain](https://www.pokecommunity.com/showpost.php?p=10126502&postcount=46)[Credit: Ghoulslash]
 - [Plural giveitem](https://www.pokecommunity.com/showpost.php?p=10177314&postcount=107)[Credit: Ghoulslash]
 - [Amulet Coin Effects If Anyone In Party is Holding It](https://github.com/pret/pokeemerald/wiki/Amulet-Coin-Effects-If-Anyone-In-Party-is-Holding-It)
 - Thief Ball now works on Elite Four as well.
 - Starter evolutions can now learn the Giga Drain, Flame Thrower, Hydro Pump moves the basics can learn.
 - [Name Rater now allows traded Pokémon to be renamed.](https://github.com/pret/pokeemerald/wiki/Name-Rater-Allows-Traded-Pokemon-to-be-Renamed)
 - [Add Move Relearning Into Party Menu](https://www.pokecommunity.com/showpost.php?p=10470602) [Credit: DiegoIsAwesome]
 - [Swap party screen slots using Select](https://www.pokecommunity.com/showpost.php?p=10420662)
 - [Fixing the aspect ratio of the Pokémon logo on the title screen](https://github.com/pret/pokeemerald/wiki/Fixing-the-aspect-ratio-of-the-Pok%C3%A9mon-logo-on-the-title-screen) [Credit: meejle]
 - [Pokémon can now follow you.](https://github.com/aarant/pokeemerald/commits/followers) [Credit: aarant]
   - Gen 4 Pokémon are ignored as followers.
 - [Added Bag Sorting](pokecommunity.com/showpost.php?p=10167488&postcount=84) [Credit: Ghoulslash]
 - [Make Poké Balls usable outside of battles](https://www.pokecommunity.com/showthread.php?p=10539730#post10539730) [Credit: Lunos]
 - [Cleanse Tag can now be a use item as well as being held.](https://github.com/pret/pokeemerald/wiki/Make-Cleanse-Tag-Avoid-All-Wild-Encounters-and-Usable-If-Held-By-Anyone-in-Your-Party;-Make-PokeDoll-Do-the-Same-for-Trainers-Seeing-You#make-cleanse-tag-a-toggle-able-use-item)
 - Doubled shiny odds.
 - Buying more than 10 Poké Balls gives an extra.
 - Indicator shown in Nuzlocke challenge if Pokémon can be caught.
 - Mareep is female 75% of the time.

## v1.4.0
- Added Weavile, Magnezone, Lickilicky, Rhyperior, Tangrowth, Electivire, Magmortar, Togekiss, Yanmega, Gliscor, Mamoswine, Porygon Z, Gallade, Probopass, Dusknoir
- [Added Difficulty Mode](https://github.com/pret/pokeemerald/wiki/Add-Difficulty-Mode)
- [Infinite TM usage](https://github.com/pret/pokeemerald/wiki/Infinite-TM-usage) [Credit: ExpoSeed]
- [Item Automatically Goes to PC if Bag is Full](https://github.com/pret/pokeemerald/wiki/Item-Automatically-Goes-to-PC-if-Bag-is-Full)
- [Fix AI's Switch In Battle (it will remain the same on easy difficulty)](https://github.com/pret/pokeemerald/wiki/Fix-AI's-Switch-In-Battle)
- Added ability to change how much EXP you'll get in battle.
- Added Nuzlocke options.
  - [Dupes Clause.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge#Dupes-Clause)
  - [Disallow overleveling Gym Leaders.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge#Cant-Overlevel-Leaders)
  - [Disallow shift mode.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge#force-set-mode)
  - [Ignore your held items.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge#no-held-items)
  - [No Battle Items.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge#no-battle-items)
- [Gen. 6 style Exp. Share](https://github.com/pret/pokeemerald/wiki/Gen-6-style-Exp.-Share---Alternative-Option)
- [All Trees Permanently Get Cut](https://github.com/pret/pokeemerald/wiki/All-Trees-Permanently-Get-Cut)
- Bug fix on Blaziken learning Death Move.
- Norman's Slaking no longer knows counter.
- Bug fix on no effect move being orange when move has low PP in showing type effectiveness.
-  Added in dynamicmultilist to allow for color changing on PC used to set Nuzlocke and extra settings.
- Added Carcinisation mode (Everything can now evolve into Krabby, Krabby in the wild, all NPCs have Krabby).
- EXP multiplier can now be changed as a setting.
- Holding R when it's turbo B no longer toggles running shoes.
- Low health beeping can be toggled off.
- Made getting Aurora Map receivable in Space Station.
- Turbo B will now always work except in the Slot Machine, Wall Clock, and Chat Rooms.
- Made wallclock default to 'Yes' when asking if the setting is correct.
- Made Lucky Egg triple EXP and a default PC item.
- Holding B makes surfing and diving faster.
- Added Eevee to Hoenn Pokédex
- [Push B in wild battle moves to Run](https://github.com/pret/pokeemerald/wiki/Push-B-in-wild-battle-moves-to-Run)

## v1.3.1
- Diving and reflection palette fix.
- Diving speed underwater same as running speed.
- [Changed Stop Learning request to Continue Learning.](https://github.com/pret/pokeemerald/wiki/Instead-of-Asking-to-Stop-learning-a-New-Move,-You'll-be-Asked-to-Continue-Learning)
- Made Eevee and its evolutions all have a 50% gender ratio.

## v1.3.0
- Added Leafeon, Glaceon, and Sylveon.
- All Eeveelutions can evolve into each other. They can evolve to Sylveon with Start Piece, back to Eevee with Everstone, and Glaceon with Never Melt Ice.
- Bug fix where overworld music cuts when the berry fanfare still plays when the player goes into their bag to plant a new berry.
- Bug fix where surfing in Slateport Harbor is no longer possible.
- Readded healing fanfare at Pokémon Center but cause overworld music to play over it once the Nurse Joy Message is closed.
- [Show Species That You're Battling in the Party Menu](https://github.com/pret/pokeemerald/wiki/Show-Species-That-You're-Switching-For-in-the-Party-Menu)
- [Trainers No Longer Spin to Face You Right As You Pass Them](https://github.com/pret/pokeemerald/wiki/Trainers-No-Longer-Spin-to-Face-You-Right-As-You-Pass-Them)
- [Shifting to Pokémon Already in Battle Exits the Shift Menu](https://github.com/pret/pokeemerald/wiki/Shifting-to-Pok%C3%A9mon-Already-in-Battle-Exits-the-Shift-Menu)
- [Get Rid of Pokemon Disobeying You](https://github.com/pret/pokeemerald/wiki/Get-Rid-of-Pokemon-Disobeying-You)
- [Pushing B When Asked To Stop Learning Move Will Cancel Teaching The Move](https://github.com/pret/pokeemerald/wiki/Pushing-B-When-Asked-To-Stop-Learning-Move-Will-Cancel-Teaching-The-Move)
- [Option to Skip Copyright and Intro. Able to toggle it on one of Prof. Birch's PCs.](https://github.com/pret/pokeemerald/wiki/Option-to-Skip-Copyright-and-Intro)
- [Button Press to Skip Copyright Screen](https://github.com/pret/pokeemerald/wiki/Button-Press-to-Skip-Copyright-Screen)
- [Allow Both Latios and Latias Appear](https://github.com/pret/pokeemerald/wiki/Allow-Both-Latios-and-Latias-Appear.)
- Jump Kick and High Jump Kick now has the effects of newer generations.
- Put more interesting Pokémon into the Safari Zone.
- Added Surkit, Masquerain, Meditite, Roselia, Zangoose, and Lunatone.
- Added ability to buy evolutionary stones and TMs from Mauville Game Corner in Lilycove Department Store.
- Ability to restart Nuzlocke challenge after failing by talking to Hiker in House in Rustboro City.
- Nuzlocke now counts in Safari Zone as well.
- Electrike and Manectric can now learn Flamethrower.
- Psyduck and Golduck can learn Fly.
- Zangoose can learn Cut.
- Made Raquaza's eye's pink-ish at the title screen.
- Sped up delay for messages about Intimidate and being buffered by weather conditions.
- Some overworld player sprite clean-up.
- [Grindrunning For Easier Diagonal Movement. Able to toggle it on one of Prof. Birch's PCs.](https://www.pokecommunity.com/showpost.php?p=10202986) [Credit: Pyredrid]

## v1.2.1
- Fixed bug that causes duplicates of caught Pokémon if they were nicknamed after being caught.
- Removed delay from leaving Pokémon Center by removing healing fanfare.
- Made Missingno smaller to match its height.
- Made dead Pokémon checking for the Nuzlocke challenge no longer occur during field poisoning and instead check and remove if needed when using a healing item.

## v1.2.0
- [Added Nuzlocke challenge setting.](https://github.com/pret/pokeemerald/wiki/Add-Nuzlocke-Challenge)
- [Pressing B as the ball shakes raises catching odds.](https://github.com/pret/pokeemerald/wiki/Raise-Odds-of-Catching-a-Pokemon-by-Pressing-B-When-the-Ball-Shakes)
- Final Elite Four battle is now a double battle with Steven and Wallace.
- Missingno. is now encounterable in the game after speaking to Wally's father and surfing in Pacifidlog Town.
- The Old Sea Map to get Mew is receivable under an old truck in the Lilycove harbor if the Nuzlocke challenge is on.
- [Jumping over ledges when bunny-hopping on the Acro Bike is now possible.](https://github.com/pret/pokeemerald/wiki/Allow-Jumping-Over-Ledges-with-Acro-Bike)
- [Can now quickly run from a battle by holding Right while the wild Pokémon's name appears.](https://github.com/pret/pokeemerald/wiki/Quickly-Run-from-a-Battle-by-Holding-Right-While-the-Wild-Pok%C3%A9mon's-Name-Appears)
- [Make Pokémon that Require a Fateful Encounter to be Legal to Always Be Set to Legal](https://github.com/pret/pokeemerald/wiki/Make-Pokemon-that-Require-a-Fateful-Encounter-to-be-Legal-to-Always-Be-Set-to-Legal)
- R is now Turbo B most of the time in the overworld and battles.
- Shedinja has a max HP of 50.
- Ponyta and Rapidash are now much faster.
- Pokémon have a 543,000 in 61,543,000 chance of getting infatuated by a Pokémon of the same gender.
- Bug fix on Show Battle Effectiveness in double battle.
- Death Move knocking out an opponent that can be permanently stolen will also remove them from the game.
- [Added ability to avoid damage in the debug menu.](https://github.com/pret/pokeemerald/wiki/Add-Ability-to-Avoid-Battle-Damage-in-Debug-Menu)
- [Surviving poison outside of battle with 1HP](https://www.pokecommunity.com/showpost.php?p=10068565&postcount=32) [Credit: Lunos]

## v1.1.0
- [Added Thief Ball](https://github.com/pret/pokeemerald/wiki/Add-Thief-Ball)
- [Added PC Access in PokéNav](https://github.com/pret/pokeemerald/wiki/Add-PC-Access-in-PokeNav)
- [Allowed All Pokémon to Evolve Without Trading](https://github.com/pret/pokeemerald/wiki/Allow-All-Pokemon-to-Evolve-Without-Trading)
- [Using HMs Without Any Pokémon in your Party Knowing Them Possible](https://github.com/pret/pokeemerald/wiki/Use-HMs-Without-Any-Pokemon-in-your-Party-Knowing-Them)
- [Changed Someone's PC to Lanette's PC from the Start of the Game](https://github.com/pret/pokeemerald/wiki/Change-Someone%27s-PC-to-Lanette%27s-PC-from-the-Start-of-the-Game)
- [Made Daycare Faster at Leveling Pokémon](https://github.com/pret/pokeemerald/wiki/Make-Daycare-Faster-at-Leveling-Pok%C3%A9mon)
- [Allowed Feebas to be caught on any Valid Fishing Spot in Route 119 if the Last Shot on the Basketball Hoop Went In](https://github.com/pret/pokeemerald/wiki/Allow-Feebas-to-be-caught-on-any-Valid-Fishing-Spot-in-Route-119-rather-than-only-Three)
- Added a Clock in Every PokéMart.
- [Norman's Slaking Has Ability Intimidate and can learn Death Move at level 100.](https://github.com/pret/pokeemerald/wiki/Make-Norman's-Slaking-Have-Ability-Intimidate)
- Charizard is fire/dragon, Meowth is normal/dark, Gyarados can learn fly
- Added Zen Headbutt, Moonblast, Play Rough, Draining Kiss, Fairy Wind, and Death Move.
- [Added Physical/Special Move Split](https://github.com/pret/pokeemerald/wiki/add-physical-special-split) [Credit: Kurausukun]
- [Physical Special Split Icons In Battle](https://www.pokecommunity.com/showpost.php?p=10527471) [Credit: Anon822]
- [Use Fly and Flash for Any Compatible Pokémon](https://www.pokecommunity.com/showpost.php?p=10420068) [Credit: ScyrousFX]
- [Added Fairy-Type](https://www.pokecommunity.com/showpost.php?p=10325868) [Credit: Lunos]
- [Not showing dex entries until getting the Pokédex](https://github.com/pret/pokeemerald/wiki/Not-showing-dex-entries-until-getting-the-Pok%C3%A9dex) [Credit: AsparagusEduardo]
- [Enable trade with FRLG Without Beating the Game](https://github.com/pret/pokeemerald/wiki/Enable-trade-with-FRLG-without-beating-the-game) [Credit: AsparagusEduardo]
- [Allow player to Change Direction Better While Moving](https://www.pokecommunity.com/showpost.php?p=10402610)  [Credit: cbt]
- [Made Move Pokémon as first PSS option](https://www.pokecommunity.com/showpost.php?p=10065761) [Credit: AsparagusEduardo]
- [Faster Berry Interactions](https://www.pokecommunity.com/showpost.php?p=10164065&postcount=82) [Credit: dunsparce9]
- [Changed Birch's Intro Pokémon to Blaziken](https://www.pokecommunity.com/showpost.php?p=9967857&postcount=6) [Credit: Avara]
- [Allowed Nicknaming in the Pokémon Party Screen](https://www.pokecommunity.com/showpost.php?p=10120389&postcount=45) [Credit: Lunos]

## v1.0.0
- Added graphics for Nick's front, back, intro scene, and overworld sprites
- Changed character's house to match Nick's
- Added secret base as garage (Secret Power TM is in PC and 2 straight boards are added as decorations when a new game is made)
- Added a basketball hoop
- Changed hometown name
- Added message on copyright screen
- Made 'Nick' be the default name to use if no name is set for a new character
- Add Jaime...kind of
- [Holding L is now turbo A](https://github.com/pret/pokeemerald/wiki/Make-L-Button-Be-Turbo-A-When-L=A-Option-Is-Set)
- [No battery run dry message appears](https://github.com/pret/pokeemerald/wiki/Get-Rid-of-Battery-Run-Dry-Error-Message)
- Party now gets healed after winning a gym badge (and when receiving your Pokédex completion diploma at the Lilycove Motel)
- [Turned off getting match calls from trainers who are not looking to battle.](https://github.com/pret/pokeemerald/wiki/Get-Match-Calls-Only-If-Caller-Wants-a-Rematch)
- [Intro now shows the biking trainer as the gender of the save file (defaults to male)](https://github.com/pret/pokeemerald/wiki/Make-the-Person-in-the-Intro-Match-the-the-Save-File)
- [Made Cleanse Tag turn the off all wild encounters and made it's held ability work if held by any Pokémon in the party](https://github.com/pret/pokeemerald/wiki/Make-Cleanse-Tag-Avoid-All-Wild-Encounters-and-Usable-If-Held-By-Anyone-in-Your-Party;-Make-PokeDoll-Do-the-Same-for-Trainers-Seeing-You#de-nerf-cleanse-tag)
- [Made Poké Doll cause no trainers to see you](https://github.com/pret/pokeemerald/wiki/Make-Cleanse-Tag-Avoid-All-Wild-Encounters-and-Usable-If-Held-By-Anyone-in-Your-Party;-Make-PokeDoll-Do-the-Same-for-Trainers-Seeing-You#pokedoll-to-avoid-battles). You can still go up and talk with them.
- Added Beldom in Meteor Falls and Mareep in Route 110
- [Added type color that shows battle effectiveness and added ability to toggle this feature in the option menu.](https://github.com/pret/pokeemerald/wiki/Show-Type-Effectiveness-In-Battle-Using-Pre-Existing--Function-and-Disable-in-Option-Menu)
  - Used [this](https://www.pokecommunity.com/showpost.php?p=10167016&postcount=83), but the vanilla code needed modification for it to work well.
- Toggle running
  - Created before finding [this](https://www.pokecommunity.com/showpost.php?p=10161076&postcount=72), but it had the same idea
- Made running indoors possible 
  - Created before finding [this](https://github.com/pret/pokeemerald/wiki/Allow-running-indoors), but it's the same idea
- Faster Pokémon Center healing
  - Created before finding [this](https://github.com/pret/pokeemerald/wiki/Speedy-Nurse-Joy), but same idea
- [Pushing R when looking at the clock allows for the time to be changed](https://www.pokecommunity.com/showpost.php?p=10481737) [Credit: paccy]
   - Tilemap for clock now includes mention of R to reset
- [Removing Badge Checks for HMs](https://www.pokecommunity.com/showpost.php?p=10036664) [Credit: wally-217]
- [White Out money calculation to match future gens and displays money lost amount](https://github.com/pret/pokeemerald/wiki/Better-White-Out-Money-Calculation) [Credit: Lunos]
- [Remove the extra save confirmation](https://github.com/pret/pokeemerald/wiki/Remove-the-extra-save-confirmation) [Credit: FieryMewtwo] 
- [Increase Text Speed Beyond Fast](https://www.pokecommunity.com/showpost.php?p=10400198) [Credit: ellabrella]
- [Return and Frustration show power in summary screen](https://www.pokecommunity.com/showpost.php?p=10575976&postcount=420) [Credit: Lunos]
- [Set L=A and fast scroll text as the default](https://www.pokecommunity.com/showpost.php?p=9967853&postcount=5) [Credit: Avara]
- [Prompt for reusing Repels](https://github.com/pret/pokeemerald/wiki/Prompt-for-reusing-Repels) [Credit: ExpoSeed]
- [Simplistic Battle Intro](https://www.pokecommunity.com/showpost.php?p=10473117) [Credit: SBird]
- [Added debug menu](https://www.pokecommunity.com/showpost.php?p=10220970&postcount=175) [Credit: TheXaman]
  - Turned off by default.
- [Faster HP Drain](https://github.com/pret/pokeemerald/wiki/Faster-HP-Drain) [Credit: SonikkuA-DatH]
- [Wrong Save File Error Message](https://www.pokecommunity.com/showpost.php?p=10449518) [Credit: Anon822]
- [Surfing Dismount Ground Effects](https://github.com/pret/pokeemerald/wiki/Surfing-Dismount-Ground-Effects) [Credit: ghoulslash]
- [Improving the WaitForVBlank function](https://github.com/pret/pokeemerald/wiki/Improving-the-WaitForVBlank-function)[Credit: DizzyEggg]
- [Lower case after first input in the naming screen](https://www.pokecommunity.com/showpost.php?p=10199896&postcount=139)[Credit: Jaizu]
- [Let a Pokémon forget any move they know](https://www.pokecommunity.com/showpost.php?p=10182839&postcount=119) [Credit: Lunos]
- Default Options are now fast text speed and L=A by default
  - Made before finding [this](https://www.pokecommunity.com/showpost.php?p=9967853&postcount=5), but same idea
- Removed small bugs with *#define BUGFIX* in *config.h*
