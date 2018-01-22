#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) :
startWidget(neuralNets, platforms, operationModes){

    mainWindow.addWidgetToStack(startWidget);
    mainWindow.setCurrentWidget(startWidget);

    //TODO initialze result and detail widget and add them to the stack

    connect(startWidget.getClassificationQPushButton, SIGNAL(clicked()), this, SLOT(setClassificationRequestState()));
}

void MainWindowHandler::setClassificationRequestState(){
    NetInfo selectedNet = startWidget.getSelectedNeuralNet();
    std::vector<PlatformInfo> selectedPlatforms = startWidget.getSelectedPlatforms();
    //TODO PlatformInfo, OperationMode, aggregateResults add them here, add the according functions to startWidget
}

ClassificationRequest MainWindowHandler::getClassificationRequestState(){
    throw NotImplementedException();
}

void MainWindowHandler::processClassificationResult(const ClassificationResult &classificationResult){
    throw NotImplementedException();
}

void MainWindowHandler::processReturnQPushButton(){
    throw NotImplementedException();
}

void MainWindowHandler::processDetailQPushButton(){
    throw NotImplementedException();
}
