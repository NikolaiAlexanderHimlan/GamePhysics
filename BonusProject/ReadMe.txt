Author: Nikolai Alexander-Himlan
Project: Bonus Project - Falling Spheres
Purpose: 

My engine code is stored under [nalexanderhim] in the libs folder, separate from the project directory.

GLUI: I have included the GLUI libs for both debug and release (labeled).

Controls:
 (currently, input does not support pressing more than one key at a time, as well as being slightly laggy due to GLUT)
//Camera
	- WASD standard FPS movement.
	- R/F will cause the camera to rise and fall on the y-axis
	- Arrow keys will rotate the pitch and yaw of the camera.

//Simulation
	- 'Home' will reset the simulation and camera view.
	- 'End' will pause the simulation.
	- 'Page Up'/'Page Down' will iterate the debug output through all the managed RigidBodies.

There is a GLUI window to the right when loading up the program which shows the position of the camera and the current target planet.  
There are GLUI Buttons to Reset the Camera, Reset the Simulation, step forward a single timestep in the simulation, and a checkbox to pause/unpause the simulation.

GitHub commit: 
	[will add after submission]

GitHub hash: 
	[will add after submission]

Blog link: 
	[video included]

