Author: Nikolai Alexander-Himlan
Project: RigidBody RubeGoldberg
Purpose: Demonstrate implementation of RigidBody physics system, including Velocity and Rotation resolution and contact generation and resolution.

My engine code is stored under [nalexanderhim] in the libs folder, separate from the project directory.

GLUI: I have included the GLUI libs for both debug and release (labeled).

NOTE: I appologize for being unable to refactor main in order to remove all the global data.

Controls:
 (currently, input does not support pressing more than one key at a time, as well as being slightly laggy due to GLUT)
//Camera
	- WASD standard FPS movement.
	- R/F will cause the camera to rise and fall on the y-axis
	- Arrow keys will rotate the pitch and yaw of the camera.

//Simulation
	- 'Home' will reset the simulation.
	- 'End' will pause the simulation
	- 'Page Up'/'Page Down' will iterate the debug output through all the managed RigidBodies.

//Object Controls//NOTE: It is named "Falling Cube" in the debug output.
	- J/L will move "model2" along the x-axis
	- U/O will move "model2" along the y-axis
	- I/K will move "model2" along the z-axis

There is a GLUI window to the right when loading up the program which shows the position of the camera and the current target planet.  While there is no debug information in the simulation, and thus no need to toggle debug info on and off, the functionality to do so is available by unchecking the "Debug Ctrl" checkboxes.

GitHub commit: 
	[will add after submission]

GitHub hash: 
	[will add after submission]

Blog link: 
	[video included]

