
# 2D Game Engine

### Game Engine created using C++. The repository also contains a game created using engine developed.

Following is the information around the structure of engine:

- The game engine makes use of 'Map' data structure, which has a unique id as a key, andd a smart pointer gameobject as value
- The game engine consists of a class named 'MyGameObject', which acts as a base class for all the gameobjects created in the project
- The engine makes use of smart pointers and weak pointers which are used to handle gameobject creation and destruction in a smart manner, to avoid any memory issues
- Game engine uses JSON to maintain information around different gameobjects and their properties
- The gameobjects are created using the JSON parser, where the file gets parsed from location
- The JobSystem is used to maintain the jobs in the game. Used for multithreading purposes
- Numerical integration used to make sure the game caculates the physics calculations accurately


## Documentation

The game engine uses a system of different components. Following are the components created in the engine.

1. Physics
- Physics component is based on a verlet integration formula
- Physics component has properties to be set for gameobjects such as mass, drag and force
- Responsible for handling the gameobject movement
- Moves the player and enemies when the force is applied on them
- Uses own map data structure called 'PhysicsRegistryMap' to store unique key as gameobject id and value as PhysicsComponent pointer
- PhysicsComponent class manages the registering of physics over any requested gameobject
- PS class manages the actual calculations for physics
- Uses update function to keep running physics on registered objects

2. Rendering
- Responsible for making the sprites render on game screen
- Uses GLib library to handle functions and operations related to rendering
- Releases the sprites when the rendering component ends and the shutdown is requested

3. Collision
- Collision component is managed via its own data structure called collisionMap, which uses a unique id as a key and a pointer to CollisionComponent class as value
- Collision component manages the AABB for each gameobject
- The collision component requires center and extent to be defined for the gameobject, on which the collision is supposed to be registered
- The collision is checked on each X and Y axes, for each gameobject
- The checks are taken into consideration with object1 in respect to space of object2 and vice versa
- The time for tOpen and tClose is calcuated and tracked for each checked
- Finds the latest tOpen and tClose during the current frame 
- Detects collision based upon the condition of tClose, if open before earliest tOpen


# Final game
- The final game makes use of all the components created while developing the game engine
- The objective of the game is to reach the goal position by avoiding the three monster as obstacles
- The game makes use of physics system to move the player and monsters in the game
- The player can be moved with 'W','S','A' and 'D' keys in up, down, left and right direction, respectively
- Touching the monster while playing results in failure state and the player has to restart the game again
- Reaching the goal by avoiding touching all three monsters results in win state
- The game makes extensive use of collision, physics, rendering, smart pointers, weak pointers, job system, matrix and every other small component in the engine to run and play the game successfully
- Enjoy the game!
