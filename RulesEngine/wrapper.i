%module wrapper

%include "stdint.i"
%include "std_string.i"
%include "std_vector.i"

%{
#include "GameWrapper.h"
%}

%include "GameWrapper.h"


// TODO: it would be nice for these to be in a namespace instead of having to prepend 'LORE_'
%rename(LORE_Card) Card;
%rename(LORE_Player) Player;
%rename(LORE_TurnAction) TurnAction;

%include "Card.h"
%include "Player.h"
%include "TurnAction.h"
