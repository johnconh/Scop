#pragma once

#include "test.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../Shader.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include <memory>

namespace test {

    class TestTexture2D: public Test
    {
        public:
            TestTexture2D();
            ~TestTexture2D();

            void OnUpdate(float deltaTime) override;
            void OnRender() override;
            void OnImGuiRender() override;

        private:
            glm::vec3 m_TranslationA, m_TranslationB;
            glm::mat4 m_Proj, m_View;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<VertexArray> m_VAO;
            std::unique_ptr<VertexBuffer> m_VB;
            std::unique_ptr<IndexBuffer> m_IB;
            std::unique_ptr<Texture> m_Texture;
    };
};