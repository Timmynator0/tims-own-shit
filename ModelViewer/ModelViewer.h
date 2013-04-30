#pragma once

#include <vrj/Draw/OpenGL/App.h>
#include <gadget/Type/PositionInterface.h>
#include <gadget/Type/DigitalInterface.h>

#include <gmtl/Quat.h>
#include <gmtl/Vec.h>

#include <string>

class cTexture;
class MainPanel;
class cModel;
class EnvironmentList;
class ShaderProgram;

class ModelViewer : public vrj::opengl::App
{
private:
	MainPanel* panel;
	gadget::PositionInterface  mWand;
	gadget::PositionInterface	mHead;
	gadget::DigitalInterface	  mLeftButton;
	std::string modelFile;

	cModel* model;
	cTexture* left;
	cTexture* right;
	cTexture* bottom;
	cTexture* front;

	ShaderProgram* shader;

	gmtl::Vec3f position;
	gmtl::Quatf rotation;
	float scale;

	bool dragging;
	gmtl::Point3f startDrag;
	gmtl::Vec3f startDirection;

public:
	EnvironmentList* environmentList;



	ModelViewer(void);
	~ModelViewer(void);
	void setModel(std::string modelFile);

	virtual void draw();
	virtual void contextInit();
	virtual void bufferPreDraw();
	virtual void preFrame();

	virtual void init();
	void setEnvironment( std::string environment );


	bool useLighting;
	bool useTexture;
};

