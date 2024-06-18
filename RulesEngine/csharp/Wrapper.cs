using System;
using System.Runtime.InteropServices;

class Wrapper
{
    // Import the Game_Create method
    [DllImport("RulesEngine/core/build/libLore.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Game_Create(out IntPtr game, [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.LPStr)] string[] playerNames, int playerCount);

    // Import the Game_Destroy method
    [DllImport("RulesEngine/core/build/libLore.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Game_Destroy(ref IntPtr game);

    // Import the PlayCard method
    [DllImport("RulesEngine/core/build/libLore.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void PlayCard(IntPtr game, string playerName, int cardIndex);

    // Import the InkCard method
    [DllImport("RulesEngine/core/build/libLore.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void InkCard(IntPtr game, string playerName, int cardIndex);

}
