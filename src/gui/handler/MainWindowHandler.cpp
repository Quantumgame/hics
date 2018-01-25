#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) {

    mainWindow = new MainWindow();
    startWidget = new StartWidget(neuralNets, platforms, operationModes);
    resultWidget = new ResultWidget();
    detailDialog = new DetailDialog();

    mainWindow->addWidgetToStack(startWidget);
    mainWindow->addWidgetToStack(resultWidget);

    mainWindow->setCurrentWidget(startWidget);
    //TODO initialze result and detail widget and add them to the stack

    connect(startWidget->getClassificationQPushButton(), SIGNAL(clicked()), this, SLOT(setClassificationRequestState()));
    connect(resultWidget->getReturnQPushButton(), SIGNAL(clicked()), this, SLOT(processReturnQPushButton()));
    connect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked()), this, SLOT(processDetailQPushButton()));
}

void MainWindowHandler::setClassificationRequestState(){
    NetInfo neuralNet = startWidget->getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget->getSelectedPlatforms();
    OperationMode m(OperationMode::HighPower); /*!< TODO change this when string mapping is implemented*/
    bool aggregate = startWidget->isAggregated();
    std::map<QString, QImage> userImgs = startWidget->getSelectedImages();

    ClassificationRequest request(neuralNet, platforms, m, aggregate, userImgs);
    this->classificationRequestState = &request;

    notify();

    //TODO here maybe display loading screen/bar
}

ClassificationRequest* MainWindowHandler::getClassificationRequestState(){
    if(classificationRequestState){
        return classificationRequestState;
    } else {
        setClassificationRequestState();
        return classificationRequestState;
    }
}

void MainWindowHandler::processClassificationResult(const ClassificationResult &classificationResult){
    resultWidget->displayResults(classificationResult);
    detailDialog->insertDetails(&classificationResult);
    mainWindow->setCurrentWidget(resultWidget);
}

void MainWindowHandler::processReturnQPushButton(){
    //TODO do this also when resultWidget gets closed
    //TODO reset detailDialog
    mainWindow->setCurrentWidget(startWidget);
    ResultWidget* temp = resultWidget;
    resultWidget = new ResultWidget();
    delete temp;
}

void MainWindowHandler::processDetailQPushButton(){
    detailDialog->show();
}
