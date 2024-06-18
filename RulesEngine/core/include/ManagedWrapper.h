// ManagedWrapper.h
#pragma once

#using <mscorlib.dll>
#include "Game.h"
#include <vcclr.h>

using namespace System;
using namespace System::Collections::Generic;

namespace LorcanaCLI {

    public ref class ManagedWrapper {
    private:
        gcroot<Lorcana::Game*> game;

    public:
        ManagedWrapper(List<String^>^ playerNames) {
            std::vector<std::string> nativePlayerNames;
            for each (String ^ name in playerNames) {
                nativePlayerNames.push_back(msclr::interop::marshal_as<std::string>(name));
            }
            game = new Lorcana::Game(nativePlayerNames);
        }

        ~ManagedWrapper() {
            this->!ManagedWrapper();
        }

        !ManagedWrapper() {
            delete game;
        }

        bool Perform(TurnAction^ turnAction) {
            // Convert managed TurnAction to native TurnAction and call the native method
            // (Implement the conversion here)
            return game->Perform(nullptr); // Placeholder
        }
    };

    // Define managed versions of Player, Card, and TurnAction classes
    public ref class TurnAction {
    public:
        // Define properties and methods for TurnAction
    };

    public ref class Player {
    public:
        // Define properties and methods for Player
    };

    public ref class Card {
    public:
        // Define properties and methods for Card
    };
}
