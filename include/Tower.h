#pragma once
#include "Entity.h"

class Tower : public Entity
{
protected:
	float damage;
	float attackSpeed;
	float turnSpeed;
};