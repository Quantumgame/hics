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

#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <ClassificationResult.h>
#include <QtWidgets/QLabel>

namespace Ui {
    class ResultWidget;
}

/**
 * @class ResultWidget
 *
 * @brief ResultWidget is a custom QWidget and is used to display the result page of the GUI.
 *
 * ResultWidget inherits QWidget and is therefore also a custom QWidget. It represents the result page of the GUI, that
 * is, when a classification is finished and the user wants to see the classified image and the Top-5 probability to
 * which labels the images match.
 *
 * It provides an interface for MainWindowHandler to abstract away the Qt objects from the rest of the software. The
 * method displayResults() can be called with a ClassificationResult as parameter which will then initialize the user
 * interface of ResultWidget with the needed data.
 *
 * @author Patrick Deubel
 */
class ResultWidget : public QWidget {

Q_OBJECT

private:

    /* Structs*/

    struct ClassificationLabel /*!< Maps the classification label and its percentage to the objects which are displaying them*/
    {
        std::string name; /*!< Classification label*/
        QLabel *nameDisplay; /*!< Displayed object*/

        float percentage; /*< Percentage label*/
        QLabel *percentageDisplay; /*!< Displayed object */
    };

    struct ImageDisplay
    {
        ImageResult *imageResult;

        std::string filePath;
        QLabel *filePathDisplay;
        QLabel *imageDisplay;
    };

    struct ResultDisplay
    {
        ImageResult *imageResult;

        std::pair<std::string, QLabel *> topResult;
        std::vector<ClassificationLabel *> results;
    };

    /* Attributes*/

    Ui::ResultWidget *ui;

    const QString PERCENTAGE_BAR_COLOR = "rgba(255, 0, 0, 0.6)";
    const int NUMERATOR_TEXT_PERCENTAGE_RATIO = 2;
    const int DENOMINATOR_TEXT_PERCENTAGE_RATIO = 3;

    std::vector<ResultDisplay *> resultDisplays;
    std::vector<ImageDisplay *> imageDisplays;

    /* Methods*/

    QFrame *createImageLayout(const std::string &filePath, ImageDisplay *imageDisplay);

    QFrame *createResultLayout(std::vector<std::pair<std::string, float>> &result, ResultDisplay *resultDisplay);

    QString shortLink(const std::string &link);

    void clearLayout(QLayout *layout);

    void resize();

public:

    /**
     * @brief The standard constructor initializes the ResultWidget
     *
     * It makes the QScrollArea resizable, which later holds the images and their (not aggregated) results and assings
     * the image layout to its container.
     *
     * @param parent is an optional parent widget
     */
    explicit ResultWidget(QWidget *parent = 0);

    /**
     * @brief Destructor for ResultWidget
     *
     * Delets the ui and all its child widgets, as well as all allocated memory in ResultWidget.
     */
    ~ResultWidget() override;

    /**
     * @brief displayResults() takes a ClassificationResult and displays its results in the ResultWidget
     *
     * displayResults() displays the images and their file path together with its classification results. If the results
     * are aggregated, only the images and their file paths are displayed in the scroll widget and next to it the
     * aggregated result.
     * If the results are not aggregated, every image gets displayed together with its result in the scroll widget.
     *
     * @param classificationResult has the classification results
     */
    void displayResults(ClassificationResult *classificationResult);

    /**
     * @brief Returns the QPushButton used to display the details
     * @return the detailsQPushButton
     */
    QPushButton *getDetailsQPushButton();

    /**
     * @brief Returns the QPushButton used to return to the starting page of the GUI
     * @return the returnQPushButton
     */
    QPushButton *getReturnQPushButton();

    /**
     * @brief getImagesQGridLayout returns the layout in which the images and their results are stored
     * @return imagesQGridLayout
     */
    QGridLayout *getImagesQGridLayout();

    /**
     * @brief getResultDisplays returns the ResultDisplay structures for an easy access to the result layouts and their
     *        content
     * @return the ResultDisplays structures
     */
    const std::vector<ResultDisplay *> &getResultDisplays() const;

protected:

    void resizeEvent(QResizeEvent * event) override;
};