# 1D Space Invaders

## Overview


Aliens fall down in 2 different channels (right 5 LEDs and left 5 LEDs).

Pressing the right or left button will fire a missile up that channel. Pressing the right button will send a missile up the right 5 LEDs and ends there; no missile fired on one side can hit aliens on the other side.

5 points for every alien shot down, 1 point for every cycle survived. 1 cycle is 1 round of attemptied spawning aliens, as what side they spawn on as well as if they spawn at all is randomly determined each cycle.

Aliens progressively fly down faster and faster as time progresses in different phases from 0-4, as displayed in the serial output.

In short, aliens will fly down from 2 different directions, and you have to shoot them down with the 2 missile launchers pointed at them. You get points for time survived and number of aliens shot down.



## Inputs/Outputs


Right/Left Buttons: The main 2 inputs. Fire missiles up corresponding sides.

Slide switch: resets game after you die. Plays Xevious theme on reset.

LEDs: Green lights moving down (Aliens), white lights moving up (missiles). Aliens spawn at random, missiles triggered by aforementioned button presses. Lights only move along the 5 LEDs on each side, never cross over to the other side.

Serial: Outputs total score, current phase, and total aliens destroyed.


