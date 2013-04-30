#pragma once

#include <cavelib/GUIPanel.h>
#include <cavelib/Components/Button.h>
#include <cavelib/Components/CheckBox.h>

class ModelViewer;


class EnvironmentButton : public Button
{
	ModelViewer* modelViewer;
public:
	EnvironmentButton(ModelViewer* modelViewer);
	void setEnvironment(std::string env);
	void click();
};




class MainPanel : public GUIPanel
{	
public:
	enum Manipulation
	{
		TRANSLATE,
		ROTATE,
		SCALE,
	};
private:
	Manipulation manipulation;
public:
	
	void setManipulation(Manipulation manipulation);
	Manipulation getManipulation();

	CheckBox* translate;
	CheckBox* rotate;
	CheckBox* scale;
	CheckBox* navigation;

	EnvironmentButton* envButton;

	MainPanel(ModelViewer* modelViewer);
	~MainPanel(void);
};

