#pragma once

// Forward declaration so we can reference Game
class Game;

/*
    Scene is an abstract base class.
    Any specific scene (Explore, Fortify, Expand)
    must inherit from this and implement run().
*/
class Scene {
public:

    // Virtual destructor ensures proper cleanup
    // when deleting derived scenes polymorphically.
    virtual ~Scene() {}

    /*
        run(Game& game)

        - Takes the main Game object by reference.
        - Allows the scene to modify game state
          (resources, stability, influence, etc.)
        - Must be implemented by every derived scene.
    */
    virtual void run(Game& game) = 0;
};
