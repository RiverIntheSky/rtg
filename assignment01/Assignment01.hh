#pragma once

#include <vector>

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <glow/fwd.hh>

#include <glow-extras/glfw/GlfwApp.hh>

class Assignment01 : public glow::glfw::GlfwApp
{
    struct Student
    {
        std::string name;
        int nr;
    };

private:
    glow::SharedTexture2D mTextureTask;
    glow::SharedVertexArray mQuad;
    glow::SharedVertexArray mMeshTask;
    glow::SharedProgram mShaderTask;
    glow::SharedProgram mShaderObj;

    glm::vec2 mVelocity = {0.234f, -0.345f};
    glm::vec2 mPosition = {0.45f, 0.45f};
    glm::vec2 mSize = {0.1f, 0.1f};

private:
    std::vector<Student> getGroup() const;
    void generateTask();

public:
    void mainLoop() override;
    void init() override;
    void update(float elapsedSeconds) override;
    void render(float = 0.0f) override;
};
