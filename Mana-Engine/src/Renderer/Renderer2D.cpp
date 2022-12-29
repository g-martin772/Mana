#include "manapch.h"
#include "Renderer2D.h"

#include "Shader.h"
#include "Buffer.h"
#include "RenderCommand.h"

namespace Mana {
	struct QuadVertex
	{
		vec3 Position;
		vec4 Color;
	};

	struct BatchData {
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		Ref<Shader> Shader;
		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;

		vec4 VertexPositions[4];

		uint32_t IndexCount = 0;
		QuadVertex* VertexBufferBase = nullptr;
		QuadVertex* VertexBufferPtr = nullptr;
	};

	static BatchData s_Data;

	void Mana::Renderer2D::Init()
	{
		s_Data.VertexArray = VertexArray::Create();
		s_Data.VertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color"    }
			});

		s_Data.VertexArray->AddVertexBuffer(s_Data.VertexBuffer);
		s_Data.VertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.VertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		s_Data.Shader = Shader::Create("assets/shaders/SimpleShader.glsl");

		s_Data.VertexPositions[0] = vec4{ -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.VertexPositions[1] = vec4{  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.VertexPositions[2] = vec4{  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.VertexPositions[3] = vec4{ -0.5f,  0.5f, 0.0f, 1.0f };
	}
	
	void Renderer2D::Shutdown()
	{
		delete[] s_Data.VertexBufferBase;
	}
	
	void Renderer2D::BeginScene()
	{
		s_Data.Shader->Bind();
		StartBatch();
	}
	
	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::DrawQuad(const mat4& transform, SpriteRendererComponent src)
	{
		
	}
	
	void Renderer2D::DrawQuad(TransformComponent tc, SpriteRendererComponent src)
	{
		constexpr size_t vertexCount = 4;

		if (s_Data.IndexCount >= BatchData::MaxIndices)
			NextBatch();

		for (size_t i = 0; i < vertexCount; i++) {
			s_Data.VertexBufferPtr->Position = tc.GetTransform() * s_Data.VertexPositions[i];
			s_Data.VertexBufferPtr->Color = src.Color;
			s_Data.VertexBufferPtr++;
		}

		s_Data.IndexCount += 6;
	}
	
	void Renderer2D::StartBatch()
	{
		s_Data.IndexCount = 0;
		s_Data.VertexBufferPtr = s_Data.VertexBufferBase;
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}
	
	void Renderer2D::Flush()
	{
		if (s_Data.IndexCount == 0)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.VertexBufferPtr - (uint8_t*)s_Data.VertexBufferBase);
		s_Data.VertexBuffer->SetData(s_Data.VertexBufferBase, dataSize);

		s_Data.Shader->Bind();
		RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.IndexCount);
	}
}

