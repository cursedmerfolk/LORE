%module Lore

%{
#include "GameWrapper.h"
%}

%include "GameWrapper.h"


// Rename the exposed Player and Card classes
%rename(LORE_Player) Player;
%rename(LORE_Card) Card;

// %include "TurnAction.h"
%include "Card.h"
%include "Player.h"
