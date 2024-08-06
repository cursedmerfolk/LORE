%module LORE_Wrapper

%include "stdint.i"
%include "std_string.i"
%include "std_vector.i"

%{
#include "GameWrapper.h"
%}

%include "GameWrapper.h"

// Rename the classes
%rename(LORE_Card) Card;
%rename(LORE_Player) Player;
%rename(LORE_TurnAction) TurnAction;

// This tells SWIG to help convert these types to a native enumerable type.
%template(LORE_ByteVector) std::vector<uint8_t>;
%template(LORE_CardVector) std::vector<Redacted::Card>;

%include "Card.h"
%include "Player.h"
%include "TurnAction.h"
