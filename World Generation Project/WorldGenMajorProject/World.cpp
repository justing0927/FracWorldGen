/*
Given the parameters generates the random world, generating things in order.
	Gasses (savegery increases oxygen, inhabitable worlds have things lost, hotter worlds more greenhouse)
		All parameter based.
			Can change overtime w flora???
	Landmasses/Elevation (Valid configuration, may all be water dependent on configuration)
		Diamond-square algorithim
		Everything not above SEA_LEVEL is water.
			SEA_LEVEL is set to whatever fills in WATER_PERCENT parameter.
				E.G. 71% for earth-like elevations means SEA_LEVEL will be ~0.
	Weather (Based on elevation, gasses, and temperatures. Most advanced interactions here)
		First generates temperatures based on equator, water, and gasses (savagery, parameter, etc)
			Temperate zones
			Temperature of individual places
		Creates the "wind" thread that the world view will display. Warm air and cold air moving appropriately.
			Assuming same spin and axis as Earth - Advanced Parameter later??
		Generates a sort of precipitation based on gasses (acidic) and elevation
			LOTS of interaction here.
			Temperature and mountains can cause deserts vs temperate lands.
			Tornadoes on flatter lands held in by mountains in certain zones.
			High rainfall vs low rainfall
	Generates bodies of water - mostly Biome tier level. 
		Enough water makes a "sea" world tile
		Placing rivers in random configurations until it works seems like best option.??
*World tier is now a series of mountains, water, or flatlands*
	Generates "biomes"
		Temperature, water, and elevation selects an appropriate biome for world tier square. E.G. Desert
			Biome squares filled out from there. E.G. Dunes, Oasis, Valley, Kingdom.
				World square update check for defining feature.
					Should still be DESERT - most of the time, unless lots of water, or something.
				Entity squares randomly filled out based on likelyhood chart.
					E.G. In a DUNES, ~90% chance the tile is sand. Could also be den, sandstone, etc.
				
		Places entities.
			If Planet canSustainLife (Valid parameters (All green or yellow))
			//DEPENDS ON HOW ADVANCED INTERACTIONS WILL BE - Entitiese need to hunt? e
			(Based on gasses)
				Higher oxygen, from lush plant live, high savagery, or appropriate temperatures causes GIANTs
					Also makes higher elevations livable and lower not.
			(Based on biome)
				Different BEASTS for biomes.

				Kingdoms are randomly placed, and only heroes are independently tracked.
				
			

*/