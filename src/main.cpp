// Grimoires of Library Classes, Methods, &c.
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
// more familiar libraries
#include <stdio.h>
#include <boost/bind.hpp>

#include "main.hpp"

namespace gzmpm = gazebo::ModelPluginMain;

gzmpm::ModelPluginMain() : ModelPlugin() {
	printf("Model plugin constructor called.\n");
}

void gzmpm::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
	//FIXME
}

