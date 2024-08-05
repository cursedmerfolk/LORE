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
		player1.lore_player = LORE.Game.AddPlayer(player1, player1.Name);
		// player2.lore_player = LORE.Game.AddPlayer(player2, player2.Name);
		// List<object> mulligans = new List<object>
		// {
		// 	(Card)FindChild("PlayerHand").FindChild("Card1"),
		// 	(Card)FindChild("PlayerHand").FindChild("Card2"),
		// 	(Card)FindChild("PlayerHand").FindChild("Card3")
		// };
		// LORE.Game.Mulligan(player1, mulligans);
		// LORE.Game.Mulligan(player2, new List<object>());
		// LORE.Game.Start();
		// LORE.Game.PassTurn(player1);
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
	}
}
