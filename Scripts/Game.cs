using Godot;
using System;
using System.Collections.Generic;

public partial class Game : Node3D
{
    Player player1;
    Player player2;

    // Called when the node enters the scene tree for the first time.
    public override void _Ready()
    {
        player1 = new Player("player1");
        player2 = new Player("player2");
        LORE.Game.AddPlayer(player1);
        LORE.Game.AddPlayer(player2);
        LORE.Game.Mulligan(player1, new List<byte>() { 1, 2, 3 });
        LORE.Game.Mulligan(player2, new List<byte>() { 1, 2, 3 });
        LORE.Game.Start();
        LORE.Game.PassTurn(player1);
    }

    // Called every frame. 'delta' is the elapsed time since the previous frame.
    public override void _Process(double delta)
    {
    }
}
