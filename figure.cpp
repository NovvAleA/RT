#pragma once
#include "figure.h"
#include <chrono>

 int drow_parall(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	Vector a1, Vector a2, Vector a3, Vector c, int color) {
	if (abs(a1.scalar(a2) + a2.scalar(a1) + a3.scalar(a1)) > 0) {
		cout << "a1,a2,a3 aren't orthogonal";
	}
//	float par_f[10];
//	Vector par_v[10];
	float w = 0, h = 0, dw = 0, dh = 0;
	float tg = 0;

	tg = tan(0.5 * alpha);
	h = 2 * a0 * tg;
	w = w_per * h / h_per;
	dh = h / h_per;
	dw = w / w_per;

	uint32_t ww = uint32_t(w_per);
	uint32_t hh = uint32_t(h_per);
	// Create a BMP image in memory, modify it, save it on disk
	BMP bmp2(ww, hh);
	bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);

	if (mode[0] == 1) {//drow axes
		for (int i = 0; i < hh; i++) {
			bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
		}
		for (int i = 0; i < ww; i++) {
			bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
		}
	}


	Vector a0v(-a0, 0, 0);
	float cos_a_l = 0;

	parallelepiped PAR(c, a1, a2, a3, a0v);
	line l(-a0, 0, 0, 1, 0, 0);
	float z = -h / 2 + dh;
	float y = -w / 2 + dw;
	for (int i = 0; i < w_per; i++) {
		for (int j = 0; j < h_per; j++) {
			l.set_e(a0, y, z);
			/*if (z > 0 && y > 0 && z < 1 && y < z) {
				cout << "";
			}*/
			cos_a_l = PAR.intersection_and_angle(l, lamp);
			if (cos_a_l != 10) {   //place for intesection function
				if (cos_a_l > 0) {
					color = int(200 * cos_a_l);
					bmp2.set_pixel(i, j, 55 + color, 55 + color, 55 + color, 255);
				}
				if (cos_a_l <= 0) {
					bmp2.set_pixel(i, j, 55, 55, 55, 255);
				}
				//	bmp2.set_pixel(i, j, 255, 20, 20, 255);
			}
			z += dh;
		}
		z = -h / 2 + dh;
		y += dw;
		//cout << i << endl;
	}
	bmp2.write("img_test.bmp");
	return 0;
}

 int drow_tetrah(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	 Vector a1, Vector a2, Vector a3, Vector c, int color) {
	 if (abs(a1.scalar(a2) + a2.scalar(a1) + a3.scalar(a1)) > 0) {
		 cout << "a1,a2,a3 aren't orthogonal";
	 }
//	 float par_f[10];
//	 Vector par_v[10];
	 float w = 0, h = 0, dw = 0, dh = 0;
	 float tg = 0;

	 tg = tan(0.5 * alpha);
	 h = 2 * a0 * tg;
	 w = w_per * h / h_per;
	 dh = h / h_per;
	 dw = w / w_per;

	 uint32_t ww = uint32_t(w_per);
	 uint32_t hh = uint32_t(h_per);
	 // Create a BMP image in memory, modify it, save it on disk
	 BMP bmp2(ww, hh);
	 bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);

	 if (mode[0] == 1) {//drow axes
		 for (int i = 0; i < hh; i++) {
			 bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
		 }
		 for (int i = 0; i < ww; i++) {
			 bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
		 }
	 }


	 Vector a0v(-a0, 0, 0);
	 float cos_a_l = 0;

	 tetrahedron TETR(c, a1, a2, a3, a0v);
	 line l(-a0, 0, 0, 1, 0, 0);
	 float z = -h / 2 + dh;
	 float y = -w / 2 + dw;
	 for (int i = 0; i < w_per; i++) {
		 for (int j = 0; j < h_per; j++) {
			 l.set_e(a0, y, z);
			 /*if (z > 0 && y > 0 && z < 1 && y < z) {
				 cout << "";
			 }*/
			 cos_a_l = TETR.intersection_and_angle(l, lamp);
			 if (cos_a_l != 10) {   //place for intesection function
				 if (cos_a_l > 0) {
					 color = int(200 * cos_a_l);
					 bmp2.set_pixel(i, j, 55 + color, 55 + color, 55 + color, 255);
				 }
				 if (cos_a_l <= 0) {
					 bmp2.set_pixel(i, j, 55, 55, 55, 255);
				 }
				 //	bmp2.set_pixel(i, j, 255, 20, 20, 255);
			 }
			 z += dh;
		 }
		 z = -h / 2 + dh;
		 y += dw;
		 //cout << i << endl;
	 }
	 bmp2.write("img_test.bmp");
	 return 0;
 }

 int drow_sphere(int h_per, int w_per, float a0, float alpha, Vector lamp, Vector mode,
	 Vector R_0_0, Vector null_1, Vector null_2, Vector c, int color) {
	float w = 0, h = 0, dw = 0, dh = 0;
	float tg = 0;
	float cos_a_l = 0;
	 
	tg = tan(0.5 * alpha);
	h = 2 * a0 * tg;
	w = w_per * h / h_per;
	dh = h / h_per;
	dw = w / w_per;
	 
	float av = 0;//angle ray from lamp and normal
	 
	Vector f;// tools without meaning
	Vector g;
	 
	

	uint32_t ww = uint32_t(w_per);
	uint32_t hh = uint32_t(h_per);
	 
	// Create a BMP image in memory, modify it, save it on disk
	BMP bmp2(w_per, h_per);
	bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);
	 
	 
	/*for (int i = 0; i < 800; i++) {
	 	for (int j = 0; j < 500; j++) {
	 		bmp2.set_pixel(i, j, 200, i , j , 255);
	 	}
	}*/
	sphere SPH(c, R_0_0[0], a0);
	line l(-a0, 0, 0, 1, 0, 0);
	float z = -h / 2 + dh;
	float y = -w / 2 + dw;
	
	for (int i = 0; i < w_per; i++) {
		for (int j = 0; j < h_per; j++) {
			l.set_e(a0, y, z);
			/*if (z > 0 && y > 0 && z < 1 && y < z) {
				cout << "";
			}*/
			cos_a_l = SPH.intersection_and_angle(l, lamp);
			if (cos_a_l != 10) {   //place for intesection function
				if (cos_a_l > 0) {
					color = int(200 * cos_a_l);
					bmp2.set_pixel(i, j, 55 + color, 55 + color, 55 + color, 255);
				}
				if (cos_a_l <= 0) {
					bmp2.set_pixel(i, j, 55, 55, 55, 255);
				}
				//	bmp2.set_pixel(i, j, 255, 20, 20, 255);
			}
			z += dh;
		}
		z = -h / 2 + dh;
		y += dw;
		//cout << i << endl;
	}
	//for (int i = 0; i < hh; i++) {                 // axes
	//	bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
	//}
	//for (int i = 0; i < ww; i++) {
	//	bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
	//}
	bmp2.write("img_test.bmp");
	return 0;
 }

 int drow_figures(vector<figure*> arr, parameters& PRM) {
	 Vector lamp = PRM.lamp;
	 float w = 0, h = 0, dw = 0, dh = 0;
	 float tg = 0;
	 float a0 = PRM.a0;
	 int h_per = PRM.height;
	 int w_per = PRM.width;
	 tg = tan(0.5 * PRM.alpha);
	 h = 2 * a0 * tg;
	 w = w_per * h / h_per;
	 dh = h / h_per;
	 dw = w / w_per;

	 uint32_t ww = uint32_t(w_per);
	 uint32_t hh = uint32_t(h_per);
	 //// Create a BMP image in memory, modify it, save it on disk
	 //BMP bmp2(ww, hh);
	 //bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);
	 BMP bmp2("space.bmp");

	 //if (1 == 1) {//drow axes
		// for (int i = 0; i < hh; i++) {
		//	 bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
		// }
		// for (int i = 0; i < ww; i++) {
		//	 bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
		// }
	 //}

	 int dim = arr.size();
	 Vector_and_cos tmp_P;
	 vector<Vector_and_cos> points(dim);
	 Vector a0v(-a0, 0, 0);
	 float cos_a_l = 0;
	 int color = 0;
	 int ind = 0;
	 line l(-a0, 0, 0, 1, 0, 0);
	 float z = -h / 2 + dh;
	 float y = -w / 2 + dw;

	 auto start_for = std::chrono::steady_clock::now();
     
	 for (int i = 0; i < w_per; i++) {
     //    #pragma omp parallel for
		 for (int j = 0; j < h_per; j++) {
			 l.set_e(a0, y, z);
             
			 for (int i1 = 0; i1 < dim; i1++) {
				 points[i1] = arr[i1]->point_and_angle(l, lamp);
			 }
			 
			 ind = nearest_from_point(points);
			 tmp_P = points[ind];
			 cos_a_l = tmp_P.cos;
			 if (cos_a_l != 10) {   //place for intesection function
				 if (cos_a_l > 0) {
					 color = abs(int(180 * cos_a_l));
					 bmp2.set_pixel(i, j,50 + color,20 + color*1,40 + color, 230);//
				 }
				 if (cos_a_l <= 0) {
					 bmp2.set_pixel(i, j, 50, 20,40, 230);
				 }
				 //	bmp2.set_pixel(i, j, 255, 20, 20, 255);
			 }
			 z += dh;
		 }
		 z = -h / 2 + dh;
		 y += dw;
		 //cout << i << endl;
	 }
	 auto end_for = std::chrono::steady_clock::now();
	 cout << "time: " << chrono::duration<double, milli>(end_for - start_for).count() << " ms" << "\n";
	
	 bmp2.write("img_test.bmp");
	 return 0;

 }

 int nearest_from_point(vector<Vector_and_cos> arr) {
	 size_t k = 0;
	 for (size_t i = 0; i < arr.size(); i++) {
		 if (arr[i].cos == 10) {
			 arr[i].P[0] = 10000;
		 }
	 }
	 float min = arr[0].P[0];
	 for (size_t i = 0; i < arr.size(); i++) {
		 if (arr[i].P[0] < min) {
			 min = arr[i].P[0];
			 k = i;
		 }
	 }
	 return (int)k;
 }

//parallelepiped::parallelepiped(Vector c, Vector a1, Vector a2, Vector a3, Vector a0) {
//	constv_m1_0_0.set(-1, 0, 0);
//	constv_1_0_0.set(1, 0, 0);
//	counter = 0;
//	centre = c;
//	axe1 = a1;
//	axe2 = a2;
//	axe3 = a3;
//	camera = a0;
//	Vector tmp;  // service vector
//
//	tmp = axe1 - centre;
//	edge[0] = tmp.module();
//	tmp = axe2 - centre;
//	edge[1] = tmp.module();
//	tmp = axe3 - centre;
//	edge[2] = tmp.module();
//
//	A = centre;   // 'center' is vertice A, not on a center of cube	
//	B = A + axe1;//vertices
//	D = A + axe2;
//	C = D + axe1;
//	A1 = A + axe3;
//	B1 = B + axe3;
//	C1 = C + axe3;
//	D1 = D + axe3;
//
//	simplex[0][0] = A; // triples of numbers are oriented for a vector product
//	simplex[0][1] = B;
//	simplex[0][2] = C;
//
//	simplex[1][0] = B;
//	simplex[1][1] = C;
//	simplex[1][2] = D;
//
//	simplex[2][0] = B1;
//	simplex[2][1] = B;
//	simplex[2][2] = A;
//
//	simplex[3][0] = A;
//	simplex[3][1] = A1;
//	simplex[3][2] = B1;
//
//	simplex[4][0] = A;
//	simplex[4][1] = D;
//	simplex[4][2] = D1;
//
//	simplex[5][0] = D1;
//	simplex[5][1] = A1;
//	simplex[5][2] = A;
//
//	simplex[6][0] = C1;
//	simplex[6][1] = B1;
//	simplex[6][2] = A1;
//
//	simplex[7][0] = A1;
//	simplex[7][1] = D1;
//	simplex[7][2] = C1;
//
//	simplex[8][0] = C1;
//	simplex[8][1] = D1;
//	simplex[8][2] = D;
//
//	simplex[9][0] = D;
//	simplex[9][1] = C;
//	simplex[9][2] = C1;
//
//	simplex[10][0] = B;
//	simplex[10][1] = B1;
//	simplex[10][2] = C1;
//
//	simplex[11][0] = C1;
//	simplex[11][1] = C;
//	simplex[11][2] = B;
//
//	for (int i = 0; i < 12; i++) {
//		Ji[i] = J_minus_one(simplex[i][0] - camera, simplex[i][1] - camera, simplex[i][2] - camera);
//		tmp = simplex[i][0] - simplex[i][1];
//		normal[i] = tmp.cross(simplex[i][2] - simplex[i][1]);
//	}
//}
