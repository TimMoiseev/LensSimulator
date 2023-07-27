#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const GLfloat* data, const GLfloat* colorData, UINT16 vertexCount, bool colored) : colored{ colored }, Buffer { data, colorData }
{
	glGenBuffers(1, &vertexBufferIndex);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIndex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertexCount, data, GL_STATIC_DRAW);
    if (colored) {
        glGenBuffers(1, &colorBufferIndex);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferIndex);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexCount, colorData, GL_STATIC_DRAW);
    }
}

void VertexBuffer::bind()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIndex);
    glVertexAttribPointer(
        0,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
        3,                                // Размер
        GL_FLOAT,                         // Тип
        GL_FALSE,                         // Нормализован?
        0,                                // Шаг
        (void*)0                          // Смещение
    );
    if (colored) {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferIndex);
        glVertexAttribPointer(
            1,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
            3,                                // Размер
            GL_FLOAT,                         // Тип
            GL_FALSE,                         // Нормализован?
            0,                                // Шаг
            (void*)0                          // Смещение
        );
    }

}


