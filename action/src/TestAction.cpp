//
// Created by 17203 on 2025/8/31.
//

#include "../include/TestAction.h"
#include <maya/MGlobal.h>
#include <maya/MItSelectionList.h>
#include <maya/MFnMesh.h>
#include <maya/MPointArray.h>

TestAction::TestAction(const std::string &name, const NodeConfig &config):
    SyncActionNode(name, config)
{
}

NodeStatus TestAction::tick() {
    std::string msg;
    getInput("message", msg);
    std::string value;
    try {
        value = config().blackboard->get<std::string>("value");
        MGlobal::displayInfo(MString(value.c_str()));
    } catch (const std::exception& e) {
        value = "";
        MGlobal::displayInfo(MString(e.what()));
    }
    std::string output_key;
    try {
        output_key = config().blackboard->get<std::string>("output_key");
        MGlobal::displayInfo(MString(output_key.c_str()));
    } catch (const std::exception& e) {

        output_key = "";
        MGlobal::displayInfo(MString(e.what()));
    }


    MGlobal::executeCommand("");
    MGlobal::displayInfo(MString(msg.c_str()));


    MSelectionList selection;
    MGlobal::getActiveSelectionList(selection);

    MItSelectionList iter(selection, MFn::kMesh);
    MGlobal::displayInfo(MString("slect mesh run!"));
    if (selection.length() == 0) {
        MGlobal::displayInfo("No objects selected.");
        return NodeStatus::SUCCESS;
    }
    //std::vector<std::thread> threads;
    for (; !iter.isDone(); iter.next()) {
        MObject node;
        iter.getDependNode(node);
        MFnMesh fnMesh(node);
        MString name = fnMesh.name();
        // MPointArray vertices;
        // fnMesh.getPoints(vertices);

        // for (unsigned int i = 0; i < vertices.length(); i++) {
        //     MPoint vertex = vertices[i];
        //     MGlobal::displayInfo(MString("Vertex ") + i + ": (" + vertex.x + ", " + vertex.y + ", " + vertex.z + ")");
        // }
        // fnMesh.setPoints(vertices);
        MGlobal::displayInfo(MString("Selected mesh name: ") + name);
    }
    return NodeStatus::SUCCESS;
}


PortsList TestAction::providedPorts() {
    return {BT::InputPort<std::string>("message")};
}
