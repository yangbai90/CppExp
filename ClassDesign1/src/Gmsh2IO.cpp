#include "Gmsh2IO.h"

Gmsh2IO::Gmsh2IO(){
    _MeshFileName.clear();
    _nNodes=0;
    _nElmts=0;
    _NodeCoords.clear();
    _ElmtConn.clear();
}

void Gmsh2IO::ReadMesh(){
    _MeshFileName="gmsh2.msh";
    _nElmts=3;_nNodesPerElmt=6;
    _nNodes=_nNodesPerElmt*_nElmts;
    _NodeCoords.resize(_nNodes*4);
    _ElmtConn.resize(_nElmts,vector<int>(0));
    for(int i=0;i<_nNodes;i++){
        _NodeCoords[i*4+0]=0.0;
        _NodeCoords[i*4+1]=1.0;
        _NodeCoords[i*4+2]=2.0;
        _NodeCoords[i*4+3]=3.0;
    }
    for(int e=0;e<_nElmts;e++){
        for(int i=0;i<_nNodesPerElmt;i++){
            _ElmtConn[e].push_back(i+1);
        }
    }
}

void Gmsh2IO::PrintMesh() const{
    cout<<"***************************************"<<endl;
    cout<<"*** Mesh file name="<<_MeshFileName<<endl;
    cout<<"*** Elmts="<<_nElmts<<", Nodes="<<_nNodes<<",NodesPerElmt="<<_nNodesPerElmt<<endl;
    for(int e=0;e<_nElmts;e++){
        cout<<"e="<<e+1<<":";
        for(int i=0;i<_nNodesPerElmt;i++){
            cout<<_ElmtConn[e][i]<<" ";
        }
        cout<<endl;
    }
    cout<<"***************************************"<<endl;
}