#include "pch.h"
#include "GraphicsEngine.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>



#include <sstream>

void GraphicsEngine::initOpenGL()
{
	
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // �����
		PFD_TYPE_RGBA,        // ���-�� ����� �����������. RGBA ��� �������.
		32,                   // �������� ������� �����������.
		0, 0, 0, 0, 0, 0,
		24,
		0,
		0,
		0, 0, 0, 0,
		24,                    // ���������� ����� ��� ������ �������
		8,                    // ���������� ����� ��� ������ ���������
		0,                    // ���������� ��������������� ������� � ������ ������.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
    glewExperimental = TRUE;
	if (auto pf = ChoosePixelFormat(dc, &pfd)) {
		if (SetPixelFormat(dc, pf, &pfd)) {
			renderContext = wglCreateContext(dc);
			
			if (wglMakeCurrent(dc, renderContext)) {
				if (glewInit() == GLEW_OK) {
                    int a = 5;
				}
			}
		}
	}
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	
}

void GraphicsEngine::beginMainLoop()
{
    
	static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
	};
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    GLuint programID = LoadShaders("Shader\\shader.vert", "Shader\\shader.frag");
	while (true) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // ������� 0. ��������� �� ���� ����� ���������� � �����, ����������� ��������.
			3,                  // ������
			GL_FLOAT,           // ���
			GL_FALSE,           // ���������, ��� �������� �� �������������
			0,                  // ���
			(void*)0            // �������� ������� � ������
		);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		SwapBuffers(dc);
	}
}

GLuint GraphicsEngine::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    // ������� �������
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // ��������� ��� ���������� ������� �� �����
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }

    // ��������� ��� ������������ ������� �� �����
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // ����������� ��������� ������
    printf("���������� �������: %sn", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // ��������� �������� ���������� �������
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
    }

    // ����������� ����������� ������
    printf("���������� �������: %sn", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // ��������� ����������� ������
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    // ������� ��������� ��������� � ����������� ������� � ���
    fprintf(stdout, "������� ��������� ��������� � ����������� ������� � ���n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // ��������� ��������� ���������
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;

}

GraphicsEngine::GraphicsEngine(HWND hWND) : hWND{ hWND }, dc{ GetDC(hWND) } {
	
}

GraphicsEngine::~GraphicsEngine()
{

}

void GraphicsEngine::run()
{
    initOpenGL();
	beginMainLoop();
}



void* createGraphicsEngine(HWND hWND)
{
	return new GraphicsEngine(hWND);
}

void destroyGraphicsEngine(GraphicsEngine* target)
{
	target->~GraphicsEngine();
}

void runGraphicsEngine(GraphicsEngine* target)
{
	target->run();
}