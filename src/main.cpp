// Grimoires of Library Classes, Methods, &c.
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
// more familiar libraries
#include <stdio.h>
#include <boost/bind.hpp>

#include "main.hpp"

namespace gz     = gazebo;
namespace gzmpm  = gazebo::ModelPluginMain;
namespace gzphys = gazebo::physics;

gzmpm::ModelPluginMain() : ModelPlugin() {
	printf("Model plugin constructor called.\n");
}

void gzmpm::Load(gzphys::ModelPtr _model, gazebo::sdf::ElementPtr _sdf) {
	this->model = _model;
	// Listen to the update event. This event is broadcast every
	// simulation iteration.
	this->updateConnection =
		gazebo::event::Events::ConnectWorldUpdateBegin(
			boost::bind(&ModelPluginMain::OnUpdate, this, _1) );
}

void gzmpm::OnUpdate(const common::UpdateInfo& _info) {
	//do stuff
}
