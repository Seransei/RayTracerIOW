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
	BVHNode(Hittable** l, int n, float time0, float time1);

	virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& hrec) const;
	virtual bool boundingBox(float t0, float t1, AABB& box) const;
};

bool BVHNode::boundingBox(float t0, float t1, AABB& b) const
{
	b = box;
	return true;
}

BVHNode::BVHNode(Hittable** l, int n, float time0, float time1)
{
	int axis = int(3 * randomDouble());

	if (axis == 0)
		qsort(l, n, sizeof(Hittable*), box_x_compare);
	else if (axis == 1)
		qsort(l, n, sizeof(Hittable*), box_y_compare);
	else
		qsort(l, n, sizeof(Hittable*), box_z_compare);

	if (n == 1) {
		left = right = l[0];
	}
	else if (n == 2) {
		left = l[0];
		right = l[1];
	}
	else {
		left = new BVHNode(l, n / 2, time0, time1);
		right = new BVHNode(l + n / 2, n - n / 2, time0, time1);
	}

	AABB boxLeft, boxRight;

	if (!left->boundingBox(time0, time1, boxLeft) ||
		!right->boundingBox(time0, time1, boxRight)) {

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
			hrec = rightRec;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}