# FracWorldGen
Wold Generator Simulation

## Project Definition
A simulator built from scratch as a way to self-teach C++ and implement OpenGL.
The project is meant to fractally generate, and display realistic worlds given sets of different paremeters, and then simulate
the passage of time. 

## Heightmap
  Learned and implemented a diamond-square algorithim from scratch to randomly generate a fractal landscape.
  This creates mountains, valleys, canyons for a pseudo-realistic heightmap. 
  
## Atmosphere
  Using basic parameters, generates a world wide atmosphere for reference.
    E.g. One parameter may has slight effects on the oxygen level world-wide - which leads to more fires and the potential for
    larger organisms, as well as living at high levels, and 
  More advanced parameters work to determine temperature using greenhouse effect which can have effects on Entities. 
  
## Climate
  Generates a series of geographical zones and wind patterns.
  Learned how to implement markov chains, which are used to generate clouds, with their type and movement in real-time.
    Uses the steady state (extrapolated to near infinity) of that markov chain to determine averages for rainfall throught the world.
  Rainfall and temperate zone determine their biomes.
    E.g. A desert is created in more Torrid zones, determined by temperature, and where rainfall is nearly non-existent.
      Usually where clouds cannot move over that area due to mountain ranges. 
      
## Behind the Scenes
  The World exists as a 'grid' of 'squares.'
  - Each square has another grid of squares forming 'biomes.'
  - Each biome has a grid of squares that form the level where individual entities can interact.
  
  Biomes can be determined by the sum of their generated lower level grids - but usually are generated top down based on 
  temperature, rainfall, and a bit of randomness. 
  Entities can interact and theoretically change the biome they are in. Generated 'animal' populations moving, dying, thriving, and
  interacting with eachother. 
    E.G. Enough cattle existing without predators will strip squares of the grasses, moving on to others, and basically causing
      desertification. Usually though a predator will exist to cull the population, thriving for awhile off the abundant food,
      before falling into a balance, or dying out. 
      
## Todo
  'Events' can occur on any of these three levels. From Volcanoes to small fires.~
  There exist weather on both the world-wide and biome scales.
  Implementing realistic drainage of water to properly form realistic bodies of water.
  More realistic food-webs, interactions between entities.
  Implementing the Kingdom entity system to simulate human communities. 
