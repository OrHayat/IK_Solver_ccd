# IK_Solver
Kinematic Chain
IK Solver (CCD method) with OpenGL written with c++, project's solution is compiled with Visual Studio 2017.

Using the cube mesh to render a cube in (5,0,0) and chain of boxes on the z axis direction. Picking an object using a color picking implementation.

Mouse key callback:

• When left mouse button is pressed picked link is rotated around the previous link Z axis (the first link will rotate around the scene z axis) when the cursor slides left or right and rotate picked link around the current X axis when the cursor slides up or down. When nothing is picked the whole scene is rotated.

• When right mouse button is pressed translate destination cube or whole chain (according to picking) under the mouse cursor (always moves in the plane parallel to the screen plane).

• When scrolling up translate destination cube or whole chain (according to picking) away into the screen. When scrolling down picked object get closer.

Adding an axis system for each joint according to the previous link axis system Using the following key callback:

• 'space' – starts and stops IK solver(Using CCD method).

• 'right and left arrows' – rotates picked link around the previous link Z axis (the first link will rotate around the scene z axis). When nothing is picked rotate the whole scenespace is rotated.

• 'up and down arrows' – rotates picked link around the current X axis (use Euler angles). When nothing is picked rotate the whole scene.

Project contains different Textures on the links.
