#include "entity.h"

inline const XMFLOAT4X4 Entity::getPosition() const { return position; }

inline void Entity::setPosition(XMFLOAT4X4 position) {
	this->position = position;
}

inline void Entity::setScaling(XMFLOAT4X4 scaling) {
	this->scaling = scaling;
}

inline void Entity::setRotation(XMFLOAT4X4 rotation) {
	this->rotation = rotation;
}

void Entity::addIntermediateTransformation(XMMATRIX transformation) {
	XMFLOAT4X4 trans;
	XMStoreFloat4x4(&trans, transformation);
	transformations.push_back(trans);
}