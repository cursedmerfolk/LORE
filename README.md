
# **L**\<redacted\> **O**pensource **R**ules **E**ngine

## Summary

This project aims to be an implementation of the rules for the \<redacted\> TCG. It should ideally be useable by as many target platforms and game engines as possible.

I'm flexible on ideas / programming languages / goals etc, feel free to throw around ideas.

The engine is currently written in C++ (at `RulesEngine/core/`) and uses SWIG to generate bindings for csharp and java (and other languages as desired).

This is currently a project that runs in Godot, but the RulesEngine library should be separated from Godot at some future point.

## Building / Development

 - Install vscode and docker (docker desktop on windows)
 - Clone the repo and open it in vscode.
 - Install the dev containers vscode extension.
 - Open the vscode command pallete (F1 on windows) and select 'Reopen in Container'
 - The container should open with everything needed to build the project.
 - `cd RulesEngine/core/` and run `make json_cpp` once, then `make windows` subsequently to build changes.

## Desired Features

 - Full rules implementation + tests.
 - Client and Server libraries.
 - Wrapper projects using various languages engines (javascript, java, etc).
 - Support for creators to write a rules engine as a plugin (for other games), to be used generically by the engine.


## Work Done

Not much unfortunately, just a basic UI and minimal implementation of basic rules.
