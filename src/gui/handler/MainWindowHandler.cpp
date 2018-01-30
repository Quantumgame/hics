#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) {

    //Initialize the used UI's
    mainWindow = new MainWindow();
    startWidget = new StartWidget(neuralNets, platforms, operationModes, mainWindow);
    resultWidget = new ResultWidget(mainWindow);
    detailDialog = new DetailDialog(mainWindow);

    //mainWindow's QStackedWidget will be the main display
    mainWindow->addWidgetToStack(startWidget);
    mainWindow->addWidgetToStack(resultWidget);

    mainWindow->setCurrentWidget(startWidget);

    //Starts the classification
    connect(startWidget->getClassificationQPushButton(), SIGNAL(clicked()), this, SLOT(setClassificationRequestState()));

    //Deletes resultWidget
    connect(resultWidget->getReturnQPushButton(), SIGNAL(clicked()), this, SLOT(processReturnQPushButton()));

    //Opens the detailDialog
    connect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked()), this, SLOT(processDetailQPushButton()));

    //Resets detailDialog and resultWidget when resultWidget is destroyed; display startWidget
    connect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton())); //TODO Check if this works
}

void MainWindowHandler::setClassificationRequestState(){
    if(classificationRequestState){
        delete classificationRequestState;
    }

    NetInfo neuralNet = startWidget->getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget->getSelectedPlatforms();
    OperationMode m(OperationMode::HighPower); /*!< TODO change this when string mapping is implemented*/
    bool aggregate = startWidget->isAggregated();
    std::map<QString, QImage> userImgs = startWidget->getSelectedImages();

    classificationRequestState = new ClassificationRequest(neuralNet, platforms, m, aggregate, userImgs);

    //Notify all observers that the state has changed
    notify();

    //TODO here maybe display loading screen/bar
}

ClassificationRequest* MainWindowHandler::getClassificationRequestState(){
    return classificationRequestState;
}

void MainWindowHandler::processClassificationResult(const ClassificationResult &classificationResult){
    //Initialize the results in resultWidget
    resultWidget->displayResults(classificationResult);
    //Initialize the details in detailDialog
    detailDialog->insertDetails(&classificationResult);
    //Change the currently displayed widget to resultWidget
    mainWindow->setCurrentWidget(resultWidget);
}

void MainWindowHandler::processReturnQPushButton(){
    mainWindow->setCurrentWidget(startWidget);
    delete resultWidget;
    resultWidget = new ResultWidget(mainWindow);
    delete detailDialog;
    detailDialog = new DetailDialog(mainWindow);
}

void MainWindowHandler::processDetailQPushButton(){
    detailDialog->show();
}

MainWindowHandler::~MainWindowHandler(){
    if(classificationRequestState){
        delete classificationRequestState;
    }
}

MainWindow *MainWindowHandler::getMainWindow() const {
    return mainWindow;
}

StartWidget* MainWindowHandler::getStartWidget() const {
    return startWidget;
}

ResultWidget* MainWindowHandler::getResultWidget() const {
    return resultWidget;
}

DetailDialog *MainWindowHandler::getDetailDialog() const {
    return detailDialog;
}
