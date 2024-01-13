#include "ModelDraw.h"
#include <QtCore/QtCore>
#include <QtWidgets/QLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/qprogressdialog.h>
#include <iostream>
#include "MeshKernel/IO.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Tools/MeshMath.h"
#include "Tools/TriQuality.h"
#include "Tools/QuadQuality.h"
#include "Tools/HexQuality.h"
#include "Tools/TetQuality.h"

ModelDraw::ModelDraw(QWidget *parent) : ViewOpenGL(parent),
                                        editModel(MODELEDIT),
                                        pickType(PickPoint) {

}

ModelDraw::~ModelDraw(void) {

}

/*=====================================表面网格操作=========================================*/

void ModelDraw::createModel() {
    currentNewID++;
    Model *model = new Model();

    modelList.insert(std::make_pair(currentNewID, model));
    currentModelID = currentNewID;
    currentModel = modelList[currentNewID];
    currentModel->modelScale = 1.0f;

    // VAO、VBO数组下标内容意义： 0:模型坐标 1:点选坐标 2:信息坐标 3:标架场坐标
    for (int i = 0; i < 4; i++) {
        currentModel->VAOs.push_back(0);
        currentModel->VBOs.push_back(0);
    }
}

void ModelDraw::deleteModel() {
    if (modelList.size() < 1) return;
    delete currentModel;
    modelList.erase(currentModelID);

    std::map<int, Model *>::iterator it;
    it = modelList.begin();
    if (it != modelList.end()) {
        currentModel = modelList[it->first];
        currentModelID = it->first;
    } else {
        currentModel = nullptr;
        currentModelID = -1;
    }

    if (modelList.size() < 1) {
        firstMeshFaceSize = -1;
        firstMeshVertexSize = -1;
    }
}

bool ModelDraw::loadMesh(std::string fileName) {
    int beg = fileName.find_last_of('/');
    QString filePath = QString::fromStdString(fileName.substr(++beg, fileName.length()));

    MeshKernel::IO io;
    clock_t time1 = clock();
    QString file_full;
    QFileInfo fileinfo;
    file_full = QString::fromLocal8Bit(fileName.c_str());
    fileinfo = QFileInfo(file_full);
    file_suffix = fileinfo.suffix();
    int sides_num;

    createModel();
    currentModel->structure = SURFACEMESH;
    saveFlieName(filePath.toStdString());
    if (file_suffix == "obj") {
        currentModel->surfaceMesh = MeshKernel::SurfaceMesh(io.ReadObjFile(fileName));
    } else if (file_suffix == "off") {
        currentModel->surfaceMesh = MeshKernel::SurfaceMesh(io.ReadOffFile(fileName));
    } else if (file_suffix == "stl") {
        currentModel->surfaceMesh = MeshKernel::SurfaceMesh(io.ReadStlFile(fileName));
    } else if (file_suffix == "vtk") {
        currentModel->surfaceMesh = MeshKernel::SurfaceMesh(io.ReadVtkFile(fileName, triconstrains));
    }
    std::cout << "currentModelID: " << currentModelID << std::endl;
    updateMeshModel();
    updateCurrentMesh();
    clock_t time2 = clock();
    std::cout << time2 - time1 << " ms" << std::endl;
    return true;
}


bool ModelDraw::saveMesh(std::string fileName) {
    if (!currentModel) return false;
    if (currentModel->structure != SURFACEMESH) return false;
    auto file_full = QString::fromLocal8Bit(fileName.c_str());
    auto fileinfo = QFileInfo(file_full);
    auto file_suffix = fileinfo.suffix();
    MeshKernel::IO io;
    if (file_suffix == "obj") {
        //currentModel->surfaceMesh.updateAllHandles();
        io.WriteObjFile(currentModel->surfaceMesh, fileName);
    } else if (file_suffix == "off") {
        io.WriteOffFile(currentModel->surfaceMesh, fileName);
    } else if (file_suffix == "stl") {
        io.WriteStlFile(currentModel->surfaceMesh, fileName);
    } else if (file_suffix == "vtk") {
        io.WriteVtkFile(currentModel->surfaceMesh, fileName);
    }
    return true;
}

void ModelDraw::meshClear() {
    if (modelList.size() <= 0) return;
    informationClear();
    drawItemClear(0);
    deleteModel();
    update();
}

void ModelDraw::meshInformationClear() {
    currentModel->information.clear();
    currentModel->crossField.clear();
    drawItem.point.clear();
    drawItem.edge.clear();
    drawItem.face.clear();
    removeSelectedAll();

    if (meshMetric != OFF) {
        meshMetric = OFF;
        drawMode = FLATFILL;
        colorMode = LIGHT;
    }
    update();
}

void ModelDraw::pickedItemClear() {
    removeSelectedAll();
    update();
}

void ModelDraw::informationClear() {
    currentModel->information.clear();
    update();
}

void ModelDraw::crossFieldClear() {
    currentModel->crossField.clear();
    update();
}

void ModelDraw::drawItemClear(int s) {
    if (s == 1) {
        drawItem.point.clear();
    } else if (s == 2) {
        drawItem.edge.clear();
    } else if (s == 3) {
        drawItem.face.clear();
    } else {
        drawItem.point.clear();
        drawItem.edge.clear();
        drawItem.face.clear();
    }
    update();
}

void ModelDraw::changeCurrentMeshToNext() {

    std::map<int, Model *>::iterator it;
    it = modelList.find(currentModelID);
    if (it == --modelList.end()) {
        it = modelList.begin();
    } else {
        it++;
    }
    currentModel = modelList[it->first];
    currentModelID = it->first;
    showInfo();
    update();
}

void ModelDraw::changeCurrentMeshToLast() {

    std::map<int, Model *>::iterator it;
    it = modelList.find(currentModelID);
    if (it == modelList.begin()) {
        it = --modelList.end();
    } else {
        it--;
    }
    currentModel = modelList[it->first];
    currentModelID = it->first;
    showInfo();
    update();
}

void ModelDraw::updateMeshModel() {
    // 只在加载第一个模型的时候才重置视角
    if (modelList.size() != 1) return;
    if (currentModel->structure == SURFACEMESH) {
        double minX = DBL_MAX;
        double maxX = -DBL_MAX;
        double minY = DBL_MAX;
        double maxY = -DBL_MAX;
        double minZ = DBL_MAX;
        double maxZ = -DBL_MAX;
        for (auto &vp : currentModel->surfaceMesh.allvertices()) {
            auto &v = vp.second;
            minX = std::min(minX, v.x()), maxX = std::max(maxX, v.x());
            minY = std::min(minY, v.y()), maxY = std::max(maxY, v.y());
            minZ = std::min(minZ, v.z()), maxZ = std::max(maxZ, v.z());
        }
        centerX = (minX + maxX) / 2;
        centerY = (minY + maxY) / 2;
        centerZ = (minZ + maxZ) / 2;
        radius = std::max(maxX - minX, std::max(maxY - minY, maxZ - minZ)) / 2;
    } else if (currentModel->structure == VOLUMEMESH) {
        double minX = DBL_MAX;
        double maxX = -DBL_MAX;
        double minY = DBL_MAX;
        double maxY = -DBL_MAX;
        double minZ = DBL_MAX;
        double maxZ = -DBL_MAX;
        for (auto &vp : currentModel->volumeMesh.allvertices()) {
            auto &v = vp.second;
            minX = std::min(minX, v.x()), maxX = std::max(maxX, v.x());
            minY = std::min(minY, v.y()), maxY = std::max(maxY, v.y());
            minZ = std::min(minZ, v.z()), maxZ = std::max(maxZ, v.z());
        }
        centerX = (minX + maxX) / 2;
        centerY = (minY + maxY) / 2;
        centerZ = (minZ + maxZ) / 2;
        radius = std::max(maxX - minX, std::max(maxY - minY, maxZ - minZ)) / 2;
    }
    printf("center: %.2f %.2f %.2f, radius: %.2f\n", centerX, centerY, centerZ, radius);
    SetScenePosition(Vector3d(centerX, centerY, centerZ), 1.6f * radius);
//    pickType = PickPoint;
//    currentModel->pick_vertices.push_back(centerX);
//    currentModel->pick_vertices.push_back(centerY);
//    currentModel->pick_vertices.push_back(centerZ);
    update();
}


// 每当mesh被修改之后，都要把新的顶点数据传入VBO中
void ModelDraw::updateCurrentMesh() {
    currentModel->vertices.clear();
    if (!currentModel) {
        showInfo();
        return;
    }

    if (currentModel->structure == SURFACEMESH) {
        std::cout << "SURFACEMESH" << std::endl;
        currentModel->surfaceMesh.genAllVerticesNormal();
        currentModel->tri_count = 0;
        // 三角形面片数据储存（四边形会拆成两个三角形）
        for (auto &fp : currentModel->surfaceMesh.allfaces()) {
            const auto &vhs = fp.second.getVertexHandle();
            for (int i = 2; i < vhs.size(); ++i) {
                vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                currentModel->tri_count++;
                float color_R, color_G, color_B;
                valueToRGB(fp.second.getValue(), color_R, color_G, color_B);
                for (auto &vh : tri_vhs) {
                    auto &v = currentModel->surfaceMesh.vertices(vh);
                    currentModel->vertices.emplace_back(v.x());
                    currentModel->vertices.emplace_back(v.y());
                    currentModel->vertices.emplace_back(v.z());
                    if (colorMode != COLOR) {
                        currentModel->vertices.push_back(v.getNormalX());
                        currentModel->vertices.push_back(v.getNormalY());
                        currentModel->vertices.push_back(v.getNormalZ());
                    } else {
                        currentModel->vertices.push_back(color_R);
                        currentModel->vertices.push_back(color_G);
                        currentModel->vertices.push_back(color_B);
                    }
                }
            }
        }
        cout << "tri count: " << currentModel->tri_count << endl;
        // 线框数据存储
        currentModel->line_count = 0;
        for (auto &ep : currentModel->surfaceMesh.alledges()) {
            currentModel->line_count++;
            auto &v0 = currentModel->surfaceMesh.vertices(ep.second.vh1());
            auto &v1 = currentModel->surfaceMesh.vertices(ep.second.vh2());
            currentModel->vertices.emplace_back(v0.x());
            currentModel->vertices.emplace_back(v0.y());
            currentModel->vertices.emplace_back(v0.z());
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(v1.x());
            currentModel->vertices.emplace_back(v1.y());
            currentModel->vertices.emplace_back(v1.z());
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
        }
        cout << "line count: " << currentModel->line_count << endl;
    } else if (currentModel->structure == VOLUMEMESH) {
        std::cout << "VOLUMEMESH" << std::endl;
        currentModel->volumeMesh.genAllVerticesNormal();

        currentModel->tri_count = 0;
        for (auto &cp : currentModel->volumeMesh.allcells()) {
            auto fhs = cp.second.getFaceHandle();
            float color_R, color_G, color_B;
            valueToRGB(cp.second.getValue(), color_R, color_G, color_B);
            for (auto fh : fhs) {
                auto &f = currentModel->volumeMesh.faces(fh);
                const auto &vhs = f.getVertexHandle();
                for (int i = 2; i < vhs.size(); ++i) {
                    vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                    currentModel->tri_count++;
                    for (auto &vh : tri_vhs) {
                        auto &v = currentModel->volumeMesh.vertices(vh);
                        currentModel->vertices.emplace_back(v.x());
                        currentModel->vertices.emplace_back(v.y());
                        currentModel->vertices.emplace_back(v.z());
                        if (colorMode != COLOR) {
                            currentModel->vertices.emplace_back(v.getNormalX());
                            currentModel->vertices.emplace_back(v.getNormalY());
                            currentModel->vertices.emplace_back(v.getNormalZ());
                        } else {
                            currentModel->vertices.emplace_back(color_R);
                            currentModel->vertices.emplace_back(color_G);
                            currentModel->vertices.emplace_back(color_B);
                        }
                    }
                }
            }
        }
        cout << "tri count: " << currentModel->tri_count << endl;
        // 线框数据存储
        currentModel->line_count = 0;
        for (auto &ep : currentModel->volumeMesh.alledges()) {
            currentModel->line_count++;
            auto &v0 = currentModel->volumeMesh.vertices(ep.second.vh1());
            auto &v1 = currentModel->volumeMesh.vertices(ep.second.vh2());
            currentModel->vertices.emplace_back(v0.x());
            currentModel->vertices.emplace_back(v0.y());
            currentModel->vertices.emplace_back(v0.z());
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(v1.x());
            currentModel->vertices.emplace_back(v1.y());
            currentModel->vertices.emplace_back(v1.z());
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
            currentModel->vertices.emplace_back(0);
        }
        cout << "line count: " << currentModel->line_count << endl;
    }
    showInfo();
    update();
}

void ModelDraw::updateCutMesh() {
    if (!currentModel) {
        showInfo();
        return;
    }
    if (currentModel->structure == SURFACEMESH) {
        // 切片情况
        if (!flag_CutPlane) return;
        currentModel->vertices.clear();
        vector<GLfloat> tempLineData;
        minX = std::numeric_limits<double>::max();
        maxX = std::numeric_limits<double>::min();
        minY = std::numeric_limits<double>::max();
        maxY = std::numeric_limits<double>::min();
        minZ = std::numeric_limits<double>::max();
        maxZ = std::numeric_limits<double>::min();
        for (auto &vp : currentModel->surfaceMesh.allvertices()) {
            auto &v = vp.second;
            minX = std::min(minX, v.x()), maxX = std::max(maxX, v.x());
            minY = std::min(minY, v.y()), maxY = std::max(maxY, v.y());
            minZ = std::min(minZ, v.z()), maxZ = std::max(maxZ, v.z());
        }
        double draw_min_x = cutX * (maxX - minX) + minX;
        double draw_min_y = cutY * (maxY - minY) + minY;
        double draw_min_z = cutZ * (maxZ - minZ) + minZ;
        //printf("draw min: (%.2f, %.2f, %.2f)\n", draw_min_x, draw_min_y, draw_min_z);
        currentModel->tri_count = 0;
        currentModel->line_count = 0;
        for (auto &fp : currentModel->surfaceMesh.allfaces()) {
            bool drawFlag = true;
            auto vex = fp.second.getVertexHandle();
            for (auto &vh : vex) {
                auto &v = currentModel->surfaceMesh.vertices(vh);
                if (v.x() < draw_min_x || v.y() < draw_min_y || v.z() < draw_min_z) {
                    drawFlag = false;
                    break;
                }
            }
            if (!drawFlag) continue;

            const auto &vhs = fp.second.getVertexHandle();
            for (int i = 2; i < vhs.size(); ++i) {
                vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                currentModel->tri_count++;
                float color_R, color_G, color_B;
                valueToRGB(fp.second.getValue(), color_R, color_G, color_B);
                for (auto &vh : tri_vhs) {
                    auto &v = currentModel->surfaceMesh.vertices(vh);
                    currentModel->vertices.emplace_back(v.x());
                    currentModel->vertices.emplace_back(v.y());
                    currentModel->vertices.emplace_back(v.z());
                    if (colorMode != COLOR) {
                        currentModel->vertices.push_back(v.getNormalX());
                        currentModel->vertices.push_back(v.getNormalY());
                        currentModel->vertices.push_back(v.getNormalZ());
                    } else {
                        currentModel->vertices.push_back(color_R);
                        currentModel->vertices.push_back(color_G);
                        currentModel->vertices.push_back(color_B);
                    }
                }
            }
            // 线框数据存储
            for (auto &eh : fp.second.getEdgeHandle()) {
                currentModel->line_count++;
                auto &e = currentModel->surfaceMesh.edges(eh);
                auto &v0 = currentModel->surfaceMesh.vertices(e.vh1());
                auto &v1 = currentModel->surfaceMesh.vertices(e.vh2());
                tempLineData.emplace_back(v0.x());
                tempLineData.emplace_back(v0.y());
                tempLineData.emplace_back(v0.z());
                tempLineData.emplace_back(0);
                tempLineData.emplace_back(0);
                tempLineData.emplace_back(0);
                tempLineData.emplace_back(v1.x());
                tempLineData.emplace_back(v1.y());
                tempLineData.emplace_back(v1.z());
                tempLineData.emplace_back(0);
                tempLineData.emplace_back(0);
                tempLineData.emplace_back(0);
            }
        }
        currentModel->vertices.insert(currentModel->vertices.end(), tempLineData.begin(), tempLineData.end());
    } else if (currentModel->structure == VOLUMEMESH) {
        if (!flag_CutPlane) return;
        currentModel->vertices.clear();
        vector<GLfloat> tempLineData;
        minX = std::numeric_limits<double>::max();
        maxX = std::numeric_limits<double>::min();
        minY = std::numeric_limits<double>::max();
        maxY = std::numeric_limits<double>::min();
        minZ = std::numeric_limits<double>::max();
        maxZ = std::numeric_limits<double>::min();
        for (auto &vp : currentModel->volumeMesh.allvertices()) {
            auto &v = vp.second;
            minX = std::min(minX, v.x()), maxX = std::max(maxX, v.x());
            minY = std::min(minY, v.y()), maxY = std::max(maxY, v.y());
            minZ = std::min(minZ, v.z()), maxZ = std::max(maxZ, v.z());
        }
        double draw_min_x = cutX * (maxX - minX) + minX;
        double draw_min_y = cutY * (maxY - minY) + minY;
        double draw_min_z = cutZ * (maxZ - minZ) + minZ;
        //printf("draw min: (%.2f, %.2f, %.2f)\n", draw_min_x, draw_min_y, draw_min_z);

        currentModel->tri_count = 0;
        currentModel->line_count = 0;
        for (auto &cp : currentModel->volumeMesh.allcells()) {
            bool drawFlag = true;
            auto fhs = cp.second.getFaceHandle();
            auto vex = cp.second.getVertexHandle();
            for (auto &vh : vex) {
                auto &v = currentModel->volumeMesh.vertices(vh);
                if (v.x() < draw_min_x || v.y() < draw_min_y || v.z() < draw_min_z) {
                    drawFlag = false;
                    break;
                }
            }
            if (!drawFlag) continue;

            float color_R, color_G, color_B;
            valueToRGB(cp.second.getValue(), color_R, color_G, color_B);
            for (auto fh : fhs) {
                auto &f = currentModel->volumeMesh.faces(fh);
                const auto &vhs = f.getVertexHandle();
                for (int i = 2; i < vhs.size(); ++i) {
                    vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                    currentModel->tri_count++;
                    for (auto &vh : tri_vhs) {
                        auto &v = currentModel->volumeMesh.vertices(vh);
                        currentModel->vertices.emplace_back(v.x());
                        currentModel->vertices.emplace_back(v.y());
                        currentModel->vertices.emplace_back(v.z());
                        if (colorMode != COLOR) {
                            currentModel->vertices.emplace_back(v.getNormalX());
                            currentModel->vertices.emplace_back(v.getNormalY());
                            currentModel->vertices.emplace_back(v.getNormalZ());
                        } else {
                            currentModel->vertices.emplace_back(color_R);
                            currentModel->vertices.emplace_back(color_G);
                            currentModel->vertices.emplace_back(color_B);
                        }
                    }
                }
                // 线框数据存储
                for (auto &eh : f.getEdgeHandle()) {
                    currentModel->line_count++;
                    auto &e = currentModel->volumeMesh.edges(eh);
                    auto &v0 = currentModel->volumeMesh.vertices(e.vh1());
                    auto &v1 = currentModel->volumeMesh.vertices(e.vh2());
                    tempLineData.emplace_back(v0.x());
                    tempLineData.emplace_back(v0.y());
                    tempLineData.emplace_back(v0.z());
                    tempLineData.emplace_back(0);
                    tempLineData.emplace_back(0);
                    tempLineData.emplace_back(0);
                    tempLineData.emplace_back(v1.x());
                    tempLineData.emplace_back(v1.y());
                    tempLineData.emplace_back(v1.z());
                    tempLineData.emplace_back(0);
                    tempLineData.emplace_back(0);
                    tempLineData.emplace_back(0);
                }
            }
        }
        currentModel->vertices.insert(currentModel->vertices.end(), tempLineData.begin(), tempLineData.end());
    }
    update();
}


void ModelDraw::loadShader() {
    if (!currentModel) return;

    // 相关数据传入shader
    shaderProgram.setUniformValue("model", viewRotateMatrix * currentModel->modelMatrix);    // 把模型矩阵传入shader
    shaderProgram.setUniformValue("view", viewMatrix); // 视角矩阵
    shaderProgram.setUniformValue("projection", projectionMatrix); // 投影矩阵
    shaderProgram.setUniformValue("rotate", viewRotateMatrix * currentModel->rotateMatrix); // 旋转矩阵（法向量专用）
    shaderProgram.setUniformValue("viewpos", 0.0f, 0.0f, 1.0f);  // 视角方向
    shaderProgram.setUniformValue("light.position", 0.0f, 0.0f, 1.0f);  // 光照方向
    shaderProgram.setUniformValue("light.ambient", 0.4f, 0.4f, 0.4f);    // 环境光照系数
    shaderProgram.setUniformValue("light.diffuse", 0.5f, 0.5f, 0.5f);    // 漫反射系数
    shaderProgram.setUniformValue("light.specular", 0.5f, 0.5f, 0.5f);    // 镜面反射系数
    shaderProgram.setUniformValue("shininess", 32.0f);

    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &currentModel->VAOs[0]);
    core->glDeleteBuffers(1, &currentModel->VBOs[0]);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &currentModel->VAOs[0]);
    core->glGenBuffers(1, &currentModel->VBOs[0]);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(currentModel->VAOs[0]);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, currentModel->VBOs[0]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       currentModel->vertices.size() * sizeof(GLfloat),
                       currentModel->vertices.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    if (colorMode != COLOR) {
        // 顶点法向传入VBO，location=1
        core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
        core->glEnableVertexAttribArray(1);
    } else {
        // 顶点颜色传入VBO，location=2
        core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
        core->glEnableVertexAttribArray(2);
    }
//    // 顶点法向传入VBO，location=1
//    core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//    core->glEnableVertexAttribArray(1);
//    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelDraw::drawTriMesh() {
    if (!currentModel) return;
    if (faceCull) { core->glEnable(GL_CULL_FACE); }
    else { core->glDisable(GL_CULL_FACE); }
    if (colorMode == COLOR) {
        shaderProgram.setUniformValue("rendermode", 4);
        shaderProgram.setUniformValue("colormode", 4);
        core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    core->glBindVertexArray(currentModel->VAOs[0]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_TRIANGLES, 0, currentModel->tri_count * 3);//count为顶点的数量

    // 表面网格
    if (surfaceGrid) {
        shaderProgram.setUniformValue("rendermode", 2);
        shaderProgram.setUniformValue("colormode", 3);
        if (isCurrentModel) {
            shaderProgram.setUniformValue("color", QVector4D(0.1, 0.1, 0.1, 1.0));
            //isCurrentModel = false;
        } else {
            shaderProgram.setUniformValue("color", QVector4D(0.5, 0.5, 0.5, 1.0));
        }
        core->glLineWidth(1);
        core->glDepthRange(0, 0.999998);    // 把线框位置深度调近，防止面片盖住线框
        core->glDisable(GL_CULL_FACE);
        core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    // 线框
        core->glBindVertexArray(currentModel->VAOs[0]);
        core->glDrawArrays(GL_LINES, currentModel->tri_count * 3, currentModel->line_count * 2);//count为顶点的数量
        core->glDepthRange(0, 1);    // 画完线框后改回原本深度
    }
}

/*=====================================体网格操作=========================================*/

bool ModelDraw::loadHedra(std::string fileName) {
    int beg = fileName.find_last_of('/');
    QString filePath = QString::fromStdString(fileName.substr(++beg, fileName.length()));

    MeshKernel::IO io;
    //meshClear();
    clock_t time1 = clock();
    QString file_full;
    QFileInfo fileinfo;
    file_full = QString::fromLocal8Bit(fileName.c_str());
    fileinfo = QFileInfo(file_full);
    file_suffix = fileinfo.suffix();
    int faces_num;

    createModel();
    currentModel->structure = VOLUMEMESH;
    saveFlieName(filePath.toStdString());
    if (file_suffix == "mesh") {
        currentModel->volumeMesh = MeshKernel::VolumeMesh(io.ReadMeshFile(fileName));
    } else if (file_suffix == "vtk") {
        currentModel->volumeMesh = MeshKernel::VolumeMesh(io.ReadVtkFile_Volume(fileName));
    }

    updateMeshModel();
    updateCurrentMesh();
    clock_t time2 = clock();
    std::cout << time2 - time1 << " ms" << std::endl;
    return true;
}

bool ModelDraw::saveHedra(std::string fileName) {
    if (!currentModel) return false;
    if (currentModel->structure != VOLUMEMESH) return false;
    auto file_full = QString::fromLocal8Bit(fileName.c_str());
    auto fileinfo = QFileInfo(file_full);
    auto file_suffix = fileinfo.suffix();
    MeshKernel::IO io;
    if (file_suffix == "mesh") {
        io.WriteMeshFile(currentModel->volumeMesh, fileName);
    }
    return true;
}

/*=====================================点选切割操作=========================================*/

void ModelDraw::loadPickItemToVBO() {
    //shaderProgram.setUniformValue("model", viewRotateMatrix * currentModel->modelMatrix);	// 把模型矩阵传入shader
    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &currentModel->VAOs[1]);
    core->glDeleteBuffers(1, &currentModel->VBOs[1]);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &currentModel->VAOs[1]);
    core->glGenBuffers(1, &currentModel->VBOs[1]);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(currentModel->VAOs[1]);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, currentModel->VBOs[1]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       currentModel->pick_vertices.size() * sizeof(GLfloat),
                       currentModel->pick_vertices.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelDraw::loadMeshInformationToVBO() {
    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &currentModel->VAOs[2]);
    core->glDeleteBuffers(1, &currentModel->VBOs[2]);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &currentModel->VAOs[2]);
    core->glGenBuffers(1, &currentModel->VBOs[2]);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(currentModel->VAOs[2]);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, currentModel->VBOs[2]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       currentModel->information.size() * sizeof(GLfloat),
                       currentModel->information.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    // 顶点颜色传入VBO，location=2
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelDraw::loadCrossFieldToVBO() {
    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &currentModel->VAOs[3]);
    core->glDeleteBuffers(1, &currentModel->VBOs[3]);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &currentModel->VAOs[3]);
    core->glGenBuffers(1, &currentModel->VBOs[3]);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(currentModel->VAOs[3]);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, currentModel->VBOs[3]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       currentModel->crossField.size() * sizeof(GLfloat),
                       currentModel->crossField.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelDraw::loadDrawItemToVBO() {
    // 点
    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &dVAO[0]);
    core->glDeleteBuffers(1, &dVBO[0]);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &dVAO[0]);
    core->glGenBuffers(1, &dVBO[0]);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(dVAO[0]);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, dVBO[0]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       drawItem.point.size() * sizeof(GLfloat),
                       drawItem.point.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    // 顶点颜色传入VBO，location=2
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 线
    core->glDeleteVertexArrays(1, &dVAO[1]);
    core->glDeleteBuffers(1, &dVBO[1]);
    core->glGenVertexArrays(1, &dVAO[1]);
    core->glGenBuffers(1, &dVBO[1]);
    core->glBindVertexArray(dVAO[1]);
    core->glBindBuffer(GL_ARRAY_BUFFER, dVBO[1]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       drawItem.edge.size() * sizeof(GLfloat),
                       drawItem.edge.data(),
                       GL_STATIC_DRAW);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 面
    core->glDeleteVertexArrays(1, &dVAO[2]);
    core->glDeleteBuffers(1, &dVBO[2]);
    core->glGenVertexArrays(1, &dVAO[2]);
    core->glGenBuffers(1, &dVBO[2]);
    core->glBindVertexArray(dVAO[2]);
    core->glBindBuffer(GL_ARRAY_BUFFER, dVBO[2]);
    core->glBufferData(GL_ARRAY_BUFFER,
                       drawItem.face.size() * sizeof(GLfloat),
                       drawItem.face.data(),
                       GL_STATIC_DRAW);
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void ModelDraw::showMeshNormal() {
    if (!currentModel || currentModel->structure == VOLUMEMESH) return;
    //相当于开关
    if (currentModel->crossField.size() > 0) {
        currentModel->crossField.clear();
        update();
        return;
    }
    for (auto &fp : currentModel->surfaceMesh.allfaces()) {
        auto fh = fp.first;
        const iGameFace &f = fp.second;
        int fSize = f.size();
        Vex midPoint;
        for (auto vh : f.getVertexHandle()) {
            auto &v = currentModel->surfaceMesh.vertices(vh);
            midPoint += v;
        }
        midPoint /= fSize;
        double s = 0.06;
        currentModel->crossField.emplace_back(midPoint.x());
        currentModel->crossField.emplace_back(midPoint.y());
        currentModel->crossField.emplace_back(midPoint.z());
        currentModel->crossField.emplace_back(midPoint.x() + const_cast<iGameFace &>(f).getNormalX() * s);
        currentModel->crossField.emplace_back(midPoint.y() + const_cast<iGameFace &>(f).getNormalY() * s);
        currentModel->crossField.emplace_back(midPoint.z() + const_cast<iGameFace &>(f).getNormalZ() * s);
    }
    updateCurrentMesh();
}

void ModelDraw::pickItem(double x, double y) {
    if (!currentModel) return;
    QVector4D point(x, y, 0.9, 1.0);        // point为鼠标点击的位置
    QVector4D toward(x, y, -1, 1.0);    // 指向toward与投影矩阵的fov相关
    QVector4D pointEnd = point + 2 * toward;
    QVector4D tpoint = currentModel->modelMatrix.inverted() * viewRotateMatrix.inverted() * viewMatrix.inverted()
        * projectionMatrix.inverted() * point;
    QVector4D tpointEnd = currentModel->modelMatrix.inverted() * viewRotateMatrix.inverted() * viewMatrix.inverted()
        * projectionMatrix.inverted() * pointEnd;
    // point1为射线起点，point2为射线终点
    QVector3D point1(tpoint.x() / tpoint.w(), tpoint.y() / tpoint.w(), tpoint.z() / tpoint.w());
    QVector3D point2(tpointEnd.x() / tpointEnd.w(), tpointEnd.y() / tpointEnd.w(), tpointEnd.z() / tpointEnd.w());
    float zMax = -9999999;

    std::vector<QVector3D> tempPoints;
    MeshKernel::iGameFaceHandle tempfHandle(-1);
    MeshKernel::iGameFace tempFace;
    QVector3D tempIntersection;
    if (currentModel->structure == SURFACEMESH) {
        // 寻找所有射线穿过的面，并找出其中离视角最近的一个面
        for (auto fp : currentModel->surfaceMesh.allfaces()) {
            auto fHandle = fp.first;
            auto fFace = fp.second;
            auto vex = fp.second.getVertexHandle();
            std::vector<QVector3D> fpoints;
            fpoints.clear();
            QVector4D fDepth(0, 0, 0, 0);
            for (int i = 0; i < vex.size(); i++) {
                fpoints.push_back(QVector3D(currentModel->surfaceMesh.vertices(vex[i]).x(),
                                            currentModel->surfaceMesh.vertices(vex[i]).y(),
                                            currentModel->surfaceMesh.vertices(vex[i]).z()));
                fDepth += QVector4D(fpoints[i], 1);
            }
            fDepth = QVector4D(fDepth.x() / fDepth.w(),
                               fDepth.y() / fDepth.w(),
                               fDepth.z() / fDepth.w(),
                               fDepth.w() / fDepth.w());
            fDepth = viewRotateMatrix * currentModel->modelMatrix * fDepth;
            bool flag = false;
            float u, v;
            QVector3D intersection;
            // 判断射线是否穿过此面
            if (vex.size() == 3) {
                flag = isIntersectTriangle(point1, point2, fpoints[0], fpoints[1], fpoints[2], intersection);
            } else if (vex.size() == 4) {
                flag = isIntersectTriangle(point1, point2, fpoints[0], fpoints[1], fpoints[2], intersection)
                    | isIntersectTriangle(point1, point2, fpoints[2], fpoints[3], fpoints[0], intersection);
            }
            if (flag && zMax < fDepth[2]) {
                zMax = fDepth[2];
                tempfHandle = fHandle;
                tempFace = fFace;
                tempIntersection = intersection;
                tempPoints.clear();
                for (int i = 0; i < vex.size(); i++) {
                    tempPoints.push_back(fpoints[i]);
                }
            }
        }
        if (tempfHandle.idx() != -1) {
            //std::cout << tempfHandle.idx() << std::endl;
            if (pickType == PickPoint) {
                double pointMin = 99999;
                MeshKernel::iGameVertexHandle tempvHandle(-1);
                MeshKernel::iGameVertex tempVertex;
                // 遍历一个面中所有的点，找出其中离射线最近的点
                for (auto vex : tempFace.getVertexHandle()) {
                    QVector3D point0(currentModel->surfaceMesh.vertices(vex).x(),
                                     currentModel->surfaceMesh.vertices(vex).y(),
                                     currentModel->surfaceMesh.vertices(vex).z());
                    double dist = point2LineDis(point1, point2, point0);
                    if (pointMin > dist) {
                        pointMin = dist;
                        tempvHandle = vex;
                        tempVertex = currentModel->surfaceMesh.vertices(vex);
                    }
                }
                pickedItemHandle = currentModel->surfaceMesh.vertexhandle(tempVertex).idx();
                selected_v_indices.emplace_back(pickedItemHandle);
                //this->updatePositionText(tempVertex.x(), tempVertex.y(), tempVertex.z());
                fixed_points.emplace_back(std::make_pair(tempvHandle, tempVertex));
                pickedItemPosition[0] = tempVertex.x();
                pickedItemPosition[1] = tempVertex.y();
                pickedItemPosition[2] = tempVertex.z();
                bool deleteFlag = false;
                for (int i = 0; i < pickedVHandle.size(); i++) {
                    if (tempvHandle == pickedVHandle[i]) {
                        pickedVHandle.erase(pickedVHandle.begin() + i);
                        currentModel->pick_vertices.erase(currentModel->pick_vertices.begin() + 3 * i,
                                                          currentModel->pick_vertices.begin() + 3 * i + 3);
                        deleteFlag = true;
                    }
                }
                if (deleteFlag == false) {
                    pickedVHandle.push_back(tempvHandle);
                    pickedItem = "vertex";
                    currentModel->pick_vertices.push_back(tempVertex.x());
                    currentModel->pick_vertices.push_back(tempVertex.y());
                    currentModel->pick_vertices.push_back(tempVertex.z());
                }
            } else if (pickType == PickEdge) {
                double pointMin = 99999;
                MeshKernel::iGameEdgeHandle tempeHandle(-1);
                MeshKernel::iGameEdge tempEdge;
                // 遍历一个面中所有的线，找出其中离射线最近的线
                for (auto edg : tempFace.getEdgeHandle()) {
                    auto vex1 = currentModel->surfaceMesh.edges(edg).vh1();
                    auto vex2 = currentModel->surfaceMesh.edges(edg).vh2();
                    QVector3D epoint1(currentModel->surfaceMesh.vertices(vex1).x(),
                                      currentModel->surfaceMesh.vertices(vex1).y(),
                                      currentModel->surfaceMesh.vertices(vex1).z());
                    QVector3D epoint2(currentModel->surfaceMesh.vertices(vex2).x(),
                                      currentModel->surfaceMesh.vertices(vex2).y(),
                                      currentModel->surfaceMesh.vertices(vex2).z());
                    double dist = point2LineDis(epoint1, epoint2, tempIntersection);
                    if (pointMin > dist) {
                        pointMin = dist;
                        tempeHandle = edg;
                        tempEdge = currentModel->surfaceMesh.edges(edg);
                    }
                }
                pickedItemHandle = currentModel->surfaceMesh.edgehandle(tempEdge).idx();
                selected_e_indices.emplace_back(pickedItemHandle);
                pickedItem = "edge";
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh1()).x());
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh1()).y());
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh1()).z());
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh2()).x());
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh2()).y());
                currentModel->pick_vertices.push_back(currentModel->surfaceMesh.vertices(tempEdge.vh2()).z());
            } else if (pickType == PickFace) {
                pickedItemHandle = currentModel->surfaceMesh.facehandle(tempFace).idx();
                selected_f_indices.emplace_back(pickedItemHandle);
                pickedItem = "face";
                const auto &vhs = tempFace.getVertexHandle();
                for (int i = 2; i < vhs.size(); ++i) {
                    vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                    for (auto &vh : tri_vhs) {
                        auto &v = currentModel->surfaceMesh.vertices(vh);
                        currentModel->pick_vertices.emplace_back(v.x());
                        currentModel->pick_vertices.emplace_back(v.y());
                        currentModel->pick_vertices.emplace_back(v.z());
                    }
                }
            }
        }
    } else if (currentModel->structure == VOLUMEMESH) {
        // 寻找所有射线穿过的面，并找出其中离视角最近的一个面
        for (auto fp : currentModel->volumeMesh.allfaces()) {
            auto fHandle = fp.first;
            auto fFace = fp.second;
            auto vex = fp.second.getVertexHandle();
            std::vector<QVector3D> fpoints;
            fpoints.clear();
            QVector4D fDepth(0, 0, 0, 0);
            for (int i = 0; i < vex.size(); i++) {
                fpoints.push_back(QVector3D(currentModel->volumeMesh.vertices(vex[i]).x(),
                                            currentModel->volumeMesh.vertices(vex[i]).y(),
                                            currentModel->volumeMesh.vertices(vex[i]).z()));
                fDepth += QVector4D(fpoints[i], 1);
            }
            fDepth = QVector4D(fDepth.x() / fDepth.w(),
                               fDepth.y() / fDepth.w(),
                               fDepth.z() / fDepth.w(),
                               fDepth.w() / fDepth.w());
            fDepth = viewRotateMatrix * currentModel->modelMatrix * fDepth;
            bool flag = false;
            float u, v;
            QVector3D intersection;
            // 判断射线是否穿过此面
            if (vex.size() == 3) {
                flag = isIntersectTriangle(point1, point2, fpoints[0], fpoints[1], fpoints[2], intersection);
            } else if (vex.size() == 4) {
                flag = isIntersectTriangle(point1, point2, fpoints[0], fpoints[1], fpoints[2], intersection)
                    | isIntersectTriangle(point1, point2, fpoints[2], fpoints[3], fpoints[0], intersection);
            }
            if (flag && zMax < fDepth[2]) {
                zMax = fDepth[2];
                tempfHandle = fHandle;
                tempFace = fFace;
                tempIntersection = intersection;
                tempPoints.clear();
                for (int i = 0; i < vex.size(); i++) {
                    tempPoints.push_back(fpoints[i]);
                }
            }
        }
        if (tempfHandle.idx() != -1) {
            //std::cout << tempfHandle.idx() << std::endl;
            if (pickType == PickPoint) {
                double pointMin = 99999;
                MeshKernel::iGameVertexHandle tempvHandle(-1);
                MeshKernel::iGameVertex tempVertex;
                // 一个面所有的点，找出其中离射线最近的点
                for (auto vex : tempFace.getVertexHandle()) {
                    QVector3D point0(currentModel->volumeMesh.vertices(vex).x(),
                                     currentModel->volumeMesh.vertices(vex).y(),
                                     currentModel->volumeMesh.vertices(vex).z());
                    double dist = point2LineDis(point1, point2, point0);
                    if (pointMin > dist) {
                        pointMin = dist;
                        tempvHandle = vex;
                        tempVertex = currentModel->volumeMesh.vertices(vex);
                    }
                }
                pickedItemHandle = currentModel->volumeMesh.vertexhandle(tempVertex).idx();
                selected_v_indices.emplace_back(pickedItemHandle);
                //this->updatePositionText(tempVertex.x(), tempVertex.y(), tempVertex.z());
                fixed_points.emplace_back(std::make_pair(pickedItemHandle, tempVertex));

                pickedItem = "vertex";
                currentModel->pick_vertices.push_back(tempVertex.x());
                currentModel->pick_vertices.push_back(tempVertex.y());
                currentModel->pick_vertices.push_back(tempVertex.z());
            } else if (pickType == PickEdge) {
                double pointMin = 99999;
                MeshKernel::iGameEdgeHandle tempeHandle(-1);
                MeshKernel::iGameEdge tempEdge;
                // 一个面所有的线，找出其中离射线最近的线
                for (auto edg : tempFace.getEdgeHandle()) {
                    auto vex1 = currentModel->volumeMesh.edges(edg).vh1();
                    auto vex2 = currentModel->volumeMesh.edges(edg).vh2();
                    QVector3D epoint1(currentModel->volumeMesh.vertices(vex1).x(),
                                      currentModel->volumeMesh.vertices(vex1).y(),
                                      currentModel->volumeMesh.vertices(vex1).z());
                    QVector3D epoint2(currentModel->volumeMesh.vertices(vex2).x(),
                                      currentModel->volumeMesh.vertices(vex2).y(),
                                      currentModel->volumeMesh.vertices(vex2).z());
                    double dist = point2LineDis(epoint1, epoint2, tempIntersection);
                    if (pointMin > dist) {
                        pointMin = dist;
                        tempeHandle = edg;
                        tempEdge = currentModel->volumeMesh.edges(edg);
                    }
                }
                pickedItemHandle = currentModel->volumeMesh.edgehandle(tempEdge).idx();
                selected_e_indices.emplace_back(pickedItemHandle);
                pickedItem = "edge";
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh1()).x());
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh1()).y());
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh1()).z());
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh2()).x());
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh2()).y());
                currentModel->pick_vertices.push_back(currentModel->volumeMesh.vertices(tempEdge.vh2()).z());
            } else if (pickType == PickFace) {
                pickedItemHandle = currentModel->volumeMesh.facehandle(tempFace).idx();
                selected_f_indices.emplace_back(pickedItemHandle);
                pickedItem = "face";
                const auto &vhs = tempFace.getVertexHandle();
                for (int i = 2; i < vhs.size(); ++i) {
                    vector<VH> tri_vhs = {vhs[0], vhs[i - 1], vhs[i]};
                    for (auto &vh : tri_vhs) {
                        auto &v = currentModel->surfaceMesh.vertices(vh);
                        currentModel->pick_vertices.emplace_back(v.x());
                        currentModel->pick_vertices.emplace_back(v.y());
                        currentModel->pick_vertices.emplace_back(v.z());
                    }
                }
            } else if (pickType == PickCell) {

            }
        }
    }
    showInfo();
    update();
}

void ModelDraw::pickPoint(double x, double y) {
    if (!currentModel) return;
    QVector4D point(x, y, 0.9, 1.0);        // point为鼠标点击的位置
    QVector4D toward(x, y, -1, 1.0);    // 指向toward与投影矩阵的fov相关
    QVector4D pointEnd = point + 2 * toward;
    QVector4D tpoint = currentModel->modelMatrix.inverted() * viewRotateMatrix.inverted() * viewMatrix.inverted()
        * projectionMatrix.inverted() * point;
    QVector4D tpointEnd = currentModel->modelMatrix.inverted() * viewRotateMatrix.inverted() * viewMatrix.inverted()
        * projectionMatrix.inverted() * pointEnd;
    // point1为射线起点，point2为射线终点
    QVector3D point1(tpoint.x() / tpoint.w(), tpoint.y() / tpoint.w(), tpoint.z() / tpoint.w());
    QVector3D point2(tpointEnd.x() / tpointEnd.w(), tpointEnd.y() / tpointEnd.w(), tpointEnd.z() / tpointEnd.w());
    float zMax = -9999999;
    double pickRadius = 0.01;
    MeshKernel::iGameVertex tempVertex;
    bool picked = false;

    if (currentModel->structure == SURFACEMESH) {
        for (auto vp : currentModel->surfaceMesh.allvertices()) {
            auto v = vp.second;
            auto vh = vp.first;
            QVector3D point0(v.x(), v.y(), v.z());
            double dist = point2LineDis(point1, point2, point0);
            if (dist < pickRadius) {
                QVector4D fDepth(point0, 0);
                fDepth = viewRotateMatrix * currentModel->modelMatrix * fDepth;
                if (fDepth[2] > zMax) {
                    zMax = fDepth[2];
                    tempVertex = v;
                    picked = true;
                }
            }
        }
    }
    if (picked) {
        pickedItemHandle = currentModel->surfaceMesh.vertexhandle(tempVertex).idx();
        currentModel->pick_vertices.push_back(tempVertex.x());
        currentModel->pick_vertices.push_back(tempVertex.y());
        currentModel->pick_vertices.push_back(tempVertex.z());
        pickedItemPosition[0] = tempVertex.x();
        pickedItemPosition[1] = tempVertex.y();
        pickedItemPosition[2] = tempVertex.z();
    }
}

void ModelDraw::removeSelectedAll() {
    currentModel->pick_vertices.clear();
    moved_points.clear();
    fixed_points.clear();
    previous_position.clear();
    pickedVHandle.clear();
    selected_v_indices.clear();
    selected_e_indices.clear();
    selected_f_indices.clear();
    selected_c_indices.clear();
    pickedItemHandle = -1;
    showInfo();
    update();
}

double ModelDraw::point2LineDis(QVector3D point1, QVector3D point2, QVector3D point0) {

    //直线的法向量(p,q,r)
    QVector3D normal = (point1 - point2).normalized();

    //两个向量
    QVector3D normal01 = (point1 - point0).normalized();
    QVector3D normal02 = (point2 - point0).normalized();

    //进行叉乘
    double cross_x = normal01.y() * normal02.z() - normal02.y() * normal01.z();
    double cross_y = normal02.x() * normal01.z() - normal02.z() * normal01.x();
    double cross_z = normal01.x() * normal02.y() - normal01.y() * normal02.x();

    double cross_length = sqrt(cross_x * cross_x + cross_y * cross_y + cross_z * cross_z);
    double dx = (point2 - point1).x();
    double dy = (point2 - point1).y();
    double dz = (point2 - point1).z();

    double qb_length = sqrt(dx * dx + dy * dy + dz * dz);

    double ds = cross_length / qb_length;
    return ds;

}

bool ModelDraw::isIntersectTriangle(QVector3D orig,
                                    QVector3D end,
                                    QVector3D v0,
                                    QVector3D v1,
                                    QVector3D v2,
                                    QVector3D &intersection) {
    // Refer to https://www.cnblogs.com/graphics/archive/2010/08/09/1795348.html
    float t, u, v;
    QVector3D dir = end - orig;
    QVector3D E1 = v1 - v0;
    QVector3D E2 = v2 - v0;
    // 叉乘
    QVector3D P(dir.y() * E2.z() - E2.y() * dir.z(),
                E2.x() * dir.z() - E2.z() * dir.x(),
                dir.x() * E2.y() - dir.y() * E2.x());
    // 点乘
    float det = E1.x() * P.x() + E1.y() * P.y() + E1.z() * P.z();
    QVector3D T;
    if (det > 0) {
        T = orig - v0;
    } else {
        T = v0 - orig;
        det = -det;
    }
    if (det < 0) {
        return false;
    }

    // Calculate u and make sure u <= 1
    u = T.x() * P.x() + T.y() * P.y() + T.z() * P.z();
    if (u < 0.0f || u > det) {
        return false;
    }

    // Q
    QVector3D Q(T.y() * E1.z() - E1.y() * T.z(),
                E1.x() * T.z() - E1.z() * T.x(),
                T.x() * E1.y() - T.y() * E1.x());

    // Calculate v and make sure u + v <= 1
    v = dir.x() * Q.x() + dir.y() * Q.y() + dir.z() * Q.z();
    if (v < 0.0f || u + v > det) {
        return false;
    }

    //// Calculate t, scale parameters, ray intersects triangle
    //t = E2.x() * Q.x() + E2.y() * Q.y() + E2.z() * Q.z();
    float fInvDet = 1.0f / det;
    //t *= fInvDet;
    u *= fInvDet;
    v *= fInvDet;
    intersection = u * E1 + v * E2 + v0;
    return true;
}

void ModelDraw::PickItemTranslate() {
    // 此功能只是试用，不会继续修改完善
    std::cout << pickedItemHandle << std::endl;
    if (pickedItemHandle == -1) return;
    if (currentModel->structure == SURFACEMESH) {
        if (pickType == PickPoint) {
            auto &pickPoint = currentModel->surfaceMesh.vertices(MeshKernel::iGameVertexHandle(pickedItemHandle));
            QVector4D QpickPoint(pickPoint.x(), pickPoint.y(), pickPoint.z(), 1);
            QpickPoint = pickItemMoveMatrix * QpickPoint;
            pickPoint = MeshKernel::iGameVertex(QpickPoint.x(), QpickPoint.y(), QpickPoint.z());
            // 更新点选渲染的位置，让红色的点也跟着被拖拽的点一起移动
            for (int i = 0; i < pickedVHandle.size(); i++) {
                if (pickedItemHandle == pickedVHandle[i]) {
                    currentModel->pick_vertices[3 * i] = pickPoint.x();
                    currentModel->pick_vertices[3 * i + 1] = pickPoint.y();
                    currentModel->pick_vertices[3 * i + 2] = pickPoint.z();
                }
            }
        } else if (pickType == PickEdge) {

        } else if (pickType == PickFace) {

        } else if (pickType == PickCell) {

        }
    } else if (currentModel->structure == VOLUMEMESH) {
        if (pickType == PickPoint) {

        } else if (pickType == PickEdge) {

        } else if (pickType == PickFace) {

        } else if (pickType == PickCell) {

        }
    }
    updateCurrentMesh();
}

void ModelDraw::pick_point_with_depth(float x, float y, double (&p)[3], double itemPosition[3]) {
    if (!currentModel) return;
    QVector4D point(x, y, 0.9, 1.0);        // point为鼠标点击的位置
    QVector4D toward(x, y, -1, 1.0);    // 指向toward与投影矩阵的fov相关
    QVector4D pointView(0, 0, 1, 1.0);
    QVector4D pointEnd = point + 2 * toward;
    QVector4D
        tpoint = currentModel->modelMatrix.inverted() * viewMatrix.inverted() * projectionMatrix.inverted() * point;
    QVector4D tpointEnd =
        currentModel->modelMatrix.inverted() * viewMatrix.inverted() * projectionMatrix.inverted() * pointEnd;
    QVector4D tpointView =
        currentModel->modelMatrix.inverted() * viewMatrix.inverted() * projectionMatrix.inverted() * pointView;
    // point1为射线起点，point2为射线终点
    QVector3D point1(tpoint.x() / tpoint.w(), tpoint.y() / tpoint.w(), tpoint.z() / tpoint.w());
    QVector3D point2(tpointEnd.x() / tpointEnd.w(), tpointEnd.y() / tpointEnd.w(), tpointEnd.z() / tpointEnd.w());
    QVector3D
        faceNormal(tpointView.x() / tpointView.w(), tpointView.y() / tpointView.w(), tpointView.z() / tpointView.w());

    // 射线向量
    double e[3]{point2.x() - point1.x(), point2.y() - point1.y(), point2.z() - point1.z()};
    // 射线起点
    double PL[3]{point1.x(), point1.y(), point1.z()};
    // 平面向量
    double q[3]{itemPosition[0] - faceNormal.x(), itemPosition[1] - faceNormal.y(), itemPosition[2] - faceNormal.z()};

    double t = (q[0] * (itemPosition[0] - PL[0]) + q[1] * (itemPosition[1] - PL[1]) + q[2] * (itemPosition[2] - PL[2]))
        / (q[0] * e[0] + q[1] * e[1] + q[2] * e[2]);
    p[0] = PL[0] + e[0] * t;
    p[1] = PL[1] + e[1] * t;
    p[2] = PL[2] + e[2] * t;

    currentModel->pick_vertices.push_back(p[0]);
    currentModel->pick_vertices.push_back(p[1]);
    currentModel->pick_vertices.push_back(p[2]);
}

/*=====================================渲染操作=========================================*/

void ModelDraw::DrawScene(void) {
    DrawBackGround();
    DrawColorBar();
    DrawSceneModel();
    DrawCoordCircle();
}

void ModelDraw::DrawBackGround(void) {
    // 渐变背景，其实是一个长方形面片，绘制在最底下
    std::vector<GLfloat> back_ground_vertices{
        // 顶点位置            // 坐标颜色
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // 右上角
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // 左下角
        1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // 右下角
        -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,    // 左上角
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // 左下角
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f    // 右上角
    };

    // 使用单位化矩阵赋值给模型、视角、投影矩阵，目的是为了旋转缩放等操作不影响背景的改变
    QMatrix4x4 identityMatrix;
    shaderProgram.setUniformValue("model", identityMatrix);    // 模型矩阵
    shaderProgram.setUniformValue("view", identityMatrix); // 视角矩阵
    shaderProgram.setUniformValue("projection", identityMatrix); // 投影矩阵
    shaderProgram.setUniformValue("colormode", 4);

    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &bVAO);
    core->glDeleteBuffers(1, &bVBO);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &bVAO);
    core->glGenBuffers(1, &bVBO);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(bVAO);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, bVBO);
    core->glBufferData(GL_ARRAY_BUFFER,
                       back_ground_vertices.size() * sizeof(GLfloat),
                       back_ground_vertices.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    // 顶点法向传入VBO，location=1
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    core->glBindVertexArray(bVAO);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    core->glDepthRange(0.9999, 1);
    core->glDrawArrays(GL_TRIANGLES, 0, back_ground_vertices.size() / 6);
    core->glDepthRange(0, 1);

}

void ModelDraw::DrawColorBar() {
    if (meshMetric == OFF) return;
    float left = -0.95f, right = -0.9f, top = 0.9f, mid = 0.0f, bottom = -0.9f;
    std::vector<GLfloat> colorBar_vertices{
        // 顶点位置            // 坐标颜色
        //第一个
        right, top, 0.1f, 1.0f, 0.0f, 0.0f,   // 右上角
        left, mid, 0.1f, 1.0f, 1.0f, 1.0f,   // 左下角
        right, mid, 0.1f, 1.0f, 1.0f, 1.0f,   // 右下角
        left, top, 0.1f, 1.0f, 0.0f, 0.0f,    // 左上角
        left, mid, 0.1f, 1.0f, 1.0f, 1.0f,   // 左下角
        right, top, 0.1f, 1.0f, 0.0f, 0.0f,   // 右上角
        //第二个
        right, mid, 0.1f, 1.0f, 1.0f, 1.0f,   // 右上角
        left, bottom, 0.1f, 0.0f, 0.0f, 1.0f,   // 左下角
        right, bottom, 0.1f, 0.0f, 0.0f, 1.0f,   // 右下角
        left, mid, 0.1f, 1.0f, 1.0f, 1.0f,    // 左上角
        left, bottom, 0.1f, 0.0f, 0.0f, 1.0f,   // 左下角
        right, mid, 0.1f, 1.0f, 1.0f, 1.0f    // 右上角
    };

    // 使用单位化矩阵赋值给模型、视角、投影矩阵，目的是为了旋转缩放等操作不影响背景的改变
    QMatrix4x4 identityMatrix;
    shaderProgram.setUniformValue("model", identityMatrix);    // 模型矩阵
    shaderProgram.setUniformValue("view", identityMatrix); // 视角矩阵
    shaderProgram.setUniformValue("projection", identityMatrix); // 投影矩阵
    shaderProgram.setUniformValue("colormode", 4);

    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &cbVAO);
    core->glDeleteBuffers(1, &cbVBO);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &cbVAO);
    core->glGenBuffers(1, &cbVBO);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(cbVAO);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, cbVBO);
    core->glBufferData(GL_ARRAY_BUFFER,
                       colorBar_vertices.size() * sizeof(GLfloat),
                       colorBar_vertices.data(),
                       GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    // 顶点法向传入VBO，location=1
    core->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    core->glEnableVertexAttribArray(2);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

    core->glBindVertexArray(cbVAO);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    core->glDepthRange(0.999, 1);
    core->glDrawArrays(GL_TRIANGLES, 0, colorBar_vertices.size() / 6);
    core->glDepthRange(0, 1);
}

void ModelDraw::DrawCoordCircle(void) {
    if (!currentModel) return;

    coord_vertices.clear();

    float R = 1.2f * radius;
    int n = 100;     //这里的n表示用多边形绘制圆的精度，可以考虑增大精度

    core->glLineWidth(1);// 线宽
    // 圆形坐标
    for (int i = 0; i < n; i++)     //通过数学计算来画多边形的点
    {
        coord_vertices.push_back(centerX + R * cos(2 * PI * i / n));
        coord_vertices.push_back(centerY + R * sin(2 * PI * i / n));
        coord_vertices.push_back(centerZ + 0);
    }

    for (int i = 0; i < n; i++) {
        coord_vertices.push_back(centerX + R * cos(2 * PI * i / n));
        coord_vertices.push_back(centerY + 0);
        coord_vertices.push_back(centerZ + R * sin(2 * PI * i / n));
    }

    for (int i = 0; i < n; i++) {
        coord_vertices.push_back(centerX + 0);
        coord_vertices.push_back(centerY + R * cos(2 * PI * i / n));
        coord_vertices.push_back(centerZ + R * sin(2 * PI * i / n));
    }

    // 十字坐标
    coord_vertices.push_back(centerX + 0);
    coord_vertices.push_back(centerY + 0);
    coord_vertices.push_back(centerZ + 1.2f * R);
    coord_vertices.push_back(centerX + 0);
    coord_vertices.push_back(centerY + 0);
    coord_vertices.push_back(centerZ + -1.2f * R);

    coord_vertices.push_back(centerX + 0);
    coord_vertices.push_back(centerY + 1.2f * R);
    coord_vertices.push_back(centerZ + 0);
    coord_vertices.push_back(centerX + 0);
    coord_vertices.push_back(centerY + -1.2f * R);
    coord_vertices.push_back(centerZ + 0);

    coord_vertices.push_back(centerX + 1.2f * R);
    coord_vertices.push_back(centerY + 0);
    coord_vertices.push_back(centerZ + 0);
    coord_vertices.push_back(centerX + -1.2f * R);
    coord_vertices.push_back(centerY + 0);
    coord_vertices.push_back(centerZ + 0);

    QMatrix4x4 t;
    t.translate(0, 0, -3.0);
    shaderProgram.setUniformValue("model", viewRotateMatrix);    // 把模型矩阵传入shader
    shaderProgram.setUniformValue("view", t);
    shaderProgram.setUniformValue("colormode", 3);

    // 释放旧数据的内存
    core->glDeleteVertexArrays(1, &cVAO);
    core->glDeleteBuffers(1, &cVBO);
    // 1.新建顶点数组对象
    core->glGenVertexArrays(1, &cVAO);
    core->glGenBuffers(1, &cVBO);
    // 2. 绑定顶点数组对象
    core->glBindVertexArray(cVAO);
    // 3. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    core->glBindBuffer(GL_ARRAY_BUFFER, cVBO);
    core->glBufferData(GL_ARRAY_BUFFER, coord_vertices.size() * sizeof(GLfloat), coord_vertices.data(), GL_STATIC_DRAW);
    // 4. 设定顶点属性指针
    // 顶点坐标传入VBO，location=0
    core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    core->glEnableVertexAttribArray(0);
    core->glBindVertexArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
    core->glBindVertexArray(cVAO);    // 前面已经记录了VBO和EBO现在只需一步调用即可

    if (coordCircle) {
        shaderProgram.setUniformValue("color", QVector4D(0.0, 0.9, 0.9, 0.6));
        core->glDrawArrays(GL_LINE_LOOP, 0, n);
        shaderProgram.setUniformValue("color", QVector4D(1.0, 0.84, 0.0, 0.6));
        core->glDrawArrays(GL_LINE_LOOP, n, n);
        shaderProgram.setUniformValue("color", QVector4D(0.8, 0.0, 0.0, 0.6));
        core->glDrawArrays(GL_LINE_LOOP, 2 * n, n);
    }
    if (ModelMoveState) {
        shaderProgram.setUniformValue("color", QVector4D(0.0, 0.9, 0.9, 0.6));
        core->glDrawArrays(GL_LINES, 3 * n, 2);
        shaderProgram.setUniformValue("color", QVector4D(1.0, 0.84, 0.0, 0.6));
        core->glDrawArrays(GL_LINES, 3 * n + 2, 2);
        shaderProgram.setUniformValue("color", QVector4D(0.8, 0.0, 0.0, 0.6));
        core->glDrawArrays(GL_LINES, 3 * n + 4, 2);
    }
}

void ModelDraw::DrawStyle(void) {
    switch (drawMode) {
        case POINTS:core->glPointSize(4);
            core->glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            shaderProgram.setUniformValue("rendermode", 1);
            break;
        case FLATLINES:core->glLineWidth(1);// 线宽
            core->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shaderProgram.setUniformValue("rendermode", 2);
            break;
        case FILL:core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            shaderProgram.setUniformValue("rendermode", 3);
            break;
        case FLATFILL:core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            shaderProgram.setUniformValue("rendermode", 4);
            break;
        default:break;
    }
}

void ModelDraw::ColorStyle(void) {
    switch (colorMode) {
        case LIGHT:shaderProgram.setUniformValue("colormode", 1);
            break;
        case NORMAL:shaderProgram.setUniformValue("colormode", 2);
            break;
        case COLOR:shaderProgram.setUniformValue("colormode", 4);
            break;
        default:break;
    }
}

void ModelDraw::DrawSceneModel(void) {
    if (!currentModel) return;
    tempModel = currentModel;
    tempModelID = currentModelID;

    // 对于所有模型，挨个渲染一次
    for (auto mp : modelList) {
        currentModel = mp.second;
        currentModelID = mp.first;
        if (currentModelID == tempModelID) isCurrentModel = true;
        DrawStyle();
        ColorStyle();
        loadShader();

        drawTriMesh();

        drawPickItem();
        drawInformationItem();
        drawCrossField();
        isCurrentModel = false;
    }
    currentModel = tempModel;
    currentModelID = tempModelID;
    drawDrawItem();
}

void ModelDraw::drawPickItem() {
    loadPickItemToVBO();
    shaderProgram.setUniformValue("colormode", 3);
    shaderProgram.setUniformValue("color", QVector4D(0.8, 0.0, 0.0, 0.6));
    core->glBindVertexArray(currentModel->VAOs[1]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glPointSize(7);
    core->glLineWidth(3);
    core->glDepthRange(0, 0.99999);
    switch (pickType) {
        case PickPoint: {
            core->glDrawArrays(GL_POINTS, 0, currentModel->pick_vertices.size() / 3);
            break;
        }
        case PickEdge: {
            core->glDrawArrays(GL_LINES, 0, currentModel->pick_vertices.size() / 3);
            break;
        }
        case PickFace: {
            core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            core->glDrawArrays(GL_TRIANGLES, 0, currentModel->pick_vertices.size() / 3);
            break;
        }
        case PickCell: {
            break;
        }
    }
    //core->glDrawArrays(GL_POINTS, 0, currentModel->pick_vertices.size() / 3);
    core->glDepthRange(0, 1);
}

void ModelDraw::drawInformationItem() {
    loadMeshInformationToVBO();
    shaderProgram.setUniformValue("colormode", 5);
    shaderProgram.setUniformValue("rendermode", 4);
    core->glPointSize(7);
    core->glLineWidth(3);
    core->glDepthRange(0, 0.999999);
    core->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    core->glBindVertexArray(currentModel->VAOs[2]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_TRIANGLES, 0, currentModel->information.size() / 6);
    core->glDepthRange(0, 1);
}

void ModelDraw::drawCrossField() {
    loadCrossFieldToVBO();
    core->glLineWidth(1);
    shaderProgram.setUniformValue("colormode", 3);
    shaderProgram.setUniformValue("color", QVector4D(30.0 / 255, 78.0 / 255, 252.0 / 255, 1.0));
    core->glDepthRange(0, 0.999998);
    core->glBindVertexArray(currentModel->VAOs[3]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_LINES, 0, currentModel->crossField.size() / 3);
    core->glDepthRange(0, 1);
}

void ModelDraw::drawDrawItem() {
    loadDrawItemToVBO();
    core->glPointSize(10);
    core->glLineWidth(5);
    shaderProgram.setUniformValue("colormode", 4);
    core->glDepthRange(0, 0.99999);
    core->glBindVertexArray(dVAO[0]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_POINTS, 0, drawItem.point.size() / 6);
    core->glBindVertexArray(dVAO[1]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_LINES, 0, drawItem.edge.size() / 6);
    core->glBindVertexArray(dVAO[2]);    // 前面已经记录了VBO和EBO现在只需一步调用即可
    core->glDrawArrays(GL_TRIANGLES, 0, drawItem.face.size() / 6);
    core->glDepthRange(0, 1);
}

/*=====================================鼠标绘制事件=========================================*/

void ModelDraw::mousePressEvent(QMouseEvent *_event) {
    if (!currentModel) return;
    switch (editModel) {
        case MODELVIEW:
        case MODELEDIT: {
            lastpoint2 = _event->pos();
            //makeCurrent();
            lastpointok = MapToSphere(lastpoint2, lastpoint3);
            mouseMode = _event->button();
            //update();
            break;
        }
        case PICKITEM: {
            if (_event->button() == Qt::LeftButton) {
                float winX = (float) (_event->x() * 2 - width()) / (width());    // 窗口坐标，范围在[-1,1]之内
                float winY = -(float) (_event->y() * 2 - height()) / (height());    // 窗口坐标，范围在[-1,1]之内
                pickItem(winX, winY);
                //pickPoint(winX,winY);
            } else if (_event->button() == Qt::RightButton) { // 鼠标右键单击绘制当前选点同深度的点
                float winX = (float) (_event->x() * 2 - width()) / (width());    // 窗口坐标，范围在[-1,1]之内
                float winY = -(float) (_event->y() * 2 - height()) / (height());    // 窗口坐标，范围在[-1,1]之内
                double p[3];
                pick_point_with_depth(winX, winY, p, pickedItemPosition);
                std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
            }
            lastpoint2 = _event->pos();
            makeCurrent();
            lastpointok = MapToSphere(lastpoint2, lastpoint3);
            mouseMode = _event->button();
            update();
            break;
        }
        case MODELCUT: {
            lineBeginPoint = QVector2D((double) (_event->x() * 2 - width()) / (width()),
                                       -(double) (_event->y() * 2 - height()) / (height()));
            makeCurrent();
            lastpointok = true;
            update();
            break;
        }
    }
}

void ModelDraw::mouseMoveEvent(QMouseEvent *_event) {
    if (!currentModel) return;
    switch (editModel) {
        case MODELVIEW: {
            QPoint newPoint2D = _event->pos();
            this->setCursor(Qt::SizeAllCursor);
            //makeCurrent();
            if (lastpointok) {
                switch (mouseMode) {
                    // 鼠标左键旋转视角
                    case Qt::LeftButton:ModelMoveState = true;
                        ViewRotate(newPoint2D);
                        break;
                        // 鼠标右键移动视角
                    case Qt::RightButton:ModelMoveState = true;
                        ViewTranslation(newPoint2D);
                        break;

                    default:break;
                }
            }
            lastpoint2 = newPoint2D;
            lastpointok = MapToSphere(lastpoint2, lastpoint3);
            //update();
            break;
        }
        case MODELEDIT: {
            QPoint newPoint2D = _event->pos();
            this->setCursor(Qt::SizeAllCursor);
            //makeCurrent();
            if (lastpointok) {
                switch (mouseMode) {
                    // 鼠标左键旋转模型
                    case Qt::LeftButton:ModelMoveState = true;
                        Rotation(newPoint2D);
                        break;
                        // 鼠标右键移动模型
                    case Qt::RightButton:ModelMoveState = true;
                        Translation(newPoint2D);
                        break;
//                        // 鼠标右键移动视角
//                    case Qt::RightButton:
//                        ModelMoveState = true;
//                        ViewRotate(newPoint2D);
//                        break;
                    default:break;
                }
            }
            lastpoint2 = newPoint2D;
            lastpointok = MapToSphere(lastpoint2, lastpoint3);
            //update();
            break;
        }
        case PICKITEM: {
            this->setCursor(Qt::PointingHandCursor);
            QPoint newPoint2D = _event->pos();
            makeCurrent();
            if (lastpointok) {
                // 可以鼠标右键拖拽来实现PickItem位置的移动（此功能只是试用）
                if (mouseMode == Qt::RightButton) {
                    PickItemTranslation(newPoint2D);    // 根据点的位置
                    PickItemTranslate();
                }
            }
            lastpoint2 = newPoint2D;
            lastpointok = MapToSphere(lastpoint2, lastpoint3);
            update();
            break;
        }
        case MODELCUT: {
            lineEndPoint = QVector2D((double) (_event->x() * 2 - width()) / (width()),
                                     -(double) (_event->y() * 2 - height()) / (height()));
            this->setCursor(Qt::CrossCursor);
            makeCurrent();
            if (lastpointok) {
                //calcCutLine(lineBeginPoint, lineEndPoint);
            }
            //update();
            break;
        }
        default:break;
    }
    update();
}

void ModelDraw::mouseReleaseEvent(QMouseEvent *_event) {
    //assert(mouseMode < N_MOUSE_MODES);
    mouseMode = Qt::NoButton;
    lastpointok = false;
    ModelMoveState = false;
    update();
}

void ModelDraw::wheelEvent(QWheelEvent *_event) {
    if (!currentModel) return;
    switch (editModel) {
        case MODELVIEW: {
            double d = _event->delta() / 120.0 * 0.2 * radius;
            ViewTranslate(Vector3d(0.0, 0.0, d));
            break;
        }
        case MODELEDIT: {
            double s = 0.03;// 代表缩放速度
            double d = _event->delta() / 120.0 * s;
            float scale = 1 + d;
            currentModel->modelScale *= scale;
            ModelScale(Vector3d(scale, scale, scale));
            break;
        }
    }
    update();
}

void ModelDraw::keyPressEvent(QKeyEvent *_event) {
    switch (_event->key()) {
        case Qt::Key_Escape:qApp->quit();
            break;
    }
    _event->ignore();
}

void ModelDraw::keyReleaseEvent(QKeyEvent *_event) {
    _event->ignore();
}

void ModelDraw::LoadRotation(void) {
    LoadCopyModelViewMatrix();
    update();
}

void ModelDraw::ResetView(void) {
    ResetModelviewMatrix();
    viewCenter();
    update();
}

void ModelDraw::viewCenter() {
    update();
}

void ModelDraw::PickItemTranslation(const QPoint &p) {
    pickItemMoveMatrix.setToIdentity();
    double z = -(viewMatrix(2, 3) / viewMatrix(2, 2));        // 右键拖动的距离与模型离视角的远近进行绑定（使拖动更流畅）

    double w = width();
    double h = height();
    double aspect = w / h;
    double near_plane = 0.01 * radius;
    double top = tan(45.0 / 2.0f * M_PI / 180.0f) * near_plane;
    double right = aspect * top;

    double dx = p.x() - lastpoint2.x();
    double dy = p.y() - lastpoint2.y();

    QVector4D trans(2.0 * dx / w * right / near_plane * z, -2.0 * dy / h * top / near_plane * z, 0.0f, 1);
    trans = currentModel->rotateMatrix.inverted() * viewRotateMatrix.inverted() * trans;
    std::cout << trans[0] << " " << trans[1] << " " << trans[2] << " " << std::endl;
    pickItemMoveMatrix.translate(trans[0], trans[1], trans[2]);
}

void ModelDraw::Translate(const Vector3d &_trans) {
    float x = _trans[0];
    float y = _trans[1];
    float z = _trans[2];
    QVector4D trans = QVector4D{x, y, z, 1.0f};
    trans = currentModel->rotateMatrix.inverted() * tempViewRotateMatrix.inverted() * trans;
    float scale = currentModel->modelScale;
    currentModel->modelMatrix.translate(trans[0] / scale, trans[1] / scale, trans[2] / scale);
}

void ModelDraw::ViewTranslate(const Vector3d &_trans) {
    viewMatrix.translate(_trans[0], _trans[1], _trans[2]);
}

void ModelDraw::ModelScale(const Vector3d &_scale) {
    currentModel->modelMatrix.scale(_scale[0], _scale[1], _scale[2]);
}

void ModelDraw::Rotate(const Vector3d &_axis, const double &_angle) {
    QMatrix4x4 tempMatrix;
    QMatrix4x4 tempRotateMatrix;
    // 由于有些模型移动之后的center并不在坐标原点，需要把center先移到坐标原点再旋转
    //tempMatrix.translate(currentModel->modelMatrix(0, 3), currentModel->modelMatrix(1, 3), currentModel->modelMatrix(2, 3));
    tempMatrix.translate(centerX, centerY, centerZ);
    QVector4D view(_axis[0], _axis[1], _axis[2], 1);
    view = tempViewRotateMatrix.inverted() * view;
    tempMatrix.rotate(_angle, view.x(), view.y(), view.z());
    tempRotateMatrix.rotate(_angle, view.x(), view.y(), view.z());
    // 再把模型移回原坐标
    tempMatrix.translate(-centerX, -centerY, -centerZ);
    //tempMatrix.translate(-currentModel->modelMatrix(0, 3), -currentModel->modelMatrix(1, 3), -currentModel->modelMatrix(2, 3));
    currentModel->modelMatrix = tempMatrix * currentModel->modelMatrix;        // 左乘的方式，使动态欧拉角改成静态欧拉角，解决方向旋转的问题
    currentModel->rotateMatrix =
        tempRotateMatrix * currentModel->rotateMatrix;    // rotateMatrix是用来储存旋转状态的（没有translate），模型法向量的旋转需要用到此矩阵
}

/*=====================================网格质量检测并可视化=========================================*/

void ModelDraw::paintSurfaceMeshMetric(double &_min, double &_max, std::vector<double> &values) {
    if (!currentModel || currentModel->structure != SURFACEMESH) return;
    if (meshMetric == OFF) {
        colorMode = LIGHT;
        return;
    }
    colorMode = COLOR;
    int faceSize = currentModel->surfaceMesh.fsize();
    bool rescale = false;// 标记是否需要对val进行重新缩放到[0,1]
    double v;
    _min = DBL_MAX;
    _max = DBL_MIN;
    for (int i = 0; i < faceSize; i++) {
        auto fh = MeshKernel::iGameFaceHandle{i};
        auto &f = currentModel->surfaceMesh.faces(fh);
        double val = 0; // val是基于value重新量化的值，取值范围为[0,MAX]，其中val越小代表质量越好，0代表最优值
        double value = 0; // value为真实计算值，值的大小取决于算法
        int sides = f.size();
        if (sides == 3) {
            switch (meshMetric) {
                case TRI_Area: {

                    value = TriQuality::Area(fh, currentModel->surfaceMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case TRI_MaxAngle: {
                    value = TriQuality::MaxAngle(fh, currentModel->surfaceMesh);
                    val = std::abs(60 - value);
                    rescale = true;
                    break;
                }
                case TRI_MinAngle: {
                    value = TriQuality::MinAngle(fh, currentModel->surfaceMesh);
                    val = std::abs(60 - value);
                    rescale = true;
                    break;
                }
                case TRI_Jacobian: {
                    value = TriQuality::Jacobian(fh, currentModel->surfaceMesh);
                    val = std::abs(1.0 - value);
                    rescale = true;
                    break;
                }
                case TRI_AspectRatio: {
                    value = TriQuality::AspectRatio(fh, currentModel->surfaceMesh);
                    val = value - 1.0;
                    rescale = true;
                    break;
                }
                case TRI_EdgeRatio: {
                    value = TriQuality::EdgeRatio(fh, currentModel->surfaceMesh);
                    val = value - 1.0;
                    rescale = true;
                    break;
                }
            }
        } else if (sides == 4) {
            switch (meshMetric) {
                case QUAD_Area: {
                    value = QuadQuality::Area(fh, currentModel->surfaceMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case QUAD_MaxAngle: {
                    value = QuadQuality::MaxAngle(fh, currentModel->surfaceMesh);
                    val = std::abs(90 - value);
                    rescale = true;
                    break;
                }
                case QUAD_MinAngle: {
                    value = QuadQuality::MinAngle(fh, currentModel->surfaceMesh);
                    val = std::abs(90 - value);
                    rescale = true;
                    break;
                }
                case QUAD_Jacobian: {
                    value = QuadQuality::Jacobian(fh, currentModel->surfaceMesh);
                    val = std::abs(1 - value);
                    rescale = true;
                    break;
                }
                case QUAD_AspectRatio: {
                    value = QuadQuality::AspectRatio(fh, currentModel->surfaceMesh);
                    val = value - 1.0;
                    rescale = true;
                    break;
                }
                case QUAD_EdgeRatio: {
                    value = QuadQuality::EdgeRatio(fh, currentModel->surfaceMesh);
                    val = value - 1.0;
                    rescale = true;
                    break;
                }
                case QUAD_Warpage: {
                    value = QuadQuality::Warpage(fh, currentModel->surfaceMesh);
                    val = value;
                    break;
                }
                case QUAD_Taper: {
                    value = QuadQuality::Taper(fh, currentModel->surfaceMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case QUAD_Skew: {
                    value = QuadQuality::Skew(fh, currentModel->surfaceMesh);
                    val = value;  // value=0代表歪斜度为0（我猜
                    break;
                }
            }
        }

        values.emplace_back(value);
        _min = std::min(_min, value);
        _max = std::max(_max, value);
        f.setValue(val);
    }

    if (rescale) {
        std::vector<double> array_value(faceSize);
        double temp_min = DBL_MAX;
        double temp_max = DBL_MIN;
        for (int i = 0; i < faceSize; i++) {
            auto fh = MeshKernel::iGameFaceHandle{i};
            auto &f = currentModel->surfaceMesh.faces(fh);
            double val = f.getValue();
            array_value[i] = val;
            temp_min = std::min(temp_min, val);
            temp_max = std::max(temp_max, val);
        }
        double scale = temp_max - temp_min;
        for (int i = 0; i < faceSize; i++) {
            auto fh = MeshKernel::iGameFaceHandle{i};
            auto &f = currentModel->surfaceMesh.faces(fh);
            double value = (array_value[i] - temp_min) / scale;
            f.setValue(value);
        }
    }

    updateCurrentMesh();
}

void ModelDraw::paintVolumeMeshMetric(double &_min, double &_max, std::vector<double> &values) {
    if (!currentModel || currentModel->structure != VOLUMEMESH) return;
    if (meshMetric == OFF) {
        colorMode = LIGHT;
        return;
    }
    colorMode = COLOR;
    int cellSize = currentModel->volumeMesh.CellSize();
    bool rescale = false;// 标记是否需要对val进行重新缩放到[0,1]
    double v;
    _min = DBL_MAX;
    _max = DBL_MIN;
    if (meshMetric == HEX_RelativeSizeSquared) {
        //先求平均体积
        v = MeshMath::get_volume_tetahedral_mesh(currentModel->volumeMesh);
        v = v / currentModel->volumeMesh.CellSize();
    }
    for (int i = 0; i < cellSize; i++) {
        auto ch = MeshKernel::iGameCellHandle{i};
        auto &c = currentModel->volumeMesh.cells(ch);
        double val; // val是基于value重新量化的值，取值范围为[0,MAX]，其中val越小代表质量越好，0代表最优值
        double value; // value为真实计算值，值的大小取决于算法
        int faces = c.faces_size();
        if (faces == 4) {
            switch (meshMetric) {
                case TET_Volume: {
                    value = TetQuality::GetVolumeOfCell(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case TET_AspectRatio: {
                    value = TetQuality::GetAspectRatioOfCell(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case TET_Jacobian: {
                    value = TetQuality::GetJacobianOfCell(ch, currentModel->volumeMesh);
                    val = std::abs(std::sqrt(2) / 2 - value);
                    rescale = true;
                    break;
                }
                case TET_CollapseRatio: {
                    value = TetQuality::GetCollapseRatioOfCell(ch, currentModel->volumeMesh);
                    val = std::abs(std::sqrt(6) / 3 - value);
                    rescale = true;
                    break;
                }
                case TET_Skew: {
                    value = TetQuality::GetVolSkewOfCell(ch, currentModel->volumeMesh);
                    val = value;
                    break;
                }
                case TET_InternalAngle: {
                    value = TetQuality::GetMinInternalAnglesOfCell(ch, currentModel->volumeMesh);
                    val = std::abs(60 - value);
                    rescale = true;
                    break;
                }
                case TET_VolAspectRatio: {
                    value = TetQuality::GetVolAspectRatioOfCell(ch, currentModel->volumeMesh);
                    val = std::abs(std::sqrt(3) / 2 - value);
                    rescale = true;
                    break;
                }
                case TET_EquiangleSkew: {
                    value = TetQuality::GetEquiangleSkewnessOfCell(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
            }
        } else if (faces == 6) {
            switch (meshMetric) {
                case HEX_Volume: {
                    value = HexQuality::hex_volume(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case HEX_Taper: {
                    value = HexQuality::hex_taper(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case HEX_Jacobian: {
                    value = HexQuality::hex_jacobian(ch, currentModel->volumeMesh);
                    val = std::abs(1.0 - value);
                    rescale = true;
                    break;
                }
                case HEX_EdgeRatio: {
                    value = HexQuality::hex_edge_ratio(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case HEX_MaxEdgeRatio: {
                    value = HexQuality::hex_maximum_edge_ratio(ch, currentModel->volumeMesh);
                    val = value;
                    rescale = true;
                    break;
                }
                case HEX_Skew: {
                    value = HexQuality::hex_skew(ch, currentModel->volumeMesh);
                    val = value;
                    break;
                }
                case HEX_Strech: {
                    value = HexQuality::hex_strech(ch, currentModel->volumeMesh);
                    val = 1 - value;
                    break;
                }
                case HEX_Diagonal: {
                    value = HexQuality::hex_diagonal(ch, currentModel->volumeMesh);
                    val = 1 - value;
                    break;
                }
                case HEX_RelativeSizeSquared: {
                    value = HexQuality::hex_relative_size_squared(ch, currentModel->volumeMesh, v);
                    val = value;
                    break;
                }
            }
        }

        values.emplace_back(value);
        _min = std::min(_min, value);
        _max = std::max(_max, value);
        c.setValue(val);
    }

    if (rescale) {
        std::vector<double> array_value(cellSize);
        double temp_min = DBL_MAX;
        double temp_max = DBL_MIN;
        for (int i = 0; i < cellSize; i++) {
            auto ch = MeshKernel::iGameCellHandle{i};
            auto &c = currentModel->volumeMesh.cells(ch);
            double val = c.getValue();
            array_value[i] = val;
            temp_min = std::min(temp_min, val);
            temp_max = std::max(temp_max, val);
        }
        double scale = temp_max - temp_min;
        for (int i = 0; i < cellSize; i++) {
            auto ch = MeshKernel::iGameCellHandle{i};
            auto &c = currentModel->volumeMesh.cells(ch);
            double value = (array_value[i] - temp_min) / scale;
            c.setValue(value);
        }
    }

    updateCurrentMesh();
}

void ModelDraw::valueToRGB(double value, float &R, float &G, float &B) {
    // value越小，颜色越蓝；value越大，颜色越红
//    if(value > 1.0001 || value < -0.0001){
//        printf("value is illegal !\n");
//        return;
//    }
    if (value > 0.5) {
        R = 1.0;
        G = 1.0 - (value - 0.5) * 2;
        B = 1.0 - (value - 0.5) * 2;
    } else if (value <= 0.5) {
        R = 1.0 - (0.5 - value) * 2;
        G = 1.0 - (0.5 - value) * 2;
        B = 1.0;
    }

}
