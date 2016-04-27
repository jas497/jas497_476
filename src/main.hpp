#ifndef _JAS497_476_MAIN_H_
#define _JAS497_476_MAIN_H_

namespace gazebo {
	/**
	 * All GZP are writen in C++ and extend one of the pre-existing classes.
	 * Since we are writing a Model plugin, we use that.
	 */
	class ModelPluginMain : public ModelPlugin {
//////////////////////////////////// FIELDS ////////////////////////////////////
		private:

		/**Pointer to the model to which this plugin is attached.  Documentation
		 * for gazebo::physics::Model can be found here:
		 * https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1physics_1_1Model.html
		 */
		physics::ModelPtr model;

		/**Pointer to the update event connection.*/
		event::ConnectionPtr updateConnection;

		/**Pointer to the global contact manager.*/
		physics::ContactManager* contactManager;

//////////////////////////////// CONSTRUCTOR(S) ////////////////////////////////
		public:

		/**Constructor.*/
		ModelPluginMain(); // : ModelPlugin();

//////////////////////////////////// METHOD ////////////////////////////////////

		/**Called once, when plugin is loaded.  The `override` identifier is
		 * only valid syntax in C++11 or later (which, in April 2016, appears to
		 * be the default.).  This will generate a warning, but the library will
		 * still compile.
		 */
		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override;
		/**Callback we will bind to GZ's updater.*/
		void onUpdate(const common::UpdateInfo& _info);
	};

	/**Incantation for the builder to make the interface..*/
	GZ_REGISTER_MODEL_PLUGIN(ModelPluginMain)
}

#endif /* _JAS497_476_MAIN_H_ */
