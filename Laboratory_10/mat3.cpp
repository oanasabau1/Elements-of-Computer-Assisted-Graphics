#include"mat3.h"

namespace egc {

	mat3& mat3::operator =(const mat3& srcMatrix) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				this->at(i, j) = srcMatrix.at(i, j);
			}
		return *this;
	}

	mat3 mat3::operator *(float scalarvalue) const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = this->at(i, j) * scalarvalue;
			}
		return m;
	}

	mat3 mat3::operator *(const mat3& srcmatrix) const {
		mat3 m;
		float sum = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					sum += this->at(i, k) * srcmatrix.at(k, j);
				}
				m.at(i, j) = sum;
				sum = 0;
			}
		}
		return m;
	}

	vec3 mat3::operator *(const vec3& srcvector) const {
		vec3 result;
		result.x = this->at(0, 0) * srcvector.x + this->at(0, 1) * srcvector.y + this->at(0, 2) * srcvector.z;
		result.y = this->at(1, 0) * srcvector.x + this->at(1, 1) * srcvector.y + this->at(1, 2) * srcvector.z;
		result.z = this->at(2, 0) * srcvector.x + this->at(2, 1) * srcvector.y + this->at(2, 2) * srcvector.z;
		return result;
	}

	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		return m;
	}

	//get element by (row, column)
	float& mat3::at(int i, int j) {
		return matrixData[3 * j + i];
	}

	const float& mat3::at(int i, int j) const {
		return matrixData[3 * j + i];
	}

	float mat3::determinant() const {
		float det = this->at(0, 0) * this->at(1, 1) * this->at(2, 2) +
			this->at(1, 0) * this->at(2, 1) * this->at(0, 2) +
			this->at(0, 1) * this->at(1, 2) * this->at(2, 0) -
			this->at(0, 2) * this->at(1, 1) * this->at(2, 0) -
			this->at(0, 1) * this->at(1, 0) * this->at(2, 2) -
			this->at(1, 2) * this->at(2, 1) * this->at(0, 0);
		return det;
	}

	mat3 mat3::inverse() const {
		mat3 m;
		float sum = determinant();

		m.at(0, 0) = this->at(1, 1) * this->at(2, 2) - this->at(1, 2) * this->at(2, 1);
		m.at(0, 1) = (-1) * (this->at(0, 1) * this->at(2, 2) - this->at(2, 1) * this->at(0, 2));
		m.at(0, 2) = this->at(0, 1) * this->at(1, 2) - this->at(1, 1) * this->at(0, 2);
		m.at(1, 0) = (-1) * (this->at(1, 0) * this->at(2, 2) - this->at(1, 2) * this->at(2, 0));
		m.at(1, 1) = this->at(0, 0) * this->at(2, 2) - this->at(0, 2) * this->at(2, 0);
		m.at(1, 2) = (-1) * (this->at(0, 0) * this->at(1, 2) - this->at(1, 0) * this->at(0, 2));
		m.at(2, 0) = this->at(1, 0) * this->at(2, 1) - this->at(2, 0) * this->at(1, 1);
		m.at(2, 1) = (-1) * (this->at(0, 0) * this->at(2, 1) - this->at(0, 1) * this->at(2, 0));
		m.at(2, 2) = this->at(1, 1) * this->at(0, 0) - this->at(1, 0) * this->at(0, 1);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				m.at(i, j) = m.at(i, j) / determinant();
			}

		return m;
	}

	mat3 mat3::transpose() const {
		mat3 m;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				m.at(i, j) = this->at(j, i);
			}
		return m;
	}


}