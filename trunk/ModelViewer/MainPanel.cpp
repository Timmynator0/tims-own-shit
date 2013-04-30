#include "MainPanel.h"
#include "ModelViewer.h"
#include "EnvironmentList.h"

#include <cavelib/Components/Panel.h>
#include <cavelib/components/Label.h>
#include <cavelib/components/CheckBox.h>
#include <CaveLib/Components/Button.h>
#include <cavelib/LayoutManagers/TableLayout.h>

#include <gmtl/Matrix.h>
#include <gmtl/Generate.h>

class ManipulateButton : public CheckBox
{
	MainPanel::Manipulation manipulation;
	MainPanel* mainPanel;
public:
	ManipulateButton(bool v, MainPanel::Manipulation manipulation, MainPanel* mainPanel) : CheckBox(v)
	{
		this->manipulation = manipulation;
		this->mainPanel = mainPanel;
	}

	void click()
	{
		CheckBox::click();
		mainPanel->setManipulation(manipulation);
	}
	
};


MainPanel::MainPanel(ModelViewer* modelViewer) : GUIPanel("")
{
	rootPanel = new Panel(new TableLayoutManager(2));

	rootPanel->add(new Label("Rotate"));
	rootPanel->add(rotate = new ManipulateButton(true, ROTATE, this));
	rootPanel->add(new Label("Translate"));
	rootPanel->add(translate = new ManipulateButton(false, TRANSLATE, this));
	rootPanel->add(new Label("Scale"));
	rootPanel->add(scale = new ManipulateButton(false, SCALE, this));
	rootPanel->add(new Label("Environment"));
	rootPanel->add(envButton = new EnvironmentButton(modelViewer));
//	rootPanel->add(new Label("Navigation"));
//	rootPanel->add(navigation = new CheckBox(false));

	setManipulation(TRANSLATE);

	rootPanel->reposition(0,0,2,3);
	rootPanel->setFont(font);

	renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(-1,-2,-5));
}


MainPanel::~MainPanel(void)
{
}

void MainPanel::setManipulation( Manipulation manipulation )
{
	this->manipulation = manipulation;
	rotate->v = manipulation == ROTATE;
	translate->v = manipulation == TRANSLATE;
	scale->v = manipulation == SCALE;
}

MainPanel::Manipulation MainPanel::getManipulation()
{
	return manipulation;
}

EnvironmentButton::EnvironmentButton( ModelViewer* modelViewer ) : Button("Environment")
{
	this->modelViewer = modelViewer;
}

void EnvironmentButton::setEnvironment( std::string env )
{
	text = env;
}

void EnvironmentButton::click()
{
	modelViewer->environmentList = new EnvironmentList(modelViewer);
}
