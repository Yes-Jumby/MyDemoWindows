#pragma once
#ifndef CLOUD_H
#define CLOUD_H

enum class PointCloudType{
    POINTXYZ,               //cloud contain x y z
    POINTXYZNORMAL,         //cloud contain x y z normal
    POINTXYZGRAY,           //cloud contain x y z gray(intensity)
    POINTXYZDIVERSE         //cloud contain x y z diverse
};

struct Cloud3D{
	Cloud3D()
		:cols(0),rows(1),cloud_size(0),
         minx(0.0),miny(0.0),minz(0.0),dx(0.0),dy(0.0), maxx(0.0), maxy(0.0), maxz(0.0),
		 point_type(PointCloudType::POINTXYZGRAY){}
	~Cloud3D() {}
    double minx;            //min x of cloud
    double miny;            //min y of cloud
    double minz;            //min z of cloud
    double maxx;            //max x of cloud
    double maxy;            //max y of cloud
    double maxz;            //max z of cloud
    double dx;              //resolution of Axis x
    double dy;              //resolution of Axis y
    unsigned long cols;     //cols of cloud in x&y coordinate
    unsigned long rows;     //rows of cloud in x&y coordinate
    unsigned long cloud_size;//size of cloud
    PointCloudType point_type;//type of cloud
};

#endif //!CLOUD_H
