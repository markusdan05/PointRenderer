#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_VertexArrayID;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void UnBind() const;

    void AddVertexBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) const;
};