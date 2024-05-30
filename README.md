# ENGR-103---Video-Game
Cyclone video game created in ENGR 103 class on Circuit Playground Express board through Arduino

Description:
  My game will be based off the cyclone game where there is a particle that travels around in a circular pattern and the player must push the button to stop it at a certain position to advance to the harder stage. If the particle is stopped at the correct position, the lights will flash green, and the level will get harder. If the particle is stopped at the incorrect position, the lights will flash red, and the level will return to 1. Before each trial, the level will be displayed on the LEDs going in a clockwise direction, starting with the LED in position 9, or level 1.

Inputs/Outputs definitions:
  Inputs:
  o	Right button: This will be an interrupt attachment function to the right button that stops the particle at a certain position.
  o	Left button: This will be an interrupt attachment function to the left button that stops the particle at a certain position.
  o	Slide switch: This will be an interrupt attachment function that will turn off the game and clear LEDs if the switch is turned off. When the switch is 
    turned back on, the game will restart from the beginning.
  Outputs:
  o	LEDs: The LEDs will display the level in a singular pink LED in the coordinating position. They will then light up in a circular pattern in the color     
    white. When a button is pushed, the LED where the particle was will light up blue. If the position of the particle matches the goal, all the LEDs will 
    light up green, if it doesn’t, they will all light up red. If the player reaches the final stage and wins the game, the LEDs will sparkle green until the 
    switch is turned off.
  o	Speaker: The board will play a level tone when displaying the level before a stage. It will then play a ticking sound as the white LED travels along the 
    board. It will play a happy sound if the board lights up green and a sad sound if the board lights up red. If the player reaches the final stage and wins 
    the game, the speaker will play random notes until the switch is turned off.

Functions:
  Map: in this game, the map function is used to transmit the time it takes to turn on and off one of the white LEDs into a level from the scale 0 – 9 so that 
  the level will coordinate with the speed of the LEDs.
  o	Syntax: level = map(time, 10, 100, 0, 9);
