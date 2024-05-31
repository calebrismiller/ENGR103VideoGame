# ENGR103VideoGame
Cyclone video game created in ENGR 103
## A Short Description
  My game will be based off the cyclone game where there is a particle that travels around in a circular pattern and the player must push the button to stop it at a certain position to advance to the harder stage. If the particle is stopped at the correct position, the lights will flash green, and the level will get harder. If the particle is stopped at the incorrect position, the lights will flash red, and the level will return to 1. Before each trial, the level will be displayed on the LEDs going in a clockwise direction, starting with the LED in position 9, or level 1.
## Libraries
1. Adafruit Circuit Playground Library: This library must be included to use the LEDs, speaker, buttons, and switch and is necessary for this code.
   
2. Async Delay Library: This library establishes an interval that allows you to check certain threshold values throughout your code and set up an operation given the results of that.
## Inputs
1. Right button: This will be an interrupt attachment function to the right button that stops the particle at a certain position.

2. Left button: This will be an interrupt attachment function to the left button that stops the particle at a certain position.

3. Slide switch: This will be an interrupt attachment function that will turn off the game and clear LEDs if the switch is turned off. When the switch is turned back on, the game will restart from the beginning.
## Outputs
1. LEDs: The LEDs will display the level in a singular pink LED in the coordinating position. They will then light up in a circular pattern in the color white. When a button is pushed, the LED where the particle was will light up blue. If the position of the particle matches the goal, all the LEDs will light up green, if it doesn’t, they will all light up red. If the player reaches the final stage and wins the game, the LEDs will sparkle green until the switch is turned off.

2. Speaker: The board will play a level tone when displaying the level before a stage. It will then play a ticking sound as the white LED travels along the board. It will play a happy sound if the board lights up green and a sad sound if the board lights up red. If the player reaches the final stage and wins the game, the speaker will play random notes until the switch is turned off.
## Functions
1. Map: in this game, the map function is used to transmit the time it takes to turn on and off one of the white LEDs into a level from the scale 0 – 9 so that the level will coordinate with the speed of the LEDs.
- Syntax: level = map(time, 10, 100, 0, 9);

2. Generate MIDI: this function generates a MIDI pitch value that will be used throughout my code to generate sound from the speaker.
- Syntax: generateMIDI()
