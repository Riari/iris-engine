#pragma once

class VAO {
public:
    VAO();

    void Bind() const;
    void Release() const;
    static void Unbind();
private:
    unsigned int m_vao{};
};