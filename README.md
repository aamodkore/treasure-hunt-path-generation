treasure-hunt-path-generation
=============================

Code used to generate the paths for each team in a Treasure Hunt. 

- Code was initially intended for the Mood Indigo 2011 - Treasure Hunt
- The edited code taking into account establishing equally difficult clue types for each team was used again for Mood Indigo 2012 - The Great Hunt.

=============================

[Visit the Mood Indigo website](http://www.moodi.org) to know more about what Mood Indigo is about recently.

=============================

Just so you know, it is basically a brute force algortihm, mindlesslessly implemented until a suitable configuration is obtained. 
The constraints are based on if a team has visited the clue, what is the load on the location at any time, and which clues have the team already solved. 
The objective was to spread out the load as evenly as possible across location, so that many teams do not clog to one location, while others remain unattended.
Also, different clue types are distributed as per difficulty so that each team gets equal number of clues of each type.
