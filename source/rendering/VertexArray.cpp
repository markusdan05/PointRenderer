#include "VertexArray.h"

#include "GL/glew.h"

#include "VertexBuffer.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_VertexArrayID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_VertexArrayID);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_VertexArrayID);
}

void VertexArray::UnBind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) const {
    Bind();
    buffer.Bind();
    const auto& elements = layout.GetElements();
    unsigned int attributeOffset = 0;
    for (int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)attributeOffset);
        attributeOffset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}
