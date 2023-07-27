#pragma once
class RenderSystem
{
public:
	void bindVertexBuffer();
	void bindIndexBuffer();
	void installShader();
	void attachWindow();
	void draw();
	void drawIndexed();
};

