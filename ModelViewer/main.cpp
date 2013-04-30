#include <cstdlib>
#include "ModelViewer.h"

// --- Lib Stuff --- //
#include <vrj/Kernel/Kernel.h>



int main(int argc, char* argv[])
{
	vrj::Kernel* kernel = vrj::Kernel::instance();  // Get the kernel
	ModelViewer* application = new ModelViewer();             // Instantiate an instance of the app



	// Load any config files specified on the command line
	kernel->init(argc, argv);
	for( int i = 1; i < argc; ++i )
	{
		if(strcmp(argv[i], "--vrjconfig") == 0)
		{
			i++;
			kernel->loadConfigFile(argv[i]);
		}
		if(strcmp(argv[i], "--model") == 0)
		{
			i++;
			application->setModel(std::string(argv[i]));
		}
		if(strcmp(argv[i], "--nolighting") == 0)
			application->useLighting = false;
		if(strcmp(argv[i], "--notexture") == 0)
			application->useTexture = false;
	}

	kernel->start();

	kernel->setApplication(application);
	kernel->waitForKernelStop();
	return 0;
}
