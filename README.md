# Final 476 project for jas497, James Starkman

The goal of this 476 project is to explain, in no uncertain terms, how
a Gazebo (GZ) plugin (GZP) is written.  It is meant to be suitable for
reading by future /[34]76/ [^regex] students (and the professor), with
the goal of writing their own plugins.

The primary example that will be used by this plugin is that of
writing a gripper.  For details, see the last section of this read-me
file.

---------------------------------------------------------------------

# Writing a Gazebo plugin

The first step is to decide what type of plugin is desired.  As of
this writing (April 2016), there are six types of plugin: World,
Model, Sensor, System, Visual, and GUI.  The reference plugin will
focus on Model plugins, but the concepts generalize.  The reader is
assumed to be familiar with C++ and using a plain-text editor such as
Emacs, GEdit, or Sublime Text (not an IDE like CLion or Eclipse; their
workflow is different, and has too much magic.  When learning
something for the first time, it is better to do it the hard way
first, then allow automated tools to take over).

## Brief overview of 3D computer simulation

FIXME



## References

[Wiki page](http://gazebosim.org/tutorials?tut=plugins_hello_world&cat=write_plugin)

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


[^regex]: This is a regular expression ("regex").  If you do not
    already know these, LEARN!  They are incredibly useful when doing
    anything string-processing related.
