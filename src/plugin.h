//
// Created by 17203 on 2025/8/31.
//

#ifndef BEHAVIORTREE_TO_MAYA_TEST_PLUGIN_H
#define BEHAVIORTREE_TO_MAYA_TEST_PLUGIN_H

#pragma once
#include <maya/MPxCommand.h>
#include <maya/MFnPlugin.h>
#include <maya/MGlobal.h>
#include <maya/MSyntax.h>


#include "behaviortree_cpp/bt_factory.h"
#include "TestAction.h"


#pragma comment(lib, "OpenMaya.lib")
#pragma comment(lib, "Foundation.lib")

using namespace BT;

class Behaviortree: public MPxCommand
{
public:
    static MSyntax newSyntax();

    MStatus doIt(const MArgList& args);
    static void* creator();
    static MStatus initialize();

    static void loadXmlFromFile(const std::string& filename);

public:
    static MString deformerName;
    static MTypeId id;

private:
    static const char* xml_text;
    static std::string xml_content;

    void* factoryPtr = nullptr;
};



#endif //BEHAVIORTREE_TO_MAYA_TEST_PLUGIN_H