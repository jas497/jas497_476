namespace gazebo {
	/**
	 * All GZP are writen in C++ and extend one of the pre-existing classes.
	 * Since we are writing a Model plugin, we use that.
	 */
	class ModelPluginMain : public ModelPlugin {
		public:
		ModelPluginMain() : ModelPlugin() {}
		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf);
	};
	/**Incantation for the builder to make the interface..*/
	GZ_REGISTER_MODEL_PLUGIN(ModelPluginMain)
}
