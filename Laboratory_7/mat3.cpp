#pragma once
#include <algorithm>
#include <iostream>
#include "vec3.h"
#include "mat3.h"
#include <math.h>

namespace egc
{
	float& mat3::at(int i, int j)
	{
		return this->matrixData[3 * j + i];
	}

	const float& mat3::at(int i, int j) const {
		return this->matrixData[3 * j + i];
	}

	mat3& mat3::operator =(const mat3& srcMatrix)
	{
		for (int i = 0; i < 9; i++)
		{
			this->matrixData[i] = srcMatrix.matrixData[i];
		}
		return *this;
	}

}