#pragma once
#include "Types.hpp"
inline float DistanceBetweenVector3(NativeVector3* pointA, NativeVector3* pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}
inline NativeVector3 addn(NativeVector3* vectorA, NativeVector3* vectorB) {
	NativeVector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}
inline float GetDistanceFloat(NativeVector3 pointA, NativeVector3 pointB) {
	float a_x = pointA.x;
	float a_y = pointA.y;
	float a_z = pointA.z;
	float b_x = pointB.x;
	float b_y = pointB.y;
	float b_z = pointB.z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba * y_ba;
	double x_2 = x_ba * x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}
inline NativeVector3 rot_to_direction(NativeVector3* rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	NativeVector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
inline double DegreeToRadian(double number) {
	return number * 0.017453292519943295;
}
inline NativeVector3 RotationToDirection(NativeVector3 rotation) {
	double radZ = DegreeToRadian(rotation.z);
	double radX = DegreeToRadian(rotation.x);
	double value = cos(radX);
	double final = abs(value);
	rotation.x = (float)(-(float)sin(radZ) * final);
	rotation.y = (float)(cos(radZ) * final);
	rotation.z = (float)sin(radX);
	return rotation;
}

inline NativeVector3 multiply(NativeVector3* vector, float x) {
	NativeVector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

