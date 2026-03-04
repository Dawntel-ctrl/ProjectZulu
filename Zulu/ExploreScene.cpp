#include "ExploreScene.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void ExploreScene::run(Game& game) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    GameState& state = game.getState();

    int machineAttempts = 0;
    int doorAttempts = 0;
    bool codeDiscovered = false;
    bool machineUnlocked = false;
    bool playerAlive = true;

    cout << "\nYou enter a sealed chamber.\n";
    cout << "Cold air hums through hidden vents.\n";
    cout << "A massive device pulses faintly in the center of the room.\n";

    while (playerAlive && !machineUnlocked) {
        game.printHUD();

        cout << "\n---------------------------------\n";
        cout << "1) Approach the machine\n";
        cout << "2) Inspect the surroundings\n";
        cout << "3) Try the door\n";
        cout << "Or type your own action:\n> ";

        string input;
        getline(cin, input);

        if (input == "1") input = "approach";
        if (input == "2") input = "inspect";
        if (input == "3") input = "door";

        //  MACHINE 
        if (input.find("approach") != string::npos ||
            input.find("machine") != string::npos) {

            machineAttempts++;

            if (!codeDiscovered) {
                cout << "\nThe device emits a violent pulse.\n";
                cout << "You are thrown backward.\n";

                game.modifyStability(-1);

                if (machineAttempts >= 3) {
                    cout << "\nThe machine overloads.\n";
                    cout << "Containment failure.\n";
                    playerAlive = false;
                }
            }
            else {
                cout << "\nA keypad flickers to life.\n";
                cout << "Enter 3-digit code: ";

                string code;
                getline(cin, code);

                if (code == "734") {
                    cout << "\nThe hum deepens.\n";
                    machineUnlocked = true;
                }
                else {
                    cout << "\nIncorrect code.\n";
                    game.modifyStability(-1);
                }
            }
        }

        //  INSPECT 
        else if (input.find("inspect") != string::npos ||
            input.find("look") != string::npos) {

            cout << "\nSteel plating lines the chamber.\n";
            cout << "Beneath torn sections lies curved stone.\n";
            cout << "\nOn the floor near a broken console:\n";
            cout << "III   -34\n";

            codeDiscovered = true;
        }

        // DOOR 
        else if (input.find("door") != string::npos ||
            input.find("leave") != string::npos) {

            doorAttempts++;

            if (doorAttempts == 1) {
                cout << "\nAccess denied.\n";
            }
            else if (doorAttempts == 2) {
                cout << "\nThe floor vibrates slightly.\n";
            }
            else {
                cout << "\nThe ground gives way.\n";
                cout << "You fall into darkness.\n";
                playerAlive = false;
            }
        }

        else {
            cout << "\nNothing happens.\n";
        }

        if (state.stability <= 0) {
            cout << "\nYou collapse as the chamber hum intensifies.\n";
            playerAlive = false;
        }
    }

    if (!playerAlive) {
        cout << "\nGAME OVER\n";
    }
    else {
        cout << "\nReality bends around you...\n";
        cout << "To be continued.\n";
        game.modifyInfluence(2);
    }
}