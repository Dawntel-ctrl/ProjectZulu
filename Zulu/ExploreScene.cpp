#include "ExploreScene.h"
#include "ActionKnowledge.h"
#include "Game.h"
#include <iostream>
#include <string>

void ExploreScene::run(Game& game) {
    GameState& state = game.getState();

    int machineAttempts = 0;
    int doorAttempts = 0;
    int failedInputs = 0;
    bool codeDiscovered = false;
    bool consoleExamined = false;
    bool ventDiscovered = false;
    bool machineUnlocked = false;
    bool heardPattern = false;
    bool keypadRevealed = false;
    bool floorDefiled = false;
    bool playerAlive = true;

    std::cout << "\nYou enter a sealed chamber.\n";
    std::cout << "Cold air hums through hidden vents.\n";
    std::cout << "A massive device pulses faintly in the center of the room.\n";
    std::cout << "A broken console slumps near the wall, and the only visible door is sealed shut.\n";

    while (playerAlive && !machineUnlocked) {
        game.printHUD();

        std::cout << "\n---------------------------------\n";
        std::cout << "Try anything that makes sense.\n";
        std::cout << "Ideas: inspect room, examine console, approach machine, listen, try door, check vents, help\n> ";

        std::string input;
        std::getline(std::cin, input);
        input = ActionKnowledge::normalize(input);

        if (input.empty()) {
            std::cout << "\nSilence. Even standing still feels dangerous here.\n";
            failedInputs++;
            continue;
        }

        if (input == "1") input = "approach machine";
        if (input == "2") input = "inspect room";
        if (input == "3") input = "try door";

        // The parser gives us a rough read on intent.
        // The scene still decides what that means in this room.
        ActionIntent intent = ActionKnowledge::detectIntent(input);

        if (intent == ActionIntent::Help) {
            std::cout << "\nThe chamber gives you a few obvious leads:\n";
            std::cout << "- The machine in the center is active.\n";
            std::cout << "- The broken console looks important.\n";
            std::cout << "- The sealed door keeps reacting.\n";
            std::cout << "- The vents are the source of the low hum.\n";

            if (!consoleExamined) {
                std::cout << "\nIf you're stuck, start by examining the room or the console closely.\n";
            }
            else if (!heardPattern) {
                std::cout << "\nYou have symbols from the console already. Maybe something in the room can help translate them.\n";
            }
            else if (!keypadRevealed) {
                std::cout << "\nYou have enough to risk the machine again.\n";
            }
            else {
                std::cout << "\nThe keypad is exposed. The clue points to a 3-digit code.\n";
            }

            continue;
        }

        if (intent == ActionIntent::Inspect) {
            std::cout << "\nSteel plating lines the chamber.\n";
            std::cout << "Beneath torn sections lies curved stone older than the facility around it.\n";
            std::cout << "Dust gathers near a broken console, and scrape marks point toward the central machine.\n";

            if (!ventDiscovered) {
                std::cout << "Above you, the vents pulse with the same rhythm as the machine.\n";
                ventDiscovered = true;
            }

            if (!consoleExamined) {
                std::cout << "\nThe console is the only object here that looks like it once controlled something.\n";
            }

            failedInputs = 0;
        }

        else if (intent == ActionIntent::Console) {
            consoleExamined = true;
            std::cout << "\nThe console casing is split open.\n";
            std::cout << "Most of the display is dead, but one line still glows through the static:\n";
            std::cout << "III   -34\n";
            std::cout << "\nIt feels like part of a code, but not enough by itself.\n";
            codeDiscovered = true;
            failedInputs = 0;
        }

        else if (intent == ActionIntent::Listen) {
            heardPattern = true;
            std::cout << "\nYou hold your breath and listen.\n";
            std::cout << "The vents pulse in three sharp bursts, then a pause, then four, then a final pattern that feels cut short.\n";
            std::cout << "The machine and vents are synchronized.\n";

            if (codeDiscovered) {
                std::cout << "Paired with the console fragment, the pattern starts to suggest a 3-digit access code.\n";
            }
            else {
                std::cout << "Whatever the sound means, the broken console might help decode it.\n";
            }

            failedInputs = 0;
        }

        else if (intent == ActionIntent::Machine) {
            machineAttempts++;

            // Touching the machine early is allowed, but it should hurt
            // and push the player back toward the clue path.
            if (!(codeDiscovered && heardPattern)) {
                std::cout << "\nThe device emits a violent pulse.\n";
                std::cout << "You are thrown backward.\n";

                game.modifyStability(-1);
                keypadRevealed = false;

                if (machineAttempts >= 3) {
                    std::cout << "\nThe machine overloads.\n";
                    std::cout << "Containment failure.\n";
                    playerAlive = false;
                }
                else if (!consoleExamined) {
                    std::cout << "You need more information before forcing this thing again. The console is the best lead.\n";
                }
                else if (!heardPattern) {
                    std::cout << "The console gave you symbols, but you're still missing part of the sequence. Listen to the room.\n";
                }
            }
            else {
                keypadRevealed = true;
                std::cout << "\nA keypad flickers to life.\n";
                std::cout << "Enter 3-digit code: ";

                std::string code;
                std::getline(std::cin, code);
                code = ActionKnowledge::normalize(code);

                if (code == "734") {
                    std::cout << "\nThe hum deepens.\n";
                    machineUnlocked = true;
                }
                else {
                    std::cout << "\nIncorrect code.\n";
                    game.modifyStability(-1);
                    std::cout << "The clue seems to combine the vent rhythm with the console fragment.\n";
                }
            }
            failedInputs = 0;
        }

        else if (intent == ActionIntent::Door) {

            doorAttempts++;

            if (doorAttempts == 1) {
                std::cout << "\nAccess denied.\n";
                std::cout << "A dead panel beside the frame flashes once, then points a thin line of light back toward the chamber.\n";
            }
            else if (doorAttempts == 2) {
                std::cout << "\nThe floor vibrates slightly.\n";
                std::cout << "The response feels less like a lock and more like the room waiting for the machine to change state.\n";
            }
            else {
                std::cout << "\nThe ground gives way.\n";
                std::cout << "You fall into darkness.\n";
                playerAlive = false;
            }

            failedInputs = 0;
        }

        else if (intent == ActionIntent::BodyFunction) {
            failedInputs = 0;

            // Weird actions should still teach the player something.
            if (!floorDefiled) {
                floorDefiled = true;
                std::cout << "\nYou commit to an extremely bad decision.\n";
                std::cout << "The waste hits the metal floor and immediately hisses.\n";
                std::cout << "Thin channels etched into the plating flare for a second, carrying the residue toward the broken console.\n";
                std::cout << "For one brief moment, the chamber makes its priorities very clear.\n";

                if (!consoleExamined) {
                    std::cout << "If the room reacts that strongly, the console is probably tied into whatever system still lives here.\n";
                }
                else {
                    std::cout << "The chamber still routes everything toward the console. That cannot be random.\n";
                }
            }
            else {
                std::cout << "\nThe chamber vents release a sterilizing burst.\n";
                std::cout << "Your eyes water as the floor is scrubbed spotless and your stability takes a hit.\n";
                game.modifyStability(-1);
            }
        }

        else if (intent == ActionIntent::Vocalize) {
            heardPattern = true;
            failedInputs = 0;
            std::cout << "\nYour voice bounces off the chamber walls and comes back warped.\n";
            std::cout << "The echo catches on the vent rhythm, splitting into distinct beats: seven, then three, then four.\n";
            std::cout << "The room practically sings the pattern back at you.\n";

            if (!codeDiscovered) {
                std::cout << "You still need something to anchor those numbers. The console might do it.\n";
            }
        }

        else if (intent == ActionIntent::Aggressive) {
            failedInputs = 0;
            std::cout << "\nYou lash out at the chamber.\n";
            std::cout << "The impact answers with a shock through the floor, reminding you that brute force is not the winning language here.\n";
            game.modifyStability(-1);

            if (!consoleExamined) {
                std::cout << "If force won't work, information probably will. The console still looks like the best lead.\n";
            }
        }

        else if (intent == ActionIntent::Wait) {
            failedInputs = 0;
            std::cout << "\nYou go still and let the room reveal itself.\n";
            std::cout << "Once you stop fighting the chamber, its rhythms become easier to read.\n";

            if (!heardPattern) {
                heardPattern = true;
                std::cout << "The vents resolve into a countable sequence beneath the machine's hum.\n";
            }
            else if (!consoleExamined) {
                std::cout << "Your eyes keep drifting back to the dead console. Something there still matters.\n";
            }
            else {
                std::cout << "You've already gathered the pieces. The machine is waiting for you to act on them.\n";
            }
        }

        else {
            failedInputs++;
            std::cout << "\nThe chamber reacts, but not in a way you fully understand.\n";

            if (failedInputs == 1) {
                std::cout << "It helps to anchor your action to something physical: the machine, the console, the vents, the floor, or the door.\n";
            }
            else {
                std::cout << "Even strange actions can teach you something here, but `help` can point you toward the next useful lead.\n";
            }
        }

        if (state.stability <= 0) {
            std::cout << "\nYou collapse as the chamber hum intensifies.\n";
            playerAlive = false;
        }
    }

    if (!playerAlive) {
        std::cout << "\nGAME OVER\n";
    }
    else {
        std::cout << "\nReality bends around you...\n";
        std::cout << "To be continued.\n";
        game.modifyInfluence(2);
    }
}
