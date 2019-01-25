# Jax-Kal Companion App

The game “Project Jax” is a multiplayer side scrolling platformer which we are building on a C++ 3D rendering engine with a 2D point of view. There is a wide story behind this platformer. We are creating a companion app for Project Jax which will be a comic book app of the game. After creating the app, we are planning to release 1 page every week.

The networking components are as follows;
Number of players: Version1 -> 2 Players, Version2-> 4 players.
Players we cooperate to achieve the goal of the level. If a player chooses single player, then that player can switch between characters anytime. If the player wants so switch between characters while in a multiplayer game, it sends a request to the other client. If he/she accepts, they switch characters with all the statuses that the characters have.All position, status and animations will be replicated to other client as well as environmental effects like position and stateof the enemies and pickup-able objects.

