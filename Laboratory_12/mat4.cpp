#include"mat4.h"

namespace egc {


	//get element by (row, column)
	float& mat4::at(int i, int j)
	{
		return matrixData[4 * j + i];
	}
	const float& mat4::at(int i, int j) const
	{
		return matrixData[4 * j + i];
	}

	mat4& mat4::operator =(const mat4& srcMatrix)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				this->at(i, j) = srcMatrix.at(i, j);
			}
		return *this;
	}

	mat4 mat4::operator +(const mat4& srcMatrix) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}
		return m;
	}
	mat4 mat4::operator *(float scalarValue) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {

				m.at(i, j) = this->at(i, j) * scalarValue;
			}
		}
		return m;

	}
	mat4 mat4::operator *(const mat4& srcMatrix) const
	{
		mat4 m;
		float sum = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++)
				{
					sum += this->at(i, k) * srcMatrix.at(k, j);
				}
				m.at(i, j) = sum;
				sum = 0;
			}
		}
		return m;
	}
	vec4 mat4::operator *(const vec4& srcVector) const
	{
		vec4 result;
		result.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z + this->at(0, 3) * srcVector.w;
		result.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z + this->at(1, 3) * srcVector.w;
		result.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z + this->at(2, 3) * srcVector.w;
		result.w = this->at(3, 0) * srcVector.x + this->at(3, 1) * srcVector.y + this->at(3, 2) * srcVector.z + this->at(3, 3) * srcVector.w;
		return result;

	}


	float mat4::determinant() const
	{
		return
			at(0, 3) * at(1, 2) * at(2, 1) * at(3, 0) - at(0, 2) * at(1, 3) * at(2, 1) * at(3, 0) -
			at(0, 3) * at(1, 1) * at(2, 2) * at(3, 0) + at(0, 1) * at(1, 3) * at(2, 2) * at(3, 0) +
			at(0, 2) * at(1, 1) * at(2, 3) * at(3, 0) - at(0, 1) * at(1, 2) * at(2, 3) * at(3, 0) -
			at(0, 3) * at(1, 2) * at(2, 0) * at(3, 1) + at(0, 2) * at(1, 3) * at(2, 0) * at(3, 1) +
			at(0, 3) * at(1, 0) * at(2, 2) * at(3, 1) - at(0, 0) * at(1, 3) * at(2, 2) * at(3, 1) -
			at(0, 2) * at(1, 0) * at(2, 3) * at(3, 1) + at(0, 0) * at(1, 2) * at(2, 3) * at(3, 1) +
			at(0, 3) * at(1, 1) * at(2, 0) * at(3, 2) - at(0, 1) * at(1, 3) * at(2, 0) * at(3, 2) -
			at(0, 3) * at(1, 0) * at(2, 1) * at(3, 2) + at(0, 0) * at(1, 3) * at(2, 1) * at(3, 2) +
			at(0, 1) * at(1, 0) * at(2, 3) * at(3, 2) - at(0, 0) * at(1, 1) * at(2, 3) * at(3, 2) -
			at(0, 2) * at(1, 1) * at(2, 0) * at(3, 3) + at(0, 1) * at(1, 2) * at(2, 0) * at(3, 3) +
			at(0, 2) * at(1, 0) * at(2, 1) * at(3, 3) - at(0, 0) * at(1, 2) * at(2, 1) * at(3, 3) -
			at(0, 1) * at(1, 0) * at(2, 2) * at(3, 3) + at(0, 0) * at(1, 1) * at(2, 2) * at(3, 3);

	}
	mat4 mat4::inverse() const
	{
		mat4 m;
		if (determinant() == 0)
			return NULL;

		float invdet = 1 / determinant();
		m.matrixData[0] = matrixData[5] * matrixData[10] * matrixData[15] - matrixData[5] * matrixData[11] * matrixData[14] - matrixData[9] * matrixData[6] * matrixData[15] + matrixData[9] * matrixData[7] * matrixData[14] + matrixData[13] * matrixData[6] * matrixData[11] - matrixData[13] * matrixData[7] * matrixData[10];
		m.matrixData[4] = -matrixData[4] * matrixData[10] * matrixData[15] + matrixData[4] * matrixData[11] * matrixData[14] + matrixData[8] * matrixData[6] * matrixData[15] - matrixData[8] * matrixData[7] * matrixData[14] - matrixData[12] * matrixData[6] * matrixData[11] + matrixData[12] * matrixData[7] * matrixData[10];
		m.matrixData[8] = matrixData[4] * matrixData[9] * matrixData[15] - matrixData[4] * matrixData[11] * matrixData[13] - matrixData[8] * matrixData[5] * matrixData[15] + matrixData[8] * matrixData[7] * matrixData[13] + matrixData[12] * matrixData[5] * matrixData[11] - matrixData[12] * matrixData[7] * matrixData[9];
		m.matrixData[12] = -matrixData[4] * matrixData[9] * matrixData[14] + matrixData[4] * matrixData[10] * matrixData[13] + matrixData[8] * matrixData[5] * matrixData[14] - matrixData[8] * matrixData[6] * matrixData[13] - matrixData[12] * matrixData[5] * matrixData[10] + matrixData[12] * matrixData[6] * matrixData[9];
		m.matrixData[1] = -matrixData[1] * matrixData[10] * matrixData[15] + matrixData[1] * matrixData[11] * matrixData[14] + matrixData[9] * matrixData[2] * matrixData[15] - matrixData[9] * matrixData[3] * matrixData[14] - matrixData[13] * matrixData[2] * matrixData[11] + matrixData[13] * matrixData[3] * matrixData[10];
		m.matrixData[5] = matrixData[0] * matrixData[10] * matrixData[15] - matrixData[0] * matrixData[11] * matrixData[14] - matrixData[8] * matrixData[2] * matrixData[15] + matrixData[8] * matrixData[3] * matrixData[14] + matrixData[12] * matrixData[2] * matrixData[11] - matrixData[12] * matrixData[3] * matrixData[10];
		m.matrixData[9] = -matrixData[0] * matrixData[9] * matrixData[15] + matrixData[0] * matrixData[11] * matrixData[13] + matrixData[8] * matrixData[1] * matrixData[15] - matrixData[8] * matrixData[3] * matrixData[13] - matrixData[12] * matrixData[1] * matrixData[11] + matrixData[12] * matrixData[3] * matrixData[9];
		m.matrixData[13] = matrixData[0] * matrixData[9] * matrixData[14] - matrixData[0] * matrixData[10] * matrixData[13] - matrixData[8] * matrixData[1] * matrixData[14] + matrixData[8] * matrixData[2] * matrixData[13] + matrixData[12] * matrixData[1] * matrixData[10] - matrixData[12] * matrixData[2] * matrixData[9];
		m.matrixData[2] = matrixData[1] * matrixData[6] * matrixData[15] - matrixData[1] * matrixData[7] * matrixData[14] - matrixData[5] * matrixData[2] * matrixData[15] + matrixData[5] * matrixData[3] * matrixData[14] + matrixData[13] * matrixData[2] * matrixData[7] - matrixData[13] * matrixData[3] * matrixData[6];
		m.matrixData[6] = -matrixData[0] * matrixData[6] * matrixData[15] + matrixData[0] * matrixData[7] * matrixData[14] + matrixData[4] * matrixData[2] * matrixData[15] - matrixData[4] * matrixData[3] * matrixData[14] - matrixData[12] * matrixData[2] * matrixData[7] + matrixData[12] * matrixData[3] * matrixData[6];
		m.matrixData[10] = matrixData[0] * matrixData[5] * matrixData[15] - matrixData[0] * matrixData[7] * matrixData[13] - matrixData[4] * matrixData[1] * matrixData[15] + matrixData[4] * matrixData[3] * matrixData[13] + matrixData[12] * matrixData[1] * matrixData[7] - matrixData[12] * matrixData[3] * matrixData[5];
		m.matrixData[14] = -matrixData[0] * matrixData[5] * matrixData[14] + matrixData[0] * matrixData[6] * matrixData[13] + matrixData[4] * matrixData[1] * matrixData[14] - matrixData[4] * matrixData[2] * matrixData[13] - matrixData[12] * matrixData[1] * matrixData[6] + matrixData[12] * matrixData[2] * matrixData[5];
		m.matrixData[3] = -matrixData[1] * matrixData[6] * matrixData[11] + matrixData[1] * matrixData[7] * matrixData[10] + matrixData[5] * matrixData[2] * matrixData[11] - matrixData[5] * matrixData[3] * matrixData[10] - matrixData[9] * matrixData[2] * matrixData[7] + matrixData[9] * matrixData[3] * matrixData[6];
		m.matrixData[7] = matrixData[0] * matrixData[6] * matrixData[11] - matrixData[0] * matrixData[7] * matrixData[10] - matrixData[4] * matrixData[2] * matrixData[11] + matrixData[4] * matrixData[3] * matrixData[10] + matrixData[8] * matrixData[2] * matrixData[7] - matrixData[8] * matrixData[3] * matrixData[6];
		m.matrixData[11] = -matrixData[0] * matrixData[5] * matrixData[11] + matrixData[0] * matrixData[7] * matrixData[9] + matrixData[4] * matrixData[1] * matrixData[11] - matrixData[4] * matrixData[3] * matrixData[9] - matrixData[8] * matrixData[1] * matrixData[7] + matrixData[8] * matrixData[3] * matrixData[5];
		m.matrixData[15] = matrixData[0] * matrixData[5] * matrixData[10] - matrixData[0] * matrixData[6] * matrixData[9] - matrixData[4] * matrixData[1] * matrixData[10] + matrixData[4] * matrixData[2] * matrixData[9] + matrixData[8] * matrixData[1] * matrixData[6] - matrixData[8] * matrixData[2] * matrixData[5];
		return m * invdet;

	}
	mat4 mat4::transpose() const
	{
		mat4 m;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = this->at(j, i);
			}
		return m;
	}
}