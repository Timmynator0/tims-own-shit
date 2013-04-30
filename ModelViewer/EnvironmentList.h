#pragma once

#include <cavelib/GUIPanel.h>

class ModelViewer;

class EnvironmentList : public GUIPanel
{
public:
	EnvironmentList(ModelViewer* modelViewer);
	~EnvironmentList(void);
};

