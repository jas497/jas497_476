//WORST CASE: ALL CONFUSION ABOUT APIS CAN BE RESOLVED HERE:
//https://bitbucket.org/osrf/gazebo/src

////////////////////////////////////////////////////////////////////////////////

// Grimoires of Library Classes, Methods, &c.
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
// more familiar libraries
#include <stdio.h>
#include <boost/bind.hpp>
//notice: we do not need ROS

#include "main.hpp"

namespace gz = gazebo;

typedef gazebo::ModelPluginMain gzmpm;

gzmpm::ModelPluginMain() : gz::ModelPlugin() {
	printf("Model plugin constructor called.\n");
}

void gzmpm::Load(gz::physics::ModelPtr _model, sdf::ElementPtr _sdf) {
	this->model = _model;
	// Attach listener to the update event. This event is broadcast before every
	// simulation iteration, which happens at about a kilohertz.
	this->updateConnection =
		gz::event::Events::ConnectWorldUpdateBegin(
			boost::bind(&gzmpm::onUpdate, this, _1) );

	this->contactManager =
		_model->GetWorld()->GetPhysicsEngine()->GetContactManager();
}

int dec = 0;

void gzmpm::onUpdate(const gz::common::UpdateInfo& _info) {
	//WARNING: This function is called very, very often! (~1000Hz)
	// (Try not to flood the screen with too many print calls.)
	namespace gph = gz::physics;
	gz::common::Time currentTime = _info.simTime;
	std::string      worldName   = _info.worldName;
	gph::ModelPtr    me          = this->model; // trivial, but clear

	unsigned int qtyKids = me->GetChildCount();
	for (unsigned int i = qtyKids; i-->0; ) {
		std::string kid = me->GetChild(i)->GetName();
		//This doesn't work, and I don't know why not.
		gph::CollisionPtr cp = me->GetChildCollision(kid);
		if (cp) { // if actually colliding
			//Not a geometry_msgs/Pose, but a GZ Pose.
			const gz::math::Pose& pose = cp->GetState().GetPose();
			std::cout << "kid=" << kid << " ||| pose=" << pose << std::endl;
		}
	}

	// Works, but needs a <gripper/> in the URDF file (see foogrip.sdf for
	// details).  More about grippers in GZ 2.2.3 (unchanged in 5.3.0):
	// https://bitbucket.org/osrf/gazebo/src/36c46c770764affe94d7829a3fc3a5e2512c4f26/gazebo/physics/Gripper.cc
	const std::vector<gph::Contact*>& contacts =
		this->contactManager->GetContacts();
	unsigned int howManyContacts = contacts.size();
	if (howManyContacts && dec == 0) {
		//shows four, which are assumed to be between the gripper plates and the floor
		printf("This many contacts: %d\n", howManyContacts);
	}
	dec = (dec+1)%10;
}
