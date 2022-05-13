#pragma once
//#include "CImg.h"
#include "figure.h"
#include "Factory.h"
#include "function.h"
//using namespace cimg_library;



int main() {
	parameters PRM;
	
	vector<figure*> Figures; 
	string file;

//	cout << "Enter file with parametrs: ";
//	cin >> file;
	file = "param.txt";
	param_from_file(file, PRM);

//	cout << "Enter file with objects: ";
//	cin >> file;
	file = "figure.txt";
	Figures = create_arr_of_figure_in_simplified_coordinates(file, PRM);
	drow_figures(Figures, PRM);
	//Vector light(-2, -2, 2), mode(1,0,0), c(2,2,1), a1(1,1,-1), a2(1,-1,1), a3(1,3,4),
	//	R(1,0,0);
	//drow_tetrah(600, 800, 6, 1, light, mode,a1,  a2,  a3,  c, 0);
	///*drow_sphere(600, 800, 6, 1, light, mode, R, a2, a3, c, 0);*/
	return 0;
}


//
//int square() {
//	int h_per = 500, w_per = 800;
//	float w = 0, h = 0, dw = 0, dh = 0, a0 = 3;
//	float alpha = 2;
//	float tg = 0;
//
//	tg = tan(0.5 * alpha);
//	h = 2 * a0 * tg;
//	w = w_per * h / h_per;
//	dh = h / h_per;
//	dw = w / w_per;
//	Vector lamp(1, 2, -1);
//
//	uint32_t ww = 800;
//	uint32_t hh = 500;
//	// Create a BMP image in memory, modify it, save it on disk
//	BMP bmp2(ww, hh);
//	bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);
//
//	for (int i = 0; i < hh; i++) {                 // axes
//		bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
//	}
//	for (int i = 0; i < ww; i++) {
//		bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
//	}
//	/*for (int i = 0; i < 800; i++) {
//		for (int j = 0; j < 500; j++) {
//			bmp2.set_pixel(i, j, 200, i , j , 255);
//		}
//	}*/
//	Vector normal, g;
//	Vector null, P;
//	int color;
//	Vector c(0, 0, 0);
//	Vector a1(1, 1, -1);
//	Vector a2(0, 1, 1);
//	Vector a3(0, -1, 1);
//	Vector a0v(-a0, 0, 0);
//	Matrix A(a1, a2, a3);
//	float a = A.det();
//	float cos_a_l = 0;
//	A = A.inverse();
////	parallelepiped PAR(c, a1, a2, a3, a0v);
//	line l(-a0, 0, 0, 1, 0, 0);
//	float z = -h / 2 + dh;
//	float y = -w / 2 + dw;
//	for (int i = 0; i < w_per; i++) {
//		for (int j = 0; j < h_per; j++) {
//			l.set_e(a0, y, z);
//			if (z > 0 && y > 0 && z < 1 && y > z) {
//
//				//cout << " ";
//			}
//			if (z > 0 && y > 0 && z < 1 && y < z) {
//
//				cout << "";
//			}
//		//	cos_a_l = PAR.intersection_and_angle(l, lamp);
//			if (cos_a_l != 10) {   //place for intesection function
//				if (cos_a_l > 0) {
//					color = int(200 * cos_a_l);
//					bmp2.set_pixel(i, j, 55 + color, 55 + color, 55 + color, 255);
//				}
//				if (cos_a_l <= 0) {
//					bmp2.set_pixel(i, j, 55, 55, 55, 255);
//				}
//				bmp2.set_pixel(i, j, 255, 20, 20, 255);
//			}
//			z += dh;
//		}
//		z = -h / 2 + dh;
//		y += dw;
//		//cout << i << endl;
//	}
//	bmp2.write("img_test.bmp");
//	return 0;
//}
//
//int circle() {
//	int h_per = 500, w_per = 800;
//	float w = 0, h = 0, dw = 0, dh = 0, a0 = 1;
//	float alpha = 2;
//	float tg = 0;
//
//	tg = tan(0.5 * alpha);
//	h = 2 * a0 * tg;
//	w = w_per * h / h_per;
//	dh = h / h_per;
//	dw = w / w_per;
//
//	int color = 100;
//	float av = 0;//angle ray from lamp and normal
//
//	Vector f;// tools without meaning
//	Vector g;
//
//	Vector lamp(0, 2, 2);
//	Vector centre(1, 0, 0);
//	sphere s(centre, 1);
//	uint32_t ww = 800;
//	uint32_t hh = 500;
//
//	// Create a BMP image in memory, modify it, save it on disk
//	BMP bmp2(w_per, h_per);
//	bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);
//
//
//	/*for (int i = 0; i < 800; i++) {
//		for (int j = 0; j < 500; j++) {
//			bmp2.set_pixel(i, j, 200, i , j , 255);
//		}
//	}*/
//	line l(-a0, 0, 0, 1, 0, 0);
//	float z = -h / 2 + dh;
//	float y = -w / 2 + dw;
//	float min = 1;
//	for (int i = 0; i < w_per; i++) {
//		for (int j = 0; j < h_per; j++) {
//			l.set_e(a0, y, z);
//			if (s.intersection(l)[0] != -1) {
//				if (z > 0.05 || y > 0.05) {
//					cout << " ";
//				}
//				f.set(0, y, z);
//				g = lamp - f;
//				f = f - centre;
//				av = f.cos_angle(g);
//				if (av > 0) {
//					color = int(200 * av);
//
//					bmp2.set_pixel(i, j, 55 + color, 55 + color, 55 + color, 255);
//				}
//				if (av <= 0) {
//					bmp2.set_pixel(i, j, 55, 55, 55, 255);
//				}
//
//			}
//			z += dh;
//		}
//		z = -h / 2 + dh;
//		y += dw;
//		//cout << i << endl;
//	}
//	//for (int i = 0; i < hh; i++) {                 // axes
//	//	bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
//	//}
//	//for (int i = 0; i < ww; i++) {
//	//	bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
//	//}
//	bmp2.write("img_test.bmp");
//	return 0;
//
//
//}
//

/*int main() {
	BMP bmp9("t1_24.bmp");
	bmp9.fill_region(0, 0, 50, 50, 0, 0, 255, 255);
	bmp9.fill_region(150, 0, 100, 150, 0, 255, 0, 255);
	bmp9.write("t1_24_copy.bmp");

	BMP bmp10("t2_24.bmp");
	bmp10.fill_region(0, 0, 50, 50, 0, 0, 255, 255);
	bmp10.fill_region(150, 0, 100, 150, 0, 255, 0, 255);
	bmp10.write("t2_24_copy.bmp");

	BMP bmp5("Shapes_24.bmp");
	bmp5.fill_region(0, 0, 100, 200, 0, 0, 255, 255);
	bmp5.fill_region(150, 0, 209, 203, 0, 255, 0, 255);
	bmp5.write("Shapes_24_copy.bmp");

	// Read an image from disk and write it back:
	BMP bmp("Shapes.bmp");
	bmp.fill_region(0, 0, 100, 200, 0, 0, 255, 255);
	bmp.write("Shapes_copy.bmp");

	// Create a BMP image in memory, modify it, save it on disk
	BMP bmp2(800, 600);
	bmp2.fill_region(0, 0, 800, 600, 0, 0, 255, 255);
	for (int i = 0, j = 0; i < 600; i++, j++) {
		bmp2.set_pixel(i, j, 255, 0, 0, 255);
	}
	bmp2.write("img_test.bmp");

	
	// Create a 24 bits/pixel BMP image in memory, modify it, save it on disk
	BMP bmp3(200, 200, false);
	bmp3.fill_region(50, 20, 100, 100, 255, 0, 255, 255);
	bmp3.write("img_test_24bits.bmp");

	BMP bmp4("img_test_24bits.bmp");
	bmp4.write("img_test_24bits_2.bmp");

	BMP bmp6(403, 305, false);
	bmp6.fill_region(0, 0, 50, 50, 0, 0, 255, 0);
	bmp6.write("test6.bmp");

	BMP bmp7("test6.bmp");
	bmp7.fill_region(0, 0, 40, 40, 255, 0, 0, 0);
	bmp7.write("test6_2.bmp");

	BMP bmp8(200, 200, false);
	bmp8.fill_region(0, 0, 100, 100, 255, 0, 255, 255);
	bmp8.write("img_test_24bits_3.bmp");

	BMP bmp11("test_pnet.bmp");
	bmp11.fill_region(0, 0, 100, 100, 255, 0, 255, 255);
	bmp11.write("test_pnet_copy.bmp");
}*/


/*
int main() {
	int h_per = 500, w_per = 800;
	float w = 0, h = 0, dw = 0, dh = 0, a0 = 3;
	float alpha = 2;
	float tg = 0;

	tg = tan(0.5 * alpha);
	h = 2 * a0 * tg;
	w = w_per * h / h_per;
	dh = h / h_per;
	dw = w / w_per;

	uint32_t ww = 800;
	uint32_t hh = 500;
	// Create a BMP image in memory, modify it, save it on disk
	BMP bmp2(ww, hh);
	bmp2.fill_region(0, 0, ww, hh, 200, 220, 255, 255);

	for (int i = 0; i < hh; i++) {                 // axes
		bmp2.set_pixel(ww / 2, i, 0, 0, 20, 20);
	}
	for (int i = 0; i < ww; i++) {
		bmp2.set_pixel(i, hh / 2, 20, 0, 0, 20);
	}
	
	Vector c(0, 0, 0);
	Vector a1(1, 1, -1);
	Vector a2(0, 1, 1);
	Vector a3(0, -1, 1);
	Vector a0v(-a0, 0, 0);
	Matrix A(a1, a2, a3);
	float a = A.det();
	A = A.inverse();
	parallelepiped PAR(c, a1, a2, a3, a0v);
	line l(-a0, 0, 0, 1, 0, 0);
	float z = -h / 2 + dh;
	float y = -w / 2 + dw;
	for (int i = 0; i < w_per; i++) {
		for (int j = 0; j < h_per; j++) {
			l.set_e(a0, y, z);
			if (z > 0 && y > 0 && z < 1 && y > z) {

				//cout << " ";
			}
			if (z > 0 && y > 0 && z < 1 && y < z) {

				cout << "";
			}
			if (PAR.intersection(l) == 1) {   //place for intesection function

				bmp2.set_pixel(i, j, 255, 20, 20, 255);
			}
			z += dh;
		}
		z = -h / 2 + dh;
		y += dw;
		//cout << i << endl;
	}
	bmp2.write("img_test.bmp");
	return 0;
}*/