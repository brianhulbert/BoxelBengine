#include "VoxelGameObject.h"

VoxelGameObject::VoxelGameObject(scene::Scene* scene, unsigned int* voxels, unsigned int width, unsigned int height, unsigned int length) : 
	width(width), height(height), length(length), GameObject(scene, nullptr, "res/shaders/BasicVoxel.shader", nullptr) {

}

VoxelGameObject::~VoxelGameObject() {
	free(voxel_data);
}

VoxelGameObject* VoxelGameObject::CreateVoxelObject(scene::Scene* scene, unsigned int* voxels, unsigned int width, unsigned int height, unsigned int length) {
	return new VoxelGameObject(scene, voxels, width, height, length);
}