#pragma once

#include "Player.h"


namespace Redacted
{


//TODO: delete these
    // char abilityName[32];
    // int8_t singers[16];
    // int8_t mulligans[8];
    // uint8_t sourcePlayerIndex;
    // uint8_t sourceCardIndex;
    // uint8_t targetPlayerIndex;
    // uint8_t targetCardIndex;
    // uint8_t shiftTargetIndex;
    // Type type;
    // bool succeeded{true};

    // uint8_t* toBytes()
    // {
    //     return reinterpret_cast<uint8_t*>(this);
    // }

    // static TurnAction* fromBytes(uint8_t* bytes)
    // {
    //     return reinterpret_cast<TurnAction*>(bytes);
    // }


struct TurnAction
{
public:
    enum Type
    {
        // Before game
        AddPlayer,
        StartGame,
        // During game
        ChallengeCard,
        InkCard,
        MoveToLocation,
        Mulligan,
        PassTurn,
        PlayCard,
        QuestCard,
        UseAbility,
    };

    TurnAction() = default;
    ~TurnAction() = default;
    TurnAction(const TurnAction& other) = default;

    TurnAction(Type type_) : type(type_) {};

    // Pointers feel wrong, not sure how to fix.
    Type type;
    bool succeeded;
    Player* sourcePlayer;
    Card* sourceCard;
    Player* targetPlayer;
    Card* targetCard;
    std::vector<Card>* singers;
    std::string* abilityName;
    std::vector<uint8_t>* mulligans;
    Card* shiftTarget;
    uint8_t targetIndex;           // Index in the target zone being moved to.

    std::string getTypeString()
    {
        if (type == Type::ChallengeCard) return "ChallengeCard";
        if (type == Type::InkCard) return "InkCard";
        if (type == Type::Mulligan) return "Mulligan";
        if (type == Type::PassTurn) return "PassTurn";
        if (type == Type::PlayCard) return "PlayCard";
        if (type == Type::QuestCard) return "QuestCard";
        if (type == Type::UseAbility) return "UseAbility";
        return "Unknown";
    }

};
// #pragma pack(pop)

}  // namespace Redacted
