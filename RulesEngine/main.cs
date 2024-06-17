using Godot;
using Lorcana;
using System;
using System.Collections.Generic;

public partial class main : Node
{
	public Lorcana.Game Game { get; set; }

	public List<string> PlayerNames  { get; set; }

	public main(string playerName1, string playerName2)
	{
		PlayerNames = new List<string>{playerName1, playerName2};
		Game = new Lorcana.Game(PlayerNames);
		Game.Players["player1"].Hand.Add(new Lorcana.Card{});
		Game.Players["player1"].Hand.Add(new Lorcana.Card{});
		Game.Players["player1"].Hand.Add(new Lorcana.Card{});
	}

	public void PlayCard(string playerName, int cardIndex)
	{
		Lorcana.Player sourcePlayer = Game.Players[playerName];
		Lorcana.Card sourceCard = sourcePlayer.Hand[cardIndex];
		Lorcana.TurnAction turnAction = new Lorcana.TurnAction
		{
			type = Lorcana.TurnAction.Type.PlayCard,
			SourcePlayer = sourcePlayer,
			SourceCard = sourceCard,
		};
		Game.Perform(turnAction);
	}

	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
	}
}
