#pragma once

#include "GameObject.h"

class VoxelGameObject : public GameObject{
private:
	VoxelGameObject(scene::Scene* scene, unsigned int* voxels, unsigned int width, unsigned int height, unsigned int length);
	unsigned int* voxel_data;
	int width;
	int height;
	int length;
public:
	static VoxelGameObject* CreateVoxelObject(scene::Scene* scene, unsigned int* voxels, unsigned int x, unsigned int y, unsigned int z);
};