#pragma once

#include <string>
#include <memory>          // Required for std::unique_ptr
#include "Scene.h"         // Base class for all scenes (polymorphism)
#include "GameState.h"     // Handles overall game state (MainMenu)
#include "RuleEngine.h"    // Applies dynamic rules to the game
#include "BehaviorAnalyzer.h" // Tracks player behavior patterns
#include "UI.h"            // Handles menu rendering and input

/*
    Game is the core controller of the engine.

    Responsibilities:
    - Maintains world stats (resources, stability, influence)
    - Controls turn progression
    - Coordinates RuleEngine and BehaviorAnalyzer
    - Switches between Scenes polymorphically
*/
class Game {
private:

    /*
        Current overall state of the game.
        Example: MainMenu, ExploreScene, GameOver
    */
    GameState state;

    /*
        RuleEngine dynamically modifies the game
        (example: decay rule, instability rule,//// find more)
    */
    RuleEngine ruleEngine;

    /*
        BehaviorAnalyzer tracks repeated patterns
        and may trigger mutations.
    */
    BehaviorAnalyzer behaviorAnalyzer;

    /*
        UI handles displaying menus and
        collecting user input.
    */
    UI ui;

    /*
        Controls main game loop.
        When false ..game exits.
    */
    bool isRunning;

    /*
        Prevents multiple mutation triggers
        from firing repeatedly.
    */
    bool mutationTriggered;

    /*
        Handles one full turn of gameplay.
        Typically:
         Show stats
         Get player choice
         Process scene
         Apply rules
    */
    void processTurn();

    /*
        Interprets player's text/choice input
        and determines which scene to activate.
    */
    void handlePlayerChoice(const std::string& choice);

    /*
        Uses BehaviorAnalyzer to check if
        player patterns should trigger new rules.
    */
    void checkForMutations(const std::string& choice);

    /*
        Determines if game ending conditions are met.
        Example:
        stability <= 0
         resources <= 0
    */
    bool checkGameOver() const;

    /*
        Core world statistics.
        These are modified by scenes and rules.
    */
    int resources;
    int stability;
    int influence;
    int turn;

    /*
        Polymorphic Scene pointer.

        This allows dynamic switching between:
        ExploreScene
         FortifyScene
         ExpandScene

        Stored as unique_ptr for automatic memory management.
    */
    std::unique_ptr<Scene> currentScene;

public:

    void printHUD() const;
    /*
        Provides controlled access to the internal GameState.

        Scenes use this to modify resources, stability, etc.
    */
    GameState& getState();
    /*
        Constructor initializes game state,
        starting resources, and systems.
    */
    Game();

    /*
        Main loop controller.
        Keeps game running until isRunning becomes false.
    */
    void run();

    // These will be needed by Scenes

    // Getters allow scenes to safely read stats
    int getResources() const;
    int getStability() const;
    int getInfluence() const;

    // Modifiers allow scenes to safely modify stats
    void modifyResources(int amount);
    void modifyStability(int amount);
    void modifyInfluence(int amount);

    // Advances turn counter
    void nextTurn();
};