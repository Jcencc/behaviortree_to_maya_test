//
// Created by 17203 on 2025/8/31.
//

#include "plugin.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include <maya/MGlobal.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>
#include <maya/MStatus.h>
#include <maya/MArgDatabase.h>
#include <maya/MItSelectionList.h>


MString Behaviortree::deformerName = "xsSimpleDeformer";
MTypeId Behaviortree::id = MTypeId(0x7f7f7);
const char* Behaviortree::xml_text;
std::string Behaviortree::xml_content;


MSyntax Behaviortree::newSyntax() {

    MSyntax syntax;
    syntax.addArg(MSyntax::kString);
    return syntax;
}

MStatus Behaviortree::doIt(const MArgList& args)
{
    MGlobal::displayInfo(MString("my C++ FuncTest!"));

    MArgDatabase argData(syntax(), args);
    MSelectionList selection;

    MString firstArg;
    if (argData.getCommandArgument(0, firstArg) == MS::kSuccess) {
        MGlobal::displayInfo("First argument: " + firstArg);
    } else {
        MGlobal::displayError("Failed to get the first argument.");
        return MS::kFailure;
    }
    try {
        loadXmlFromFile(firstArg.asChar());
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    BehaviorTreeFactory factory;
    factory.registerNodeType<TestAction>("TestAction");
    factory.registerNodeType<SetBlackboardNode>("SetBlackboardNode");
    auto tree = factory.createTreeFromText(xml_text);

    tree.tickWhileRunning();

    return MS::kSuccess;
}

void* Behaviortree::creator()
{
    return new Behaviortree;
}

MStatus Behaviortree::initialize() {
    return MStatus::kSuccess;
}

void Behaviortree::loadXmlFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("not open XML file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    xml_content = buffer.str();
    xml_text = xml_content.c_str();
}


// MStatus initializePlugin( MObject obj )
// {
//     MStatus result;
//     MFnPlugin plugin( obj);
//     MFnPlugin mPlugin(obj, "Jcen", "1.0", "Any");
//     result = plugin.registerNode( Behaviortree::deformerName, Behaviortree::id,
//                                     &Behaviortree::creator, &Behaviortree::initialize,
//                                     MPxNode::kDeformerNode );
//
//     return result;
// }
//
// MStatus uninitializePlugin( MObject obj)
// {
//     MStatus result;
//     MFnPlugin plugin( obj );
//     result = plugin.deregisterNode(Behaviortree::id);
//     return result;
// }


MStatus initializePlugin(MObject mObj)
{
	MFnPlugin mPlugin(mObj, "Jcen", "1.0", "Any");
	MStatus status = mPlugin.registerCommand("behaviortree_to_maya_test", Behaviortree::creator, Behaviortree::newSyntax);
    if (!status) {
        status.perror("registerCommand");
        return status;
    }
	return MS::kSuccess;
}

MStatus uninitializePlugin(MObject mobj)
{
	MFnPlugin mPlugin(mobj);
	MStatus status = mPlugin.deregisterCommand("behaviortree_to_maya_test");
    if (!status) {
        status.perror("deregisterCommand");
        return status;
    }
	return MS::kSuccess;
}