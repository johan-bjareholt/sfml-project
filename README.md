spacesim-2d
============

A 2d planetatary simulator written in SFML.
Create multiple planets and watch them orbit around eachother.

An school project for the course DV1537 at Blekinge Institute of Technology

A more detailed changelog can be found in docs/changelog.md

#### Controls

- W: Throttle spaceship forward
- S: Throttle spaceship backward (should probably be removed)
- A: Rotate spaceship counter-clockwise
- D: Rotate spaceship clockwise

#### Todo

- Planet design
- Make spaceship able to land on planets
- Rethink drawgroups, preferably without drawables
- Fix so font isn't loaded once for every getFont()
- Move gravitational loop away from game.loop}\_logic

#### Screenshots

![Ship view](https://raw.githubusercontent.com/johan-bjareholt/spacesim-2d/master/screenshots/spacesim2d-1.png)
![Planetary view](https://raw.githubusercontent.com/johan-bjareholt/spacesim-2d/master/screenshots/spacesim2d-1.png)
