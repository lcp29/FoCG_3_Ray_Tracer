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
#define ENABLE_SHADOW 1<<3
#define ENABLE_MIRROR 1<<4

#define SX 1280
#define SY 960

constexpr double epsilon = 1e-8;

class RayTracer
{
	// �ӿڹ̶����ֱ���SXxSY�����Ӧu->y, v->x, w->-z��d = 0.1, fovX = 90��
public:
	RayTracer();
	~RayTracer();
	void draw();
	RGB render(const Ray& ray);
	RGB render_nomirror(const Ray& r, Eigen::Vector3d& pos, Eigen::Vector3d& nor, Texture& t);
	void addSurface(const Sphere& s);
	void addPtls(const PointLight& p);
	unsigned enbflag;
	RGB getPixel(int x, int y);
	RGB Ia;
	void setCamera(const Eigen::Vector3d& e, const Eigen::Vector3d& u, const Eigen::Vector3d& v);
private:
	Eigen::Vector3d e, u, v;		//�������
	RGB* vbuf[SX];	               // ��Ļ����SXxSY
	std::vector<Surface*> surfaces; // ����ȾͼԪ
	std::vector<PointLight> ptls;  // ���Դ
	double dimco;				   // ���ȹ�һ��ϵ��
	double l, b;				   // left, bottom
	RGB bgcolor;
	Ray genRay(Eigen::Vector3d e, Eigen::Vector3d v, Eigen::Vector3d w, int i, int j);
	bool hit(const Ray& r, bool cal_int, Eigen::Vector3d& pos, Eigen::Vector3d& norm, Texture& te);
};

