#include <iostream>

#include "Mesh.h"

using namespace std;

int main(){
    Mesh mesh1,mesh2(1);
    mesh1.ReadMesh();
    mesh1.PrintMesh();

    cout<<mesh1.GetMeshFileName()<<endl;

    mesh2.ReadMesh();
    mesh2.PrintMesh();

    cout<<mesh2.GetMeshFileName()<<endl;
    return 0;
}