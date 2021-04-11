#pragma once
#include "Surface.h"
#include "Ray.h"
#include "RGB.h"
#include "Texture.h"
#include "PointLight.h"
#include "Sphere.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <limits>

#define ENABLE_DIFFUSE 1
#define ENABLE_SPECULAR 1<<1
#define ENABLE_AMBIENT 1<<2
#define ENABLE_MIRROR 1<<3

class RayTracer
{
	// �ӿڹ̶����ֱ���640x480�����Ӧu->y, v->x, w->-z��d = 0.1, fovX = 90��
public:
	RayTracer();
	~RayTracer();
	void draw();
	void addSurface(const Sphere& s);
	void addPtls(const PointLight& p);
	unsigned enbflag;
	RGB getPixel(int x, int y);
	RGB Ia;
private:
	RGB* vbuf[640];	               // ��Ļ����640*480
	std::vector<Surface*> surfaces; // ����ȾͼԪ
	std::vector<PointLight> ptls;  // ���Դ
	double dimco;				   // ���ȹ�һ��ϵ��
	Eigen::Vector3d d;			   // ���㵽�ӿ�ƽ�����
	double l, b;				   // left, bottom
	RGB bgcolor;
	Ray genRay(int i, int j);
	bool hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te);
};

