#ifndef LOADOBJ_H
#define LOADOBJ_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
using namespace std;

void load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements);

#endif // LOADOBJ_H
