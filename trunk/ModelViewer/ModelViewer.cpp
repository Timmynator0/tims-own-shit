#include <GL/glew.h>

#include <vrj/draw/OpenGL/DrawManager.h>
#include "ModelViewer.h"
#include "MainPanel.h"
#include "EnvironmentList.h"

#include <CaveLib/texture.h>
#include <cavelib/model.h>
#include <cavelib/Shader.h>

#include <gmtl/Xforms.h>
#include <gmtl/Ray.h>
#include <gmtl/VecOps.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Math.h>

ModelViewer::ModelViewer(void)
{
	environmentList = NULL;
	modelFile = "d:/cave/runtime/data/models/trex/dino poly.lwo";
	model = NULL;
	panel = NULL;
	scale = 1;
	useTexture = true;
	useLighting = true;
}


ModelViewer::~ModelViewer(void)
{
}

void ModelViewer::init()
{
	mWand.init("VJWand");
	mHead.init("VJHead");
	mLeftButton.init("VJButton0");

}

void ModelViewer::contextInit()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	panel = new MainPanel(this);


	shader = new ShaderProgram("data/ModelViewer/shaders/default.vert", "data/ModelViewer/shaders/default.frag");
	shader->bindAttributeLocation("a_position", 0);
	shader->bindAttributeLocation("a_normal",	1);
	shader->bindAttributeLocation("a_texCoord", 2);
	//	shader->bindFragLocation("fragColor", 0);
	shader->link();
	shader->use();


	front = CaveLib::loadTexture("data/cubemaps/wall.png");
	left = CaveLib::loadTexture("data/cubemaps/wall.png");
	right = CaveLib::loadTexture("data/cubemaps/wall.png");
	bottom = CaveLib::loadTexture("data/cubemaps/wall.png");
	if(modelFile != "" && model == NULL)
	{
		ModelLoadOptions* options = new ModelLoadOptions();
		options->scale = 5;
		model = CaveLib::loadModel(modelFile, options);
		position = gmtl::Vec3f(0,-5 - model->bbox.mMin[1],-4 - model->bbox.mMin[2]);
	}

}

void ModelViewer::bufferPreDraw()
{
	glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


float lightRot = 0;

void ModelViewer::preFrame()
{
	lightRot += 0.01f;
	if(panel || environmentList)
	{
		mWand->updateData();
		gmtl::Matrix44f mat = mWand->getData();

		gmtl::Vec4f origin = mat * gmtl::Vec4f(0,0,0,1);
		gmtl::Vec4f point = mat * gmtl::Vec4f(0,0,-1,1);
		gmtl::Vec4f diff = point - origin;

		

		gmtl::Rayf selector(gmtl::Vec3f(origin[0], origin[1], origin[2]), gmtl::Vec3f(diff[0], diff[1], diff[2]));
		panel->setSelector(selector);
		if(environmentList)
			environmentList->setSelector(selector);

		gadget::DigitalState::State data = mLeftButton->getData();
		if(data == gadget::Digital::TOGGLE_ON)
		{
			if(environmentList)
				environmentList->mouseDown();
			else
				panel->mouseDown();

			if((!environmentList || !environmentList->selectedComponent) && !panel->selectedComponent)
			{
				startDrag = selector.mOrigin;
				startDirection = selector.mDir;
				dragging = true;
			}
		}
		else if(data == gadget::Digital::TOGGLE_OFF)
		{
			if(dragging)
			{
				dragging = false;
			}
			else if(environmentList)
				environmentList->mouseUp();
			else
				panel->mouseUp();
		}
		else if (data == gadget::Digital::ON)
		{
			gmtl::Vec3f diff = startDrag - selector.mOrigin;
			if(dragging)
			{
				if(panel->getManipulation() == MainPanel::TRANSLATE)
					position += selector.mDir / 20.0f;
				else if(panel->getManipulation() == MainPanel::ROTATE)
				{
					float rot1 = atan2(startDirection[2], startDirection[0]);
					float rot2 = atan2(selector.mDir[2], selector.mDir[0]);

					float diff = rot1 - rot2;
					while(diff > 3.1416)
						diff -= 2*3.1416;
					
					while(diff < 3.1416)
						diff += 2*3.1416;
					

					rotation = rotation * gmtl::make<gmtl::Quatf>(gmtl::EulerAngleXYZf(0,diff,0));
				}
				else if(panel->getManipulation() == MainPanel::SCALE)
					scale *= 1 + selector.mDir[1] / 20.0f;


				startDirection = selector.mDir;
				startDrag = selector.mOrigin;
			}
		}

		gmtl::Point3f head = mHead->getData() * gmtl::Point3f(0,0,0);
		if(head[2] < -4)
		{
			panel->renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(-1,-2,-5));
		}
		else
		{
			if(head[0] < -3)
			{
				panel->renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(5,-2,-1));
				panel->renderMatrix *= gmtl::make<gmtl::Matrix44f>(gmtl::EulerAngleXYZf(0, -3.1415/2, 0));
			}
			else if(head[0] > 3)
			{
				panel->renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(-5,-2,-1));
				panel->renderMatrix *= gmtl::make<gmtl::Matrix44f>(gmtl::EulerAngleXYZf(0, 3.1415/2, 0));
			}
			else
				panel->renderMatrix = gmtl::makeTrans<gmtl::Matrix44f>(gmtl::Vec3f(-1,-2,-5));

		}
	}
}

void ModelViewer::draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);


	glUseProgram(0);

	glColor4f(1,1,1,1);
	glDisable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	if(front)
	{
		glBindTexture(GL_TEXTURE_2D, front->tid());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -5.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f,  5.0f, -5.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f,  5.0f, -5.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f, -5.0f);  // Bottom Left Of The Texture and Quad
		glEnd();
	}

	if(bottom)
	{
		glBindTexture(GL_TEXTURE_2D, bottom->tid());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f, -5.0f, -5.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f, -5.0f, -5.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f,  5.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f,  5.0f);  // Bottom Right Of The Texture and Quad
		glEnd();
	}

	if(right)
	{
		glBindTexture(GL_TEXTURE_2D, right->tid());
		glBegin(GL_QUADS);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.0f, -5.0f, -5.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.0f,  5.0f, -5.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 5.0f,  5.0f,  5.0f);  // Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 5.0f, -5.0f,  5.0f);  // Bottom Left Of The Texture and Quad
		glEnd();
	}

	if(left)
	{
		glBindTexture(GL_TEXTURE_2D, left->tid());
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -5.0f, -5.0f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-5.0f, -5.0f,  5.0f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-5.0f,  5.0f,  5.0f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f,  5.0f, -5.0f);  // Top Left Of The Texture and Quad
		glEnd();
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	float amb[] = { 0.2, 0.2, 0.2, 1.0 }; glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	float dif[] = { 0.8, 0.8, 0.8, 1.0 }; glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	float spe[] = { 0.0, 0.0, 0.0, 1.0 }; glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);
	glColor3f(1,1,1);
	float pos[] = { 0.0, 0.0, 0.0, 1.0 }; glLightfv(GL_LIGHT0, GL_POSITION, pos);



	panel->draw();
	if(environmentList)
		environmentList->draw();

	glColor3f(1,1,1);

	if(model)
	{
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GEQUAL, 0.99);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_NORMALIZE);
		glDisable(GL_COLOR_MATERIAL);
		glPushMatrix();


		glTranslatef(position[0], position[1], position[2]);
		glScalef(scale, scale, scale);
		gmtl::Matrix44f rot = gmtl::make<gmtl::Matrix44f>(rotation);
		glMultMatrixf(rot.mData);


		shader->use();
		gmtl::Matrix44f modelViewMatrix;
		gmtl::identity(modelViewMatrix);
		modelViewMatrix *= gmtl::makeTrans<gmtl::Matrix44f>(position);
		modelViewMatrix *= gmtl::makeScale<gmtl::Matrix44f>(scale);
		modelViewMatrix *= gmtl::make<gmtl::Matrix44f>(rotation);
//		modelViewMatrix *= gmtl::make<gmtl::Matrix44f>(gmtl::EulerAngleXYZf(-0.507f, 2.309f, 0.0f));



		gmtl::Matrix33f normalMatrix;
		normalMatrix.set(modelViewMatrix[0][0], modelViewMatrix[0][1], modelViewMatrix[0][2],
			modelViewMatrix[1][0], modelViewMatrix[1][1], modelViewMatrix[1][2],
			modelViewMatrix[2][0], modelViewMatrix[2][1], modelViewMatrix[2][2]);
		normalMatrix = gmtl::transpose(gmtl::invert(normalMatrix));
		//end of camera


		gmtl::Vec4f head = mHead->getData() * gmtl::Vec4f(0,0,0,1);


		shader->setUniformVec3("lightPosition", gmtl::Vec3f(head[0], head[1], head[2]));



		gmtl::Matrix44f projectionMatrix;

		glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix.mData);


		shader->setUniformBool("useLighting", useLighting);
		shader->setUniformBool("useTexture", useTexture);
		if(useTexture)
			shader->setUniformInt("s_texture", 0);

		shader->setUniformMatrix3("normalMatrix", normalMatrix);
		shader->setUniformMatrix4("modelViewProjectionMatrix", projectionMatrix * modelViewMatrix);
		shader->setUniformMatrix4("modelViewMatrix", modelViewMatrix);

		model->draw(shader);
//		glUseProgram(0);
//		model->draw(NULL);

		glPopMatrix();
	}


}

void ModelViewer::setModel( std::string modelFile )
{
	this->modelFile = modelFile;
}

void ModelViewer::setEnvironment( std::string environment )
{
	delete front;
	delete left;
	delete right;
	delete bottom;
	front = NULL;
	left = NULL;
	right = NULL;
	bottom = NULL;
	if(environment != "")
	{
		front = CaveLib::loadTexture("data/cubemaps/" + environment + "/front.png");
		left = CaveLib::loadTexture("data/cubemaps/" + environment + "/left.png");
		right = CaveLib::loadTexture("data/cubemaps/" + environment + "/right.png");
		bottom = CaveLib::loadTexture("data/cubemaps/" + environment + "/bottom.png");
	}
	panel->envButton->setEnvironment(environment != "" ? environment : "None");
}
