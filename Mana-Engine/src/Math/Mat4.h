#pragma once

#include "Core/Core.h"

#include "Vec3.h"
#include "Vec4.h"
#include "MathUtils.h"

#include <cmath>
#include <array>

// Where is this coming from, its apearantly not cmath
#undef near
#undef far

namespace Mana {
	// for now only with float, is there any need to make this templated like vec?
	class MANA_API mat4
	{
	public:
		std::array<float, 16> elements;

		mat4() {}

		mat4(float diag) {
			elements = { diag, 0.0f, 0.0f, 0.0f,
						 0.0f, diag, 0.0f, 0.0f,
						 0.0f, 0.0f, diag, 0.0f,
						 0.0f, 0.0f, 0.0f, diag };
		}

		static mat4 Identity() {
			return mat4(1);
		}

		static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) {
			mat4 result;

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		static mat4 Perspective(float fov, float aspectRatio, float near, float far) {
			mat4 result;

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		static mat4 Translation(const vec3& translation) {
			mat4 result;

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		static mat4 Rotation(float angle, const vec3& axis) {
			mat4 result;

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		}

		static mat4 Scale(const vec3& scale) {
			mat4 result;

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		mat4& Multiply(const mat4& other) {
			float data[16];
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					data[x + y * 4] = sum;
				}
			}
			std::memcpy(elements.data(), data, 16 * sizeof(float));

			return *this;
		}

		friend mat4 operator*(mat4 left, const mat4& right) {
			return left.Multiply(right);
		}

		vec3 Multiply(const vec3& other) const {
			return vec3(
				elements[0] * other.x + elements[1] * other.y + elements[2] * other.z + elements[3],
				elements[4] * other.x + elements[5] * other.y + elements[6] * other.z + elements[7],
				elements[8] * other.x + elements[9] * other.y + elements[10] * other.z + elements[11]);
		}

		friend vec3 operator*(const mat4& left, const vec3& right) {
			return left.Multiply(right);
		}

		vec4 Multiply(const vec4& other) const {
			return vec4(
				elements[0] * other.x + elements[1] * other.y + elements[2] * other.z + elements[3] * other.w,
				elements[4] * other.x + elements[5] * other.y + elements[6] * other.z + elements[7] * other.w,
				elements[8] * other.x + elements[9] * other.y + elements[10] * other.z + elements[11] * other.w,
				elements[12] * other.x + elements[13] * other.y + elements[14] * other.z + elements[15] * other.w);
		}

		friend vec4 operator*(const mat4& left, const vec4& right) {
			return left.Multiply(right);
		}
	};
}
