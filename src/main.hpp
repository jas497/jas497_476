namespace gazebo {
	/**
	 * All GZP are writen in C++ and extend one of the pre-existing classes.
	 * Since we are writing a Model plugin, we use that.
	 */
	class ModelPluginMain : public ModelPlugin {
		public:

		ModelPluginMain() : ModelPlugin() {}
		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
		void OnUpdate(const common::UpdateInfo& _info);

		private:

		/**Pointer to the model to which this plugin is attached.  Documentation
		 * for gazebo::physics::Model can be found here:
		 * https://osrf-distributions.s3.amazonaws.com/gazebo/api/dev/classgazebo_1_1physics_1_1Model.html
		 */
		physics::ModelPtr model;

		/**Pointer to the update event connection.*/
		event::ConnectionPtr updateConnection;
	};

	/**Incantation for the builder to make the interface..*/
	GZ_REGISTER_MODEL_PLUGIN(ModelPluginMain)
}
