Changelog
=========

### 15 apr

Fixes for universal gravitation, now works pretty well
Fixed memory leak
Fixed seperate SFML views for GUI and the game entities

### 3 jan

Added drawgroup class
Fonts are now working and in use
Started working on mouse support within zoomed view
Changes in universal gravitation

### 16 dec

#### 09:40
Universal gravitation force is now applied in correct direction, although the force amount is a little messed up.
Preparation for dynamic mass of celestial objects
Now loads fonts for text


### 12 dec
Code for universal gravitation with CelestialObjects is much cleaner.
Almost functions as it should

### 8 dec

#### 13:45
Started working on universal gravitation.
Partitially works


### 6 dec

#### 19:28
Created a celestial object class.
Ship now accelerates instead.
Camera works better

### 5 dec

#### 23:40
Moved window initialization to graphics.h so it is globally accessible
Made a new circle in the game mode for reference
Started working on a camera
You can now move around in game with arrow keys
It now properly switches scene

#### 16:50
Changed the abstract Scene baseclass with other base functions.
Scenes are now accessible globally from the getScene and changeScene functions.
Added some options in the main function

### 4 dec
Initial commit, basic scene system as a base to later make seperate game and menu scenes.
