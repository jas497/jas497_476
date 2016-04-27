// Grimoires of Library Classes, Methods, &c.
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
// more familiar libraries
#include <stdio.h>
#include <boost/bind.hpp>

#include "main.hpp"

namespace gz = gazebo;

typedef gazebo::ModelPluginMain gzmpm;

gzmpm::ModelPluginMain() : gz::ModelPlugin() {
	printf("Model plugin constructor called.\n");
}

void gzmpm::Load(gz::physics::ModelPtr _model, sdf::ElementPtr _sdf) {
	this->model = _model;
	// Attach listener to the update event. This event is broadcast before every
	// simulation iteration.
	this->updateConnection =
		gz::event::Events::ConnectWorldUpdateBegin(
			boost::bind(&gzmpm::onUpdate, this, _1) );
}

void gzmpm::onUpdate(const gz::common::UpdateInfo& _info) {
	//https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1common_1_1UpdateInfo.html
	gz::common::Time currentTime = _info->simTime;
	std::string      worldName   = _info->worldName;
	
}
