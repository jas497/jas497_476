#include <gazebo/gazebo.hh>

namespace gazebo {
	class ModelPluginMain : public ModelPlugin {
		public:
		ModelPluginMain() : ModelPlugin() {
			printf("Model plugin constructor called.\n");
		}
		void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {}
	};
	GZ_REGISTER_MODEL_PLUGIN(ModelPluginMain)
}

