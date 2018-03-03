/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <QtCore/QThread>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::vector<NetInfo *> &neuralNets, std::vector<PlatformInfo *> &platforms,
                                     std::vector<OperationMode> &operationModes) {

    //Initialize the used UI's
    mainWindow = new MainWindow();
    startWidget = new StartWidget(neuralNets, platforms, operationModes, mainWindow);
    resultWidget = new ResultWidget();
    detailDialog = new DetailDialog(mainWindow);

    //mainWindow's QStackedWidget will be the main display
    mainWindow->addWidgetToStack(startWidget);
    mainWindow->addWidgetToStack(resultWidget);

    mainWindow->setCurrentWidget(startWidget);

    connectAll();
}

void MainWindowHandler::abortClassification() {
    cancelClassification = true;
}

void MainWindowHandler::setClassificationRequestState() {
    delete classificationRequestState;
    classificationRequestState = nullptr;

    NetInfo neuralNet = startWidget->getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget->getSelectedPlatforms();
    OperationMode mode = startWidget->getSelectedOperationMode();
    bool aggregate = startWidget->isAggregated();
    std::map<QString, QImage> userImgs = startWidget->getSelectedImages();

    if (!platforms.empty() && !userImgs.empty()) {
        classificationRequestState = new ClassificationRequest(neuralNet, platforms, mode, aggregate, userImgs);

        workerThread = new WorkerThread(this);
        connect(workerThread, &WorkerThread::resultReady, this, &MainWindowHandler::processClassificationResult);
        connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
        workerThread->start();

        //Displays a busy loading progress bar and disables all widgets
        startWidget->displayProgress();
    }
}

void MainWindowHandler::displayErrorMessage(const QString &errorMessage) {
    startWidget->resetProgressDisplay();
    startWidget->displayErrorMessage(errorMessage);
}

ClassificationRequest *MainWindowHandler::getClassificationRequestState() {
    return classificationRequestState;
}

void MainWindowHandler::processClassificationResult(ClassificationResult *classificationResult) {
    //If classificationResult is a nullptr the classification went wrong
    if (classificationResult) {
        disconnectAll();
        mainWindow->removeWidgetFromStack(resultWidget);
        delete resultWidget;
        resultWidget = new ResultWidget;
        connectAll();
        //Initialize the results in resultWidget
        resultWidget->displayResults(classificationResult);
        mainWindow->addWidgetToStack(resultWidget);
        //Initialize the details in detailDialog
        detailDialog->insertDetails(classificationResult);
        //Change the currently displayed widget to resultWidget
        mainWindow->setCurrentWidget(resultWidget);
    } else {
        //Check if an exception has been set during the classification
        if (exceptionptr) {
            try {
                //Since the exception is stored as a exception pointer we need to rethrow it to catch the exception
                std::rethrow_exception(exceptionptr);
            } catch (std::exception &e) {
                //Display the error message and reset the loading state of the GUI to the normal starting page
                displayErrorMessage(QString::fromStdString(e.what()));
                exceptionptr = nullptr;
            }
        } else {
            //This case should never occur, but for safety measures the GUI should be resetted
            startWidget->resetProgressDisplay();
        }
    }

    cancelClassification = false;
}

void MainWindowHandler::processReturnQPushButton() {
    //Enable the widgets in StartWidget again and remove the progress bar
    startWidget->resetProgressDisplay();
    cancelClassification = false;

    mainWindow->setCurrentWidget(startWidget);

    disconnectAll();
    mainWindow->removeWidgetFromStack(resultWidget);
    delete resultWidget;

    resultWidget = new ResultWidget(mainWindow);
    mainWindow->addWidgetToStack(resultWidget);

    delete detailDialog;
    detailDialog = new DetailDialog(mainWindow);
    connectAll();
}

void MainWindowHandler::processDetailQPushButton() {
    detailDialog->show();
}

void MainWindowHandler::connectAll() {
    //Starts the classification
    connect(startWidget->getClassificationQPushButton(), SIGNAL(clicked(bool)), this,
            SLOT(setClassificationRequestState()));

    connect(startWidget->getCancelProgressButton(), SIGNAL(clicked(bool)), this, SLOT(abortClassification()));

    //Deletes resultWidget
    connect(resultWidget->getReturnQPushButton(), SIGNAL(clicked(bool)), this, SLOT(processReturnQPushButton()));

    //Opens the detailDialog
    connect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked(bool)), this, SLOT(processDetailQPushButton()));

    //Resets detailDialog and resultWidget when resultWidget is destroyed; display startWidget
    connect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton())); //TODO Check if this works
}

void MainWindowHandler::disconnectAll() {
    disconnect(startWidget->getClassificationQPushButton(), SIGNAL(clicked()), this,
               SLOT(setClassificationRequestState()));
    disconnect(startWidget->getCancelProgressButton(), SIGNAL(clicked()), this, SLOT(abortClassification()));
    disconnect(resultWidget->getReturnQPushButton(), SIGNAL(clicked()), this, SLOT(processReturnQPushButton()));
    disconnect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked()), this, SLOT(processDetailQPushButton()));
    disconnect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton()));
}

MainWindowHandler::~MainWindowHandler() {
    disconnectAll();
    delete detailDialog;
    delete resultWidget;
    delete startWidget;
    delete mainWindow;
    delete classificationRequestState;
}

bool MainWindowHandler::isClassificationAborted() {
    return cancelClassification;
}

MainWindow *MainWindowHandler::getMainWindow() const {
    return mainWindow;
}

StartWidget *MainWindowHandler::getStartWidget() const {
    return startWidget;
}

ResultWidget *MainWindowHandler::getResultWidget() const {
    return resultWidget;
}

DetailDialog *MainWindowHandler::getDetailDialog() const {
    return detailDialog;
}

void MainWindowHandler::setExceptionptr(const std::exception_ptr &exceptionptr) {
    MainWindowHandler::exceptionptr = exceptionptr;
}
