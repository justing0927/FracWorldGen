/*
So a 10x10 sheet of squares makes up the currently displayed "Grid" - each square has its own display.
That Grid is sorta the view.
This is a sorta fractal project so a square is made up of other squares that form a grid.
So every square contains a list of 100 squares that make it up, forming another grid.
This has a total of three tiers: World, biome, and entity.
So every square of the world tier is made up of a 100 squares of the biome tier, each made up of 100 squares
of the entity tier.

Different things also interact at the world tier that influence the tiers below it, and vice versa.

A square itself thus always has:
	A symbol representing the defining characteristic of a square - e.g. A ^ for a mountain. 
		A world tier square, made up of mostly high elevation rock, is a mountain.
			It could theoretically be mined or destroyed to become a flat, or populated to become a Kingdom.
		These symbols obviously change by tier, mountains, hills, entities themselves.
		These symbols update as either entities interact with them, or their composite squares change.
	A location - their spot in a grid.
	A description of the square (its symbol).
Certain squares also have:
	A list of 100 squares that make it up (World and Biome tier)
	Food level
*/