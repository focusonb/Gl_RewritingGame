#pragma once
#include "glSquarePainter.h"

enum class CorlorChess { white,black};



class GlCirclePainter : public GlPainter
{
public:
	GlCirclePainter() = delete;
	GlCirclePainter(const PointGl& point, int width, CorlorChess color);
	void draw() const override;
	void setSize(const int& size) override {};
	void addOne(const PointGl& point, int width);
protected:
	bool configureShader(CorlorChess color);

private:
	GLuint VAO, VAO1, VBO, VBO1;
	unsigned int shaderProgram;
	unsigned int shaderProgramOutSquare;
	unsigned int texture1;
	list<GLuint> m_vao;
	list<GLuint> m_vao1;
};