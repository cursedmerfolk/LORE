using System;

public class Player : LORE.IPlayer
{
	public int test = 0;

	public Player(string name)
	{
		((LORE.IPlayer)this).SetName(name);
	}
}
