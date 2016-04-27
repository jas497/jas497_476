# Final 476 project for jas497, James Starkman

(note to self: view prettified version with [this](http://dillinger.io/))

The goal of this 476 project is to explain, in no uncertain terms, how
a Gazebo (GZ) plugin (GZP) is written.  It is meant to be suitable for
reading by future /[34]76/ [^regex] students (and the professor), with
the goal of writing their own plugins.

Regarding the development environment, the Atlas machines already have
everything that is needed installed.  Compiling GZPs can work
differently than compiling regular ROS nodes (straight call to `cmake`
instead of `catkin_make`), although for purposes of this project we
will compile it in the usual ROS way.  Note that GZPs are libraries
(`libfoo.so` files), not direct executables.

The primary example that will be used by this plugin is that of
writing a gripper [^gripper].  All code, XML files, buildscripts,
etc. are well-commented, to aid understanding.  For details, see the
last section of this read-me file.  Running the example is simple:

```
$ roslaunch jas497_476 test.launch
```

Stylistic note: GZ uses CamelCase for its APIs.  To avoid confusion,
either mimic this or settle on another style; try not to mix.  More
generally, this applies to all software engineering, not just writing
GZP.  Here, examples will use camelCase.

---------------------------------------------------------------------

# Writing a Gazebo plugin

A GZP is a C++ library file that the main GZ server loads and
executes.  It has pre-defined callback functions that happen at
predefined points in the program flow, similar to many other
frameworks, including Windows drivers/applications, Android apps,
Emacs function hooks, /(Node)?JS/ [^regex], and more.  Familiarity
with any of these will give you a basic idea of what API calls you can
expect to be available.

The first step is to decide what type of plugin is desired.  As of
this writing (April 2016), there are six types of plugin: World,
Model, Sensor, System, Visual, and GUI.  The reference plugin will
focus on Model plugins, but the concepts generalize.  The reader is
assumed to be familiar with C++ and using a plain-text editor such as
Emacs, GEdit, or Sublime Text (not an IDE like CLion or Eclipse; their
workflows are different, and have too much magic.  When learning
something for the first time, it is better to do it the hard way
first, then allow automated tools to simplify things).

## Brief overview of computer simulation

The way that a simulator works is to divide time (which is continuous)
into segments (which are discrete) and evaluate a series of *update
equations* at each time step.  These equations are not necessarily
linear or time-independent, two common mathematical conveniences
usually assumed in analytical engineering.  The size of the time step
is not necessarily uniform, although making it so simplifies
implementation.  These equations modify *state*.  Physically, we model
the state of a given particle's position as six parameters, XYZ and
their corresponding velocities.  Things that are not particles (such
as rigid bodies) also have orientation, which is more state to keep
track of.

The update equations can be anything.  In a physics simulator like GZ,
they are usually ordinary differential equations such as what one
learned in introductory physics/dynamics.

To detect collisions, since the update equations could indeed be
anything, the only way guaranteed to work is to wait until one object
intersects another.  Attempting to predict the collision (e.g.,
declaring that it has happened when one object is within a certain
boundary of another) does not work because the update equations could
suddenly cause the object to reverse course.  Regarding the problem of
determining when two objects have intersected, a common solution is to
make each define a *collision box* (or series of collision boxes, or
cylinders, or other geometric primitives) ![img_collide], since
checking whether two planes (or a plane and a circle, etc.) intersect
is elementary geometry.  A more computationally-intensive approach is
to check the entirety of a mesh, but that usually is not worth the
cost.

[img_collide]: images/collision_box.png "Example: grey tote in Gazebo.
Orange planes are the collision box, while the visual of the tote is
the mesh.  Notice how they are similar, but not the same, and think
about why the tradeoff was made."

This is also why a small time step is needed: with a large one, an
object might pass through a thin wall if its velocity is high enough
and the wall thin enough, since in one step it would be on one side of
the partition and the next, the other.  Of course, an adaptive time
step could attempt to solve this, but those tend to be complicated and
force one to decide which tradeoffs are acceptable and which are not.

Given that the two objects are in collision, we can then move them
both back a bit, to make them stop being in collision, and then handle
the collision.

## Implementing the above with Gazebo

GZ handles most of the above for you.  As of this writing, it has four
different physics engines (different ways to think about the above
problems), all with different implementations and optimization
criteria.  The default engine is named "ODE", the Open Dynamics
Engine.  It is good at cluttered scenes, while engines such as DART
are better at long joint chains (such as for humanoid robots).
Regarding accuracy, all are about the same, although Bullet tends to
deviate from the others (it was developed for gaming, which has
different requirements).

GZ provides ways to access the various stages in this process.  Here
are a few:

### Update equations

The only logical way to access this is through a GZP.  GZ offers two
[Events](https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1event_1_1Events.html)
related to this, one before it starts work
(`ConnectWorldUpdateBegin`), and one after it is done
(`ConnectWorldUpdateEnd`).  The "Connect" part refers to the
connection between the callback and the thing sending the callback.
The "WorldUpdate" part is self-explanatory, as are "Begin" and "End".

To do this in a Model plugin, bind a function taking a `const
gazebo::common::UpdateInfo&` to the Begin connection (now would be a
good time to look at the code).

Other Events that can be hooked include the start/pause signals,
adding/removing entities, etc.

### Graphics

This includes both Visual and GUI plugins.  Visual plugins control the
appearances of objects in the simulation, while GUI plugins add a 2D
overlay on top of the main GZ window.

For more information on Visual plugins, start
[here](http://answers.gazebosim.org/question/3383/how-to-add-a-dynamic-visual-marker-in-gazebo/).

For more information on GUI plugins, start
[here](http://gazebosim.org/tutorials?tut=gui_overlay).

### Collisions

To specify this for a new model, use
[URDF](http://wiki.ros.org/urdf/Tutorials/Adding%20Physical%20and%20Collision%20Properties%20to%20a%20URDF%20Model).
To see this from another process, look for ROS messages of type
`gazebo_msgs/Contacts?State` [^regex].  The interface will be familiar
to anyone who has used `tf` before.  To manipulate this in a plugin,
FIXME.








## References

[Wiki page](http://gazebosim.org/tutorials?tut=plugins_hello_world&cat=write_plugin)
[Engines](http://gazebosim.org/blog/feature_physics)

---------------------------------------------------------------------

# Record of discussions on this project

>> Regarding the "gazebo plug-in" option, I have looked into how one
>> writes extensions for Gazebo, and the "boilerplate" part seems to be a
>> non-issue; on the other hand, the "modelling" part might be more
>> complicated.  Springs (or, at least, spring-loaded joints) appear to
>> exist already, as does friction.  Are you looking for linear,
>> piston-like springs?
>> 
>> Separately, how would a gripper work?  Would it be an existing model
>> with spring-pistons covering its inside (using friction to hold the
>> object), or a custom blob?  Also, in which Gazebo physics engines does
>> the gripper fail as you described?
 
> We could discuss in specific how your plug-in could fix the grasp
> stability problem.
> 
> Specifically, let's say there is a contact site of interest on an
> object (eventually, will be a gripper finger).  We would like
> something like the following: *If an object touches the contact site
> of interest, identify the object, the coordinates of touch, the amount
> of penetration (deflection of the virtual spring) and velocity of the
> object (in the direction of penetration) *exert a force vector on the
> object, proportional to the object's penetration (spring deflection)
> and object's velocity (proving damping).
> 
> Perhaps a good place to start would be to simply make a patch on the
> ground that absorbs shock from falling objects.  The object should
> dampen its energy and should come to a stable rest on your surface.
> If you can do that, I expect we could generalize it to fingertips.

---------------------------------------------------------------------

[^regex]: This is a regular expression ("regex").  If you do not
    already know these, LEARN!  They are incredibly useful when doing
    anything related to string processing.  Here, it is used to mean
    "376 or 476".

[^gripper]: These
    [already exist](https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1physics_1_1Gripper.html),
    but we need an example.
