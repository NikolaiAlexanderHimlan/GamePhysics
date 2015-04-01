Author: Nikolai Alexander-Himlan
Project: MassAggregate Blob Game
Purpose: 

GLUI: I have included the GLUI libs for both debug and release (labeled), visual studio didn't like having a different name for the lib file.

Controls:
 (currently, input does not support pressing more than one key at a time, as well as being slightly laggy due to GLUT)
	- WASD standard FPS movement.
	- Arrow keys will rotate the pitch and yaw of the camera.
	- 'Home' will reset the simulation.
	- 'End' will pause the simulation
	- 'Page Up'/'Page Down' will iterate the debug output through all the managed particles.

There is a GLUI window to the right when loading up the program which shows the position of the camera and the current target planet.  While there is no debug information in the simulation, and thus no need to toggle debug info on and off, the functionality to do so is available by unchecking the "Debug Ctrl" checkboxes.

GitHub commit: 

GitHub hash: 

Blog link: 

