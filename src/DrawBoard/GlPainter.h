#pragma once
#include <list>
#include <glad/glad.h>
using std::list;
class GlPainter {
public:
	virtual void draw() const = 0;
	virtual void setSize(const int& size) = 0;
	static void deleteVertexArrays() {
		for (auto it : vao) {
			glDeleteVertexArrays(1, &it);
		}
	};
	static void deleteBuffers() {
		for (auto it : vbo) {
			glDeleteBuffers(1, &it);
		}
	}
protected:
	static list<GLuint> vao;
	static list<GLuint> vbo;
};
