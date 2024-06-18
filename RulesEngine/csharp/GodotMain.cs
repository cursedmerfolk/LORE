using Godot;
using System;

public partial class GodotMain : Node
{
	public IntPtr Game;

	public string[] PlayerNames { get; set; }

	public GodotMain(string playerName1, string playerName2)
	{
		PlayerNames = new string[]{ playerName1, playerName2 };
		Wrapper.Game_Create(out Game, PlayerNames, PlayerNames.Length);
	}

	public void PlayCard(string playerName, int cardIndex)
	{
		Wrapper.PlayCard(Game, playerName, cardIndex);
	}

	public void InkCard(string playerName, int cardIndex)
	{
		Wrapper.InkCard(Game, playerName, cardIndex);
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
