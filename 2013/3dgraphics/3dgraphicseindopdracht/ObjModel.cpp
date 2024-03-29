#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "loadTGA.h"

std::string replace(std::string str, std::string toReplace, std::string replacement)
{
	size_t index = 0;
	while (true) 
	{
		 index = str.find(toReplace, index);
		 if (index == std::string::npos) 
			 break;
		 str.replace(index, toReplace.length(), replacement);
		 ++index;
	}
	return str;
}

std::vector<std::string> split(std::string str, std::string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while(true)
	{
		index = str.find(sep);
		if(index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index+1);
	}
	ret.push_back(str);
	return ret;
}

inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}




ObjModel::ObjModel(std::string fileName)
{
	std::string dirName = fileName;
	if(dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if(dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if(fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());



	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while(!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		
		line = replace(line, "\t", " ");
		while(line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if(line == "")
			continue;
		if(line[0] == ' ')
			line = line.substr(1);
		if(line == "")
			continue;
		if(line[line.length()-1] == ' ')
			line = line.substr(0, line.length()-1);
		if(line == "")
			continue;
		if(line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if(params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if(params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if(params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if(params[0] == "f")
		{
			for(size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for(size_t i = ii-3; i < ii; i++)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii-3) ? 1 : i], "/");
					if(indices.size() >= 1)
						vertex.position = atoi(indices[0].c_str())-1;
					if(indices.size() == 2) //texture 
						vertex.texcoord = atoi(indices[1].c_str())-1;
					if(indices.size() == 3)
					{
						if( indices[1] != "")
						{
							vertex.texcoord = atoi(indices[1].c_str())-1;
						}
						vertex.normal = atoi(indices[2].c_str())-1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if(params[0] == "s")
		{
		}
        else if(params[0] == "mtllib")
        {
            loadMaterialFile(dirName + "/" + params[1], dirName);
        }
		else if(params[0] == "usemtl")
		{
			if(currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for(size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if(info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if(currentGroup->materialIndex == -1)
				std::cout<<"Could not find material name "<<params[1]<<std::endl;
				;
		}
	}
	groups.push_back(currentGroup);
}


ObjModel::~ObjModel(void)
{
}

Texture::Texture(std::string location)
{
	glGenTextures(TEXTURE_COUNT, textures);
	if(texcount <0) texcount = 0;
	std::vector<std::string> params = split(location, ".");
	std::string locatie = params[0]+".tga";
	std::cout<<"locatie "<<locatie<<std::endl;
	TextureFiles[texcount] = locatie.c_str();
	// het laden van de texture
	glBindTexture(GL_TEXTURE_2D, textures[texcount]);
	LoadTGATexture(TextureFiles[texcount], GL_LINEAR, GL_LINEAR, GL_CLAMP);
	number = texcount;
	texcount++;
}
Texture::~Texture(void)
{
}
Texture::Texture()
{
}
void ObjModel::draw()
{
	for(size_t i = 0; i < groups.size(); i++)
	{
		Texture t = this->materials.at(groups[i]->materialIndex)->texture;
		glBindTexture(GL_TEXTURE_2D, t.textures[t.number]);
		glBegin(GL_TRIANGLES);
		for(list<Face>::iterator face = groups[i]->faces.begin(); face != groups[i]->faces.end(); face++)
		{
			for(list<Vertex>::iterator vertex = face->vertices.begin(); vertex != face->vertices.end(); vertex++)
			{
				glNormal3fv(normals[vertex->normal].v);
				glTexCoord2fv(texcoords[vertex->texcoord].v);
				glVertex3fv(vertices[vertex->position].v);
			}		
		}
		glEnd();
	}
}


void ObjModel::loadMaterialFile( std::string fileName, std::string dirName )
{
	std::ifstream pFile(fileName.c_str());

	MaterialInfo* currentMaterial = NULL;

	while(!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		
		line = replace(line, "\t", " ");
		while(line.find("  ") != std::string::npos)
			line = replace(line, "  ", " ");
		if(line == "")
			continue;
		if(line[0] == ' ')
			line = line.substr(1);
		if(line == "")
			continue;
		if(line[line.length()-1] == ' ')
			line = line.substr(0, line.length()-1);
		if(line == "")
			continue;
		if(line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if(params[0] == "newmtl")
		{
			if(currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if(params[0] == "map_kd")
		{
			Texture currentTexture(""+dirName + "/" + params[1]);
			currentMaterial->hasTexture = true;
			currentMaterial->texture = currentTexture;
		}
		else
			//std::cout<<"Didn't parse "<<params[0]<<" in material file"<<std::endl;
			;
	}
	if(currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

ObjModel::MaterialInfo::MaterialInfo()
{
	hasTexture = false;
}
std::vector<Vec3f>*	ObjModel::getVertices()
{
	return &vertices;
}


Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}
