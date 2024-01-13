//
// Created by te1t0ch1phead on 2022/4/19.
//

#include "TriangleSoupKDTree.h"
#include "extern/include/GeometrySmallLib.h"
#include <map>
#include <queue>

TriangleSoupKDTree::TriangleSoupKDTree(MeshKernel::SurfaceMesh * mesh) {
    this->mesh=mesh;
    int fSize = this->mesh->FaceSize();
    int vSize = this->mesh->VertexSize();
    face_record.resize(fSize);
    std::vector<MeshKernel::iGameFaceHandle> faceList;
    for(int i = 0;i<fSize;i++){
        faceList.emplace_back(FH{i});
    }
    for(int i=0;i<fSize;i++){
        FH fh = FH{i};
        auto& f = this->mesh->faces(fh);
        std::vector<VH> face;
        for(auto vh : f.getVertexHandle()){
            face.emplace_back(vh);
        }
        faces.emplace_back(face);
    }
    for(int i=0;i<vSize;i++){
        VH vh = VH{i};
        auto& v = this->mesh->vertices(vh);
        std::vector<double> vertex;
        vertex.emplace_back(v.x());
        vertex.emplace_back(v.y());
        vertex.emplace_back(v.z());
        vertices.emplace_back(vertex);
    }

    this->mesh->initBBox();
    double eps_x = (mesh->BBoxMax.x() - mesh->BBoxMin.x())/10/vSize;
    double eps_y = (mesh->BBoxMax.y() - mesh->BBoxMin.y())/10/vSize;
    double eps_z = (mesh->BBoxMax.z() - mesh->BBoxMin.z())/10/vSize;
    mesh->BBoxMax.x()+=eps_x;
    mesh->BBoxMin.x()-=eps_x;
    mesh->BBoxMax.y()+=eps_y;
    mesh->BBoxMin.y()-=eps_y;
    mesh->BBoxMax.z()+=eps_z;
    mesh->BBoxMin.z()-=eps_z;

    this->root=build_sub_tree(mesh->BBoxMin,mesh->BBoxMax,faceList,-1,0);
}

int TriangleSoupKDTree::build_sub_tree(MeshKernel::iGameVertex BBOXMIN,
                                       MeshKernel::iGameVertex BBOXMAX,
                                       std::vector<MeshKernel::iGameFaceHandle> face_list,
                                       int fa,
                                       int cut_type){
//    std::cout <<" new node " << kdt.size()<<" "<< face_list.size() <<std::endl;
//    std::cout <<"BBOXMIN"<<BBOXMIN.x()<<" "<< BBOXMIN.y()<<" "<< BBOXMIN.z()<<"BBOXMAX "<<
//    BBOXMAX.x()<<" "<< BBOXMAX.y()<<" "<< BBOXMAX.z()<<std::endl;


    kdtnode node;
    node.BBOXMIN=BBOXMIN;
    node.BBOXMAX=BBOXMAX;
    node.cut_type=cut_type;
    node.fa=fa;
    node.l=node.r=-1;
    node.exist=true;
    node.size=face_list.size();

    if(face_list.size()<= 16){
        node.face_list=face_list;
        kdt.push_back(node);
        for(int i=0;i<node.face_list.size();i++){
            face_record[face_list[i]] = std::make_pair(kdt.size()-1,i);
        }

        return kdt.size()-1;
    }

    double eps,cut_Axis,l,r;
    if(cut_type == 0){
        eps = (BBOXMAX.x() - BBOXMIN.x());
        l = BBOXMIN.x();
        r = BBOXMAX.x();
        cut_Axis = (l+r)/2;
    }
    else if(cut_type == 1){
        eps = (BBOXMAX.y() - BBOXMIN.y());
        l = BBOXMIN.y();
        r = BBOXMAX.y();
        cut_Axis = (l+r)/2;
    }
    else {
        eps = (BBOXMAX.z() - BBOXMIN.z());
        l = BBOXMIN.z();
        r = BBOXMAX.z();
        cut_Axis = (l+r)/2;
    }
    eps/=(1.0*face_list.size());
    std::vector<MeshKernel::iGameFaceHandle>left_child;
    std::vector<MeshKernel::iGameFaceHandle>right_child;
    std::vector<MeshKernel::iGameFaceHandle>self;
    std::function<bool(double,bool)>check = [&](double cut_Axis,bool is_final_build){

        int cnt_left=0;
        int cnt_right=0;
        for(auto i : face_list){
            std::vector<double> tmp;
            if(cut_type == 0) {
//                auto& f =  this->mesh->faces(i);
//                for(auto vh : f.getVertexHandle()){
//                    tmp.emplace_back(this->mesh->vertices(vh).x());
//                }
                for(auto vh : faces[i.idx()]){
                    tmp.emplace_back(vertices[vh.idx()][0]);
                }
            }
            else if(cut_type == 1){
//                auto& f =  this->mesh->faces(i);
//                for(auto vh : f.getVertexHandle()){
//                    tmp.emplace_back(this->mesh->vertices(vh).y());
//                }
                for(auto vh : faces[i.idx()]){
                    tmp.emplace_back(vertices[vh.idx()][1]);
                }
            }
            else{
//                auto& f =  this->mesh->faces(i);
//                for(auto vh : f.getVertexHandle()){
//                    tmp.emplace_back(this->mesh->vertices(vh).z());
//                }
                for(auto vh : faces[i.idx()]){
                    tmp.emplace_back(vertices[vh.idx()][2]);
                }
            }
            if(*std::max_element(tmp.begin(),tmp.end())< cut_Axis) {
                cnt_left++;
                if(is_final_build){
                    left_child.push_back(i);
                }
            }
            else if(*std::min_element(tmp.begin(),tmp.end())> cut_Axis){
                cnt_right++;
                if(is_final_build){
                    right_child.push_back(i);
                }
            }
            else{
                if(is_final_build) {
                    self.push_back(i);
                }
            }
        }
        return cnt_left <= cnt_right;
    };
    while(l+eps<r){
        double mid = (l+r)/2;
        if(check(mid,false))
        {
            cut_Axis=mid;
            l=mid;
        } else {
            r=mid;
        }
    }
    check(cut_Axis,true);
    node.cnt_plane=cut_Axis;
    MeshKernel::iGameVertex BBOXMAX_left_child = BBOXMAX;
    MeshKernel::iGameVertex BBOXMAX_right_child = BBOXMAX;
    MeshKernel::iGameVertex BBOXMIN_left_child = BBOXMIN;
    MeshKernel::iGameVertex BBOXMIN_right_child = BBOXMIN;

    if(cut_type == 0){
        BBOXMAX_left_child.x() = cut_Axis;
        BBOXMIN_right_child.x() = cut_Axis;
    }
    else if(cut_type == 1){
        BBOXMAX_left_child.y() = cut_Axis;
        BBOXMIN_right_child.y() = cut_Axis;
    }
    else{
        BBOXMAX_left_child.z() = cut_Axis;
        BBOXMIN_right_child.z() = cut_Axis;
    }
    node.face_list=self;
    kdt.push_back(node);
    int id = kdt.size()-1;
    for(int i=0;i<node.face_list.size();i++){
        face_record[face_list[i]] = std::make_pair(id,i);
    }
  //  std::cout <<" l,r,mid"<<l<<" "<<r<<" "<<cut_Axis<<std::endl;
  //  std::cout << id<<" "<< face_list.size()<<" "<<self.size()<<" "<< left_child.size()<<" "<< right_child.size()<<std::endl;
    if(left_child.size()>0){
        kdt[id].l = build_sub_tree(BBOXMIN_left_child,BBOXMAX_left_child,
                               left_child,id,(cut_type+1)%3);
    }
    if(right_child.size()>0){
        kdt[id].r = build_sub_tree(BBOXMIN_right_child,BBOXMAX_right_child,
                               right_child,id,(cut_type+1)%3);
    }
  //  std::cerr<<id<<" "<<node.l<<" "<<  node.r << std::endl;
    return id;
}
static int lalala=0;
std::vector<MeshKernel::iGameFaceHandle> TriangleSoupKDTree::query_cross_face(MeshKernel::iGameFaceHandle fh){

    auto tmp = queryByHandle(this->root, fh);;
    return tmp;
}

std::vector<MeshKernel::iGameFaceHandle> TriangleSoupKDTree::queryByHandle(int id, MeshKernel::iGameFaceHandle fh){
   // std::cout<< "query "<< id << std::endl;
    std::vector<MeshKernel::iGameFaceHandle> ret;
    //auto& f =  this->mesh->faces(fh);
    //int sides = f.size();
    int sides = faces[fh.idx()].size();
    if(sides == 3){
//        MeshKernel::iGameVertex mv0 = this->mesh->vertices(f.vh(0));
//        MeshKernel::iGameVertex mv1 = this->mesh->vertices(f.vh(1));
//        MeshKernel::iGameVertex mv2 = this->mesh->vertices(f.vh(2));
//        std::vector<double> m0{mv0.x(),mv0.y(),mv0.z()};
//        std::vector<double> m1{mv1.x(),mv1.y(),mv1.z()};
//        std::vector<double> m2{mv2.x(),mv2.y(),mv2.z()};
        auto& vhs = faces[fh.idx()];
        std::vector<double> m0{vertices[vhs[0].idx()][0],vertices[vhs[0].idx()][1],vertices[vhs[0].idx()][2]};
        std::vector<double> m1{vertices[vhs[1].idx()][0],vertices[vhs[1].idx()][1],vertices[vhs[1].idx()][2]};
        std::vector<double> m2{vertices[vhs[2].idx()][0],vertices[vhs[2].idx()][1],vertices[vhs[2].idx()][2]};
        GeometrySmallLib geo;
        for(auto this_node_fh : kdt[id].face_list) {
//            auto& tf =  this->mesh->faces(this_node_fh);
//            MeshKernel::iGameVertex nv0 = this->mesh->vertices(tf.vh(0));
//            MeshKernel::iGameVertex nv1 = this->mesh->vertices(tf.vh(1));
//            MeshKernel::iGameVertex nv2 = this->mesh->vertices(tf.vh(2));
//            std::vector<double> n0{nv0.x(),nv0.y(),nv0.z()};
//            std::vector<double> n1{nv1.x(),nv1.y(),nv1.z()};
//            std::vector<double> n2{nv2.x(),nv2.y(),nv2.z()};
            auto& t_vhs = faces[this_node_fh.idx()];
            int t_sides = t_vhs.size();
            if(t_sides == 3){
                std::vector<double> n0{vertices[t_vhs[0].idx()][0],vertices[t_vhs[0].idx()][1],vertices[t_vhs[0].idx()][2]};
                std::vector<double> n1{vertices[t_vhs[1].idx()][0],vertices[t_vhs[1].idx()][1],vertices[t_vhs[1].idx()][2]};
                std::vector<double> n2{vertices[t_vhs[2].idx()][0],vertices[t_vhs[2].idx()][1],vertices[t_vhs[2].idx()][2]};
                if (geo.check_tri_intersect(n0,n1,n2,m0,m1,m2)){
                    ret.push_back(this_node_fh);
                }
            }
            else if(t_sides == 4){
                std::vector<double> n0{vertices[t_vhs[0].idx()][0],vertices[t_vhs[0].idx()][1],vertices[t_vhs[0].idx()][2]};
                std::vector<double> n1{vertices[t_vhs[1].idx()][0],vertices[t_vhs[1].idx()][1],vertices[t_vhs[1].idx()][2]};
                std::vector<double> n2{vertices[t_vhs[2].idx()][0],vertices[t_vhs[2].idx()][1],vertices[t_vhs[2].idx()][2]};
                std::vector<double> n3{vertices[t_vhs[3].idx()][0],vertices[t_vhs[3].idx()][1],vertices[t_vhs[3].idx()][2]};
                if (geo.check_tri_intersect(n0,n1,n2,m0,m1,m2)
                    ||geo.check_tri_intersect(n2,n3,n0,m0,m1,m2)){
                    ret.push_back(this_node_fh);
                }
            }
        }
    }
    else if(sides == 4){
//        MeshKernel::iGameVertex mv0 = this->mesh->vertices(f.vh(0));
//        MeshKernel::iGameVertex mv1 = this->mesh->vertices(f.vh(1));
//        MeshKernel::iGameVertex mv2 = this->mesh->vertices(f.vh(2));
//        MeshKernel::iGameVertex mv3 = this->mesh->vertices(f.vh(3));
//        std::vector<double> m0{mv0.x(),mv0.y(),mv0.z()};
//        std::vector<double> m1{mv1.x(),mv1.y(),mv1.z()};
//        std::vector<double> m2{mv2.x(),mv2.y(),mv2.z()};
//        std::vector<double> m3{mv3.x(),mv3.y(),mv3.z()};
        auto& vhs = faces[fh.idx()];
        std::vector<double> m0{vertices[vhs[0].idx()][0],vertices[vhs[0].idx()][1],vertices[vhs[0].idx()][2]};
        std::vector<double> m1{vertices[vhs[1].idx()][0],vertices[vhs[1].idx()][1],vertices[vhs[1].idx()][2]};
        std::vector<double> m2{vertices[vhs[2].idx()][0],vertices[vhs[2].idx()][1],vertices[vhs[2].idx()][2]};
        std::vector<double> m3{vertices[vhs[3].idx()][0],vertices[vhs[3].idx()][1],vertices[vhs[3].idx()][2]};
        GeometrySmallLib geo;
        for(auto this_node_fh : kdt[id].face_list) {
//            auto& tf =  this->mesh->faces(this_node_fh);
//            MeshKernel::iGameVertex nv0 = this->mesh->vertices(tf.vh(0));
//            MeshKernel::iGameVertex nv1 = this->mesh->vertices(tf.vh(1));
//            MeshKernel::iGameVertex nv2 = this->mesh->vertices(tf.vh(2));
//            MeshKernel::iGameVertex nv3 = this->mesh->vertices(tf.vh(3));
//            std::vector<double> n0{nv0.x(),nv0.y(),nv0.z()};
//            std::vector<double> n1{nv1.x(),nv1.y(),nv1.z()};
//            std::vector<double> n2{nv2.x(),nv2.y(),nv2.z()};
//            std::vector<double> n3{nv3.x(),nv3.y(),nv3.z()};
            auto& t_vhs = faces[this_node_fh.idx()];
            int t_sides = t_vhs.size();
            if(t_sides == 3){
                std::vector<double> n0{vertices[t_vhs[0].idx()][0],vertices[t_vhs[0].idx()][1],vertices[t_vhs[0].idx()][2]};
                std::vector<double> n1{vertices[t_vhs[1].idx()][0],vertices[t_vhs[1].idx()][1],vertices[t_vhs[1].idx()][2]};
                std::vector<double> n2{vertices[t_vhs[2].idx()][0],vertices[t_vhs[2].idx()][1],vertices[t_vhs[2].idx()][2]};
                if (geo.check_tri_intersect(n0,n1,n2,m0,m1,m2)
                    ||geo.check_tri_intersect(n0,n1,n2,m2,m3,m0)){
                    ret.push_back(this_node_fh);
                }
            }
            else if(t_sides == 4){
                std::vector<double> n0{vertices[t_vhs[0].idx()][0],vertices[t_vhs[0].idx()][1],vertices[t_vhs[0].idx()][2]};
                std::vector<double> n1{vertices[t_vhs[1].idx()][0],vertices[t_vhs[1].idx()][1],vertices[t_vhs[1].idx()][2]};
                std::vector<double> n2{vertices[t_vhs[2].idx()][0],vertices[t_vhs[2].idx()][1],vertices[t_vhs[2].idx()][2]};
                std::vector<double> n3{vertices[t_vhs[3].idx()][0],vertices[t_vhs[3].idx()][1],vertices[t_vhs[3].idx()][2]};
                if (geo.check_tri_intersect(n0,n1,n2,m0,m1,m2)
                    ||geo.check_tri_intersect(n0,n1,n2,m2,m3,m0)
                    ||geo.check_tri_intersect(n2,n3,n0,m0,m1,m2)
                    ||geo.check_tri_intersect(n2,n3,n0,m2,m3,m0)){
                    ret.push_back(this_node_fh);
                }
            }
        }
    }



    std::vector<double>bound_limit;
    if(kdt[id].cut_type == 0){
//        auto& f =  this->mesh->faces(fh);
//        for(auto vh : f.getVertexHandle()){
//            bound_limit.emplace_back(this->mesh->vertices(vh).x());
//        }
        for(auto vh : faces[fh.idx()]){
            bound_limit.emplace_back(vertices[vh.idx()][0]);
        }
    }
    else if(kdt[id].cut_type == 1){
//        auto& f =  this->mesh->faces(fh);
//        for(auto vh : f.getVertexHandle()){
//            bound_limit.emplace_back(this->mesh->vertices(vh).y());
//        }
        for(auto vh : faces[fh.idx()]){
            bound_limit.emplace_back(vertices[vh.idx()][1]);
        }
    }
    else{
//        auto& f =  this->mesh->faces(fh);
//        for(auto vh : f.getVertexHandle()){
//            bound_limit.emplace_back(this->mesh->vertices(vh).z());
//        }
        for(auto vh : faces[fh.idx()]){
            bound_limit.emplace_back(vertices[vh.idx()][2]);
        }
    }

    if(*std::min_element(bound_limit.begin(),bound_limit.end())<kdt[id].cnt_plane ){
        //std::cout << "qmin"<<std::endl;
        if(kdt[id].l!=-1){
            auto tmp = queryByHandle(kdt[id].l, fh);
            for(auto i : tmp)
                ret.push_back(i);
        }

    }
    if(*std::max_element(bound_limit.begin(),bound_limit.end())>kdt[id].cnt_plane ){
       // std::cout << "qmax"<<std::endl;
        if(kdt[id].r!=-1){
            auto tmp = queryByHandle(kdt[id].r, fh);
            for(auto i : tmp)
                ret.push_back(i);

        }
    }

    return ret;
}


