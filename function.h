#pragma once
#include "Factory.h"
#include <string>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;

int param_from_file(const string& fname_param, parameters& PRM) {
	ifstream inp;

	string tmp;
   
    float x = 0, y = 0, z = 0;

    inp.open(fname_param);
    while (!inp.eof()) {
        inp >> tmp;

        if (tmp == "camera") {
            inp >> x >> y >> z;
            PRM.camera.set(x, y, z);
        }
        else if (tmp == "normal") {
            inp >> x >> y >> z;
            PRM.normal.set(x, y, z);
        }
        else if (tmp == "up") {
            inp >> x >> y >> z;
            PRM.up.set(x, y, z);
        }
        else if (tmp == "lamp") {
            inp >> x >> y >> z;
            PRM.lamp.set(x, y, z);
        }
        else if (tmp == "a0") {
            inp >> PRM.a0;
        }
        else if (tmp == "limit") {
            inp >> PRM.limit;
        }
        else if (tmp == "alpha") {
            inp >> PRM.alpha;
        }
        else if (tmp == "width") {
            inp >> PRM.width;
        }
        else if (tmp == "height") {
            inp >> PRM.height;
        }
        else { 
            cout << "Error in create_arr_of_figure_from_file! tmp =" << tmp << "\n";
            inp.close();
        }
    }
    inp.close();
    if (PRM.normal.scalar(PRM.up) != 0) {
        cout << " normal*up != 0";
    }
	return 1;
}

vector<figure*> create_arr_of_figure_in_simplified_coordinates( const string& fname_figure, parameters& PRM) {
    vector<figure*> arr;
    map<string, Factory*> factory;
    factory["sphere"] = new Factory_sphere;
    factory["parall"] = new Factory_parallelepiped;
    factory["tetrah"] = new Factory_tetrahedron;


    ifstream inp;

    string tmp;

    if (PRM.a0 == 0) {
        cout << "a0  = 0";
    }

    inp.open(fname_figure);

    while (!inp.eof()) {
        inp >> tmp;
        if (tmp == "sphere" || tmp == "tetrah" || tmp == "parall") {
            Vector ad[4], a0;//center and 3 adges
            a0.set(-PRM.a0, 0, 0);
            for (int i = 0; i < 4; ++i) {
                inp >> ad[i][0] >> ad[i][1] >> ad[i][2];
            }
            arr.push_back(factory[tmp]->Create(ad[0], ad[1], ad[2], ad[3], a0));
            tmp = " ";
        }
       
    }
    inp.close();

    float normal_module = PRM.normal.module();

    vector<figure*>::iterator k;

    //orient the normal along Ox (axe1)

    if (PRM.normal[1] != 0) {
        float fi_z = atan(PRM.normal[1] / PRM.normal[0]);
        Rotation_Matrix Rz(fi_z, 3);
        PRM.camera = Rz * PRM.camera;
        PRM.normal = Rz * PRM.normal;
        PRM.up =     Rz * PRM.up;
        PRM.lamp =   Rz * PRM.lamp;
        for (k = arr.begin(); k != arr.end(); k++) {
            (*k)->TRUcentre = Rz * (*k)->TRUcentre;
            (*k)->TRUaxe1 =   Rz * (*k)->TRUaxe1;
            (*k)->TRUaxe2 =   Rz * (*k)->TRUaxe2;
            (*k)->TRUaxe3 =   Rz * (*k)->TRUaxe3;
            
         //   (*k)->VECTa0 = Rz * (*k)->VECTa0;
        }
    }
  /*  else {
        Swap_Matrix SWAPxy(1, 2);
        PRM.camera = SWAPxy * PRM.camera;
        PRM.normal = SWAPxy * PRM.normal;
        PRM.up = SWAPxy * PRM.up;
        PRM.lamp = SWAPxy * PRM.lamp;
        for (k = arr.begin(); k != arr.end(); k++) {
            (*k)->TRUaxe1 = SWAPxy * (*k)->TRUaxe1;
            (*k)->TRUaxe2 = SWAPxy * (*k)->TRUaxe2;
            (*k)->TRUaxe3 = SWAPxy * (*k)->TRUaxe3;
            (*k)->TRUcentre = SWAPxy * (*k)->TRUcentre;
            (*k)->VECTa0 = SWAPxy * (*k)->VECTa0;
        }
    }*/
    if (abs(normal_module - PRM.normal.module()) > 0.1) {
        cout << "first oops";
    }
    if (PRM.normal[0] != 0) {
        float fi_y = atan(PRM.normal[2] / PRM.normal[0]);
        Rotation_Matrix  Ry(fi_y, 2);
        PRM.camera = Ry * PRM.camera;
        PRM.normal = Ry * PRM.normal;
        PRM.up =     Ry * PRM.up;
        PRM.lamp =   Ry * PRM.lamp;
        for (k = arr.begin(); k != arr.end(); k++) {
            (*k)->TRUcentre = Ry * (*k)->TRUcentre;
            (*k)->TRUaxe1 =   Ry * (*k)->TRUaxe1;
            (*k)->TRUaxe2 =   Ry * (*k)->TRUaxe2;
            (*k)->TRUaxe3 =   Ry * (*k)->TRUaxe3;
           
        //    (*k)->VECTa0 = Ry * (*k)->VECTa0;
        }
    }
    else {
        Swap_Matrix SWAPxz(1, 3);
        PRM.camera = SWAPxz * PRM.camera;
        PRM.normal = SWAPxz * PRM.normal;
        PRM.up =     SWAPxz * PRM.up;
        PRM.lamp =   SWAPxz * PRM.lamp;
        for (k = arr.begin(); k != arr.end(); k++) {
            (*k)->TRUcentre = SWAPxz * (*k)->TRUcentre;
            (*k)->TRUaxe1 =   SWAPxz * (*k)->TRUaxe1;
            (*k)->TRUaxe2 =   SWAPxz * (*k)->TRUaxe2;
            (*k)->TRUaxe3 =   SWAPxz * (*k)->TRUaxe3;
         //   (*k)->VECTa0 = SWAPxz * (*k)->VECTa0;
        }
    }


    //orient the up along Oz (axe3)
    if (PRM.up[1] != 0) {
        float fi_x = -1.57 + atan(PRM.up[2]/ PRM.up[1]);
        Rotation_Matrix  Rx(fi_x, 1);
        PRM.camera = Rx * PRM.camera;
        PRM.normal = Rx * PRM.normal;
        PRM.up = Rx * PRM.up;
        PRM.lamp = Rx * PRM.lamp;
        for (k = arr.begin(); k != arr.end(); k++) {
            (*k)->TRUcentre = Rx * (*k)->TRUcentre;
            (*k)->TRUaxe1 = Rx * (*k)->TRUaxe1;
            (*k)->TRUaxe2 = Rx * (*k)->TRUaxe2;
            (*k)->TRUaxe3 = Rx * (*k)->TRUaxe3;

            //    (*k)->VECTa0 = Ry * (*k)->VECTa0;
        }
    }
    //else {
    //    Swap_Matrix SWAPyz(2, 3);
    //    PRM.camera = SWAPyz * PRM.camera;
    //    PRM.normal = SWAPyz * PRM.normal;
    //    PRM.up =     SWAPyz * PRM.up;
    //    PRM.lamp =   SWAPyz * PRM.lamp;
    //    for (k = arr.begin(); k != arr.end(); k++) {
    //        (*k)->TRUcentre = SWAPyz * (*k)->TRUcentre;
    //        (*k)->TRUaxe1 =   SWAPyz * (*k)->TRUaxe1;
    //        (*k)->TRUaxe2 =   SWAPyz * (*k)->TRUaxe2;
    //        (*k)->TRUaxe3 =   SWAPyz * (*k)->TRUaxe3;
    //        //   (*k)->VECTa0 = SWAPxz * (*k)->VECTa0;
    //    }
    //}

    Vector parallel_transfer(PRM.a0,0,0);
    parallel_transfer = parallel_transfer + PRM.camera;
    PRM.camera = PRM.camera - parallel_transfer;
    PRM.lamp = PRM.lamp - parallel_transfer;

    for (k = arr.begin(); k != arr.end(); k++) {
        (*k)->TRUcentre = (*k)->TRUcentre - parallel_transfer;  
    }
    if (abs(normal_module - PRM.normal.module()) > 0.1) {
        cout << "second oops";
    }

    for (k = arr.begin(); k != arr.end(); k++) {
        (*k)->simple_figure((*k)->TRUcentre, (*k)->TRUaxe1, (*k)->TRUaxe2, (*k)->TRUaxe3, (*k)->VECTa0);
    }

    return arr;
}


//float scalarG(Vector a, const Vector& b, Matrix& G) {
//	return a.scalar(G * b);
//}
//
//if (tmp == "sphere" || tmp == "tetrah" || tmp == "parall") {
//    float x, y, z, R;
//    Vector c, a1, a2, a3, a0;
//    c.set(x, y, z);
//    a1.set(R, 0, 0);
//    a0.set(PRM.a0, 0, 0);
//    inp >> x >> y >> z >> R;
//    arr.push_back(factory[tmp]->Create(c, a1, a2, a3, a0));
//}
//else if (tmp == "tetrah") {
//    Vector ad[4], a0;//center and 3 adges
//    a0.set(PRM.a0, 0, 0);
//    for (int i = 0; i < 4; ++i) {
//        inp >> ad[i][0] >> ad[i][1] >> ad[i][2];
//    }
//    arr.push_back(factory[tmp]->Create(ad[0], ad[1], ad[2], ad[3], a0));
//}
//else if (tmp == "parall") {
//    Vector ad[4], a0;//center and 3 adges
//    a0.set(PRM.a0, 0, 0);
//    for (int i = 0; i < 4; ++i) {
//        inp >> ad[i][0] >> ad[i][1] >> ad[i][2];
//    }
//    arr.push_back(factory[tmp]->Create(ad[0], ad[1], ad[2], ad[3], a0));
//}

