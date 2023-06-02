#pragma once

#include <string>

// ------------------------- Earth Character Info -------------------------
const std::string EarthCharacterInfo =
R"(Tierra Tarrencrest: An earth witch with high defense and can 
debuff enemy power and interrupt them.)";

const std::string EarthEffectInfo[2] =
{
	R"(Fortified: Unit with Fortified negate damage 
	from the next Spell (Max stack 3))",

	R"(Petrify: Spell of Unit with Petrify have 1 less 
	Will per stack, during this turn. (Minimum 1) (Max stack 3) )"
};

// ------------------------- Fire Character Info -------------------------
const std::string FireCharacterInfo =
R"(Helia Hino: A fire witch with that can deal a high burst damage 
and slowly burn damage.)";

const std::string FireEffectInfo[2] = 
{
	R"(Marking: Unit with mark take double damage 
	from the next spell during this turn.)",
	
	R"(Burning: Unit with Burning take 10 damage per stack 
	at the start of the turn. (Stack decrease by 1 after 
	take damage) )"
};

// ------------------------- Water Character Info -------------------------
const std::string WaterCharacterInfo =
R"(Seina Aquarone: A water witch, Gain mana faster and slow down 
the enemy cast time.)";

const std::string WaterEffectInfo[2] =
{
	R"(Overflow: Unit with Overflow gain 1 extra mana 
	per stack during this battle (Max stack 5))",

	R"(Freezing: Unit with Freezing use 1 more mana per 
	stack to decrease Cast Time, during this turn.
	(Max stack 3))"
};

// ------------------------- Wind Character Info -------------------------
const std::string WindCharacterInfo =
R"(Fumi Ventis: A wind witch, the more you compare the
will the more she become strong in the next turn.)";

const std::string WindEffectInfo[1] =
{
	R"(Boost: Gain stack(s) upon winning spell crash.
	At start of the turn gain buffs based on the stacks. 
	2+ stack: Reduce cost for decrease Cast Time this turn by 1 
	5+ stack: Reduce cost for increasing Will this turn  by 1
	8 stack: Increase all Spell Damage cast this turn by 10.
	Upon reaching 8 stack, during this turn no stack is gain
	and the stack is reset at the end of this turn.)"
};