#pragma once

/*
This is sort of an entity interface (or maybe the header file will be for an entity object)
Entities come in all shapes and sizes, but only truly exist on the entity tier.
Entities are "living" threads that act independently, can move, and interact with other entities.
A person is an entity
A hero is a type of person
A beast is an entity
a mouse is a type of beast
a giant mouse is a possible subset of mouse
A kingdom is an entity - one of the most advanced types
Hamlets, villages, towns, cities are all kingdoms.
They contain a military might, population, food, etc.
They too can move through their borders - shrinking and growing.
Entities have a savagery level (affected by global parameter) - Chance to kill another entity
Hunger level - A need for food - if it is lower than the Food level of the area, it can sustain itself.
If it is higher, than it needs to kill other entities for food or starve after a few cycles.
Reproduction level ? Something random to determine randomly dying out past
Kingdoms savagery is their military might, the added savagery of all of their heroes and some of their population.
That some of population is based on where they live (how harsh conditions are)
So a desert kingdom may have less food, making it harder to expand borders, but have a higher savagery
increasing the chance they win conflicts and beat out BEASTS
As well as the size of their borders. So the larger they are the less they can devote to a single square -
but the higher population they have total to use.
*/

enum eType { person, beast, kingdom };

class Entity
{
public:

	eType et;
	int savagery;
	int hunger;
	//reproduction ?

	Entity(eType t, int s, int h)
	{
		et = t;
		savagery = s;
		hunger = h;
	}
	
};