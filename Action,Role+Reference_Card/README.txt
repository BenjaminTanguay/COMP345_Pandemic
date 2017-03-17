ReferenceCard and  RoleCard I thought of as extending “Card”
ReferenceCard of more straightforward like “Deck” (it is simply a list -same for all players)
RoleCard is a bit like “EventCard” in the sense that It points to a more complex structure that could be used to perform actions without having to implement each action with checks in a driver.
The idea is each rolecard gives a set of rules and costs that can be verified before playing.
So we would have:{ if ( Player1.rolecardcheck() ) do: display_possibility_to_perform_role()}
This method could be more generic if each role has a class inheriting from RoleCard. The role cards Could also have a function that would take a player as an argument in order to pass on control to another player.
In this sense it is an action that can be played if conditions are met. Alternatively an Event card like structure can be given.
Instead of the player trying to figure out from the gamestate what possible moves are possible from get() functions for each action.

The action classes can give the actions a cost that can be associated to them directly instead of listing their costs in a driver. Also they could be added like the “eventCard” type.
