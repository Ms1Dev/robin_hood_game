
This was a first year C++ project. It is a very simple side scroller where you have to get from one end of the map to the other and shoot enemy characters with arrows without getting hit by their arrows.

Again, very simple and pretty terrible graphics but the cool thing is the whole thing is rendered in the console! It uses coloured characters repeatedly printing to the console to produce a very low res video.

It works by printing rows of the "Upper half block" ▀ ascii character (0xDF) to produce the pixels for the image. As the rows are built before each upper block character has an escape code prepended to
it which controls the foreground and background colour of the character. Foreground will control the upper half of the character and the background will control the lower half. In this way each character controls
the colour of two pixels.

It is quite tempermental and only works on my Windows machine.

<div>
  <img src="https://github.com/Ms1Dev/robin_hood_game/blob/master/Screenshot%202024-05-28%20144320.png" alt="Character shooting arrow" height="250"/>
  <img src="https://github.com/Ms1Dev/robin_hood_game/blob/master/Screenshot%202024-05-28%20143629.png" alt="Character ducking to avoid arrow" height="250"/>
  <img src="https://github.com/Ms1Dev/robin_hood_game/blob/master/Screenshot%202024-05-28%20143647.png" alt="Player character and AI character" height="250"/>
  <img src="https://github.com/Ms1Dev/robin_hood_game/blob/master/Screenshot%202024-05-28%20143750.png" alt="Character walking" height="250"/>
</div>
