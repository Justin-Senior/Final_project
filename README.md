# 3GC3 Final Project
### Justin Senior and Nikhail Singh

This is an extension of a project which was completed during my university and I (Justin Senior) have updated since submission with fixes and updates to features.

## Running our Code:
To run our project simply use the make command to run the included makefile.
Uses OpenGL and the GLUT library version 3.0.0.


## Description:
Our final project randomly generates a 3D explorable environment using a Voronoi algorithm to specify a type of biome for each Voronoi Cell. Each biome hs its own types of vegetation, 
uses a different height map algorithm to create distinct looking terrain and textures for each type of surface in the biomes..

Our idea for this project is to create a simulation of an explorable 3D environment that we would procedurally generate. 
The application wouldn't be a full-fledged game as we would only be able to explore but would randomly generate an environment everytime it starts up and a user could then explore the said environment. Minecraft's biomes would be an example of something similar to what we are trying to make.

## Implementation details:

### Voronoi Algorithm
For the random generation, we decided to use Voronoi cells. Originally we planned on using the [edge flipping algorithm](https://www.cise.ufl.edu/~ungor/delaunay/delaunay/node5.html) to create delauney triangulations and then using those to create Voronoi cells.
After doing research on this and how the implementation worked we determined that we did not need to utilize all of the features of a fully fledged Voronoi library so we decided to implement a simplified algorithm that only did what we needed to do.

Our version of the algorithm works:
1. randomly picking a set of points on the plane, our Voronoi points and assign them a biome. 
2. for every other point it determines which Voronoi point it is closest to and assigns that point the same biome as its Voronoi point.
3. run different heightmap algorithms depending on the biome type.

### HeightMap Algorithms:
1. Circles - used for hills and forests.
2. FaultLine - used for the rocky mountain biomes.

### Vegetation
1. Trees which appear in forests
2. seaweed which appear underwater
3. ferns which appear in all biomes
4. bushes which are appear in deserts and on mountains.

## Features
Our project implements the following features:
1. Randomly generated terrain using voronoi cells.
2. A  simple camera that enables you to move around and will move up and down based on the height of the terrain. <strong> Known issue </strong> is that it will crash if you get too close to the edges of the map.
2. Four biomes: forests, mountains, deserts, and water. 
3. A minimap that displays an overhead of the entire map (After getting a new PC this feature is not working, still working on a fix)
4. Vegetation for biomes
5. Textures for every surface

## References
1. **[LearnOpenGL Textures](https://learnopengl.com/Getting-started/Textures)**
2. **[Image data loader by Sean Barret](https://github.com/nothings/stb)**
