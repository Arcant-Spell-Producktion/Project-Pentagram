#pragma once

#include <string>

// ------------------------- Earth Character Info -------------------------
const std::string EarthCharacterInfo =
R"(Tierra Tarrencrest: An earth witch with high
defense and can debuff enemy power and interrupt
them.)";

const std::string EarthEffectInfo[2] =
{
	R"(Fortified: When a unit with fortified effect take
	damage from spell, turn it to 0 and decrease 1 stack.)",

	R"(Pertify: Unit that suffer from pertify will have 1
	less will for each spell.(can't go below 1))"
};

// ------------------------- Fire Character Info -------------------------
const std::string FireCharacterInfo =
R"(Helia Hino: A fire witch with that can deal a high
burst damage and slowly burn damage.)";

const std::string FireEffectInfo[2] = 
{
	R"(Marking: When a unit with mark effect take
	damage from spell, Double it.)",
	
	R"(Burning: Unit with burning will take 10 damage per
	stack at the start of the turn.(Stack decrease by 1
	after take damage))"
};

// ------------------------- Water Character Info -------------------------
const std::string WaterCharacterInfo =
R"(Water Witch: A water witch, Gain mana faster and
slow down the enemy cast time.)";

const std::string WaterEffectInfo[2] =
{
	R"(Overflow: Gain an extra mana during the battle.
	(Maximum at 5))",

	R"(Freezing: Unit that suffer from Freezing will use 1
	more mana to adjust cast time.(this effect is stackable))"
};

// ------------------------- Wind Character Info -------------------------
const std::string WindCharacterInfo =
R"(Wind Witch: A wind witch, the more you compare the
will the more she become strong in the next turn.)";

const std::string WindEffectInfo[1] =
{
	R"(Boost: When a spell wins in a WillCompare sequence
	gain a stack. On next turn base gain a buff based on
	how many stacks you have.)"
};