using Godot;
using System;

public partial class Game : Node3D
{
	Player player1;
	Player player2;
	
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		LORE.Game.Mulligan();
		LORE.Game.Start();
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
	}
}
