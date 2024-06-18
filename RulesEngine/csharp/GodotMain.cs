using Godot;
using System;

public partial class GodotMain : Node
{
	public SWIGTYPE_p_void Game;

	public GodotMain(string playerName1, string playerName2)
	{
		Game = game.Game_Create(playerName1, playerName2);
	}

	public void PlayCard(string playerName, int cardIndex)
	{
		game.PlayCard(Game, playerName, cardIndex);
	}

	public void InkCard(string playerName, int cardIndex)
	{
		game.InkCard(Game, playerName, cardIndex);
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
