#pragma once
#ifndef __plyRead_h__
#define __plyRead_h__

#include <iostream>
#include <fstream>
#include <string> 

#include "Core\FeimosRender.h"
#include "Core\Geometry.hpp"
#include "Core\Transform.h"

#include "MainGUI/DebugText.hpp"

namespace Feimos {

class plyInfo {
public:
	int nVertices, nTriangles;
	Point3f *vertexArray;
	int *vertexIndices;
	plyInfo(std::string filePath) {

		std::fstream f(filePath);
		std::string ed;
		for (int i = 0; i < 2; i++) {
			f >> ed;
			if (ed == "vertex") f >> nVertices;
			else if (ed == "face") f >> nTriangles;
		}
		
		vertexArray = new Point3f[nVertices];
		vertexIndices = new int[3 * nTriangles];

		for (int i = 0; i < nVertices; i++) {
			f >> vertexArray[i][0];
			f >> vertexArray[i][1];
			f >> vertexArray[i][2];
			vertexArray[i] *= 20;
		}
		for (int i = 0; i < nTriangles; i++) {
			f >> ed;
			f >> vertexIndices[i * 3 + 0];
			f >> vertexIndices[i * 3 + 1];
			f >> vertexIndices[i * 3 + 2];
		}
	}


};


}



#endif


