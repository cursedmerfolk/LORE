using System;

public class Player
{
    public string Name;

    // The internal LORE::Player associated with this Player object in Godot.
    public LORE_Player lore_player;

	public Player(string name)
	{
		Name = name;
	}
}
