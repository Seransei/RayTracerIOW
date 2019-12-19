#pragma once
#include "Hittable.h"
#include "Random.h"

int box_x_compare(const void* a, const void* b) {
	AABB boxLeft, boxRight;
	Hittable* ah = *(Hittable**)a;
	Hittable* bh = *(Hittable**)b;

	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		std::cerr << "no bounding box in BVHNode constructor\n";

	if (boxLeft.min.x() - boxRight.min.x() < 0.0f)
		return -1;
	else
		return 1;
}

int box_y_compare(const void* a, const void* b) {
	AABB boxLeft, boxRight;
	Hittable* ah = *(Hittable**)a;
	Hittable* bh = *(Hittable**)b;

	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		std::cerr << "no bounding box in BVHNode constructor\n";

	if (boxLeft.min.y() - boxRight.min.y() < 0.0f)
		return -1;
	else
		return 1;
}

int box_z_compare(const void* a, const void* b) {
	AABB boxLeft, boxRight;
	Hittable* ah = *(Hittable**)a;
	Hittable* bh = *(Hittable**)b;

	if (!ah->boundingBox(0, 0, boxLeft) || !bh->boundingBox(0, 0, boxRight))
		std::cerr << "no bounding box in BVHNode constructor\n";

	if (boxLeft.min.z() - boxRight.min.z() < 0.0f)
		return -1;
	else
		return 1;
}

class BVHNode : public Hittable
{
public:
	Hittable* left;
	Hittable* right;
	AABB box;

	BVHNode(){}
	BVHNode(Hittable** l, int n, float t0, float t1);

	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const;
	virtual bool boundingBox(float t0, float t1, AABB& box) const;
};

bool BVHNode::boundingBox(float t0, float t1, AABB& b) const
{
	b = box;
	return true;
}

BVHNode::BVHNode(Hittable** list, int n, float t0, float t1)
{
	int axis = int(3 * randomDouble());

	if (axis == 0)
		qsort(list, n, sizeof(Hittable*), box_x_compare);
	else if (axis == 1)
		qsort(list, n, sizeof(Hittable*), box_y_compare);
	else
		qsort(list, n, sizeof(Hittable*), box_z_compare);

	if (n == 1) {
		left = right = list[0];
	}
	else if (n == 2) {
		left = list[0];
		right = list[1];
	}
	else {
		left = new BVHNode(list, n / 2, t0, t1);
		right = new BVHNode(list + n / 2, n - n / 2, t0, t1);
	}

	AABB boxLeft, boxRight;

	if (!left->boundingBox(t0, t1, boxLeft) ||
		!right->boundingBox(t0, t1, boxRight)) {

		std::cerr << "no bounding box in BVHNode constructor\n";
	}

	box = surroundingBox(boxLeft, boxRight);
}

bool BVHNode::hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const
{
	if (box.hit(r, t_min, t_max))
	{
		HitRecord leftRec, rightRec;
		bool hitLeft = left->hit(r, t_min, t_max, leftRec);
		bool hitRight = right->hit(r, t_min, t_max, rightRec);
		if (hitLeft && hitRight)
		{
			if (leftRec.t < rightRec.t)
				hrec = leftRec;
			else
				hrec = rightRec;
			return true;
		}
		else if (hitLeft)
		{
			hrec = leftRec;
			return true;
		}
		else if (hitRight) 
		{
			hrec = rightRec;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}