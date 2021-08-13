/*
 * Copyright:   2021 Johnathon Leong
 *
 * License:     License under GPL-3.0-or-later.
 *              Please refer to https://www.gnu.org/licenses/gpl-3.0.txt for more information on the
 *              terms of GPL-3.0 or relavent website for a later version of the GPL.
 *
 * Disclaimer:  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY
 *              EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *              OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 *              SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *              INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *              TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *              BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *              CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 *              WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:      Johnathon Leong
 *
 * Note:
 *
 * Version:     1.0.2
 * Date:        2021/08/11 (YYYY/MM/DD)
 * Change Log:  1. Updated the "Read Me" and the "About" details.
 *              2. Added a feature for the "About" to save its content.
 *
 * Version:     1.0.1
 * Date:        2021/08/10 (YYYY/MM/DD)
 * Change Log:  1. Updated the application selection page to include more applications
 *              2. Included a "Read Me" and a "About" selection to describe this software more.
 *
 * Version:     1.0.0
 * Date:        2021/07/29 (YYYY/MM/DD)
 * Change Log:  1. First release of learnappsselection.
 *              2. Implemented learnappsselection class.
 */

#include "learnappsselection.h"

#include <QDir>

#include "genericlibrarymaths.h"
#include "learnappfilling.h"
#include "learnappjumbling.h"
#include "learnapprecognizing.h"
#include "learnappspelling.h"
#include "learnlibrarycustomwidgets.h"
#include "learnlibraryfunctions.h"

#define LEARNAPPSSELECTION_VERSION_MAJOR 1
#define LEARNAPPSSELECTION_VERSION_MINOR 0
#define LEARNAPPSSELECTION_VERSION_PATCH 2

/**
 * @brief learnappsselection - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnappsselection::learnappsselection(QWidget * parent) : QWidget(parent) {
  initAttributes();
  initWidget();

  if (QDir("./pictures").exists() == false) {
    QDir().mkdir("./pictures");
    readme();
  }

  for (unsigned char i = 0; i < LEARNAPPSSELECTION_APPS_TOTAL_NUM; i++)
    connect(mpApps[i], SIGNAL(released()), this, SLOT(slot_mpAppsSelect()));
}

/**
 * @brief learnappsselection - Default destructor.
 */
learnappsselection::~learnappsselection() {
  for (unsigned long i = 0; i < LEARNAPPSSELECTION_APPS_TOTAL_NUM; i++)
    delete mpApps[i];
  delete mpDisplayApps;
  if (mpSelectedApp != nullptr)
    delete mpSelectedApp;
}

/**
 * @brief readme - Generate content for About
 */
void learnappsselection::about(void ) {
  QStringList message = mMessageBoxMsg;
  message.append("----------------------------------------------------");
  message.append("Click on \"Save\" to save this \"About\" content to this folder.");

  QMessageBox mpMessageBoxAbout;
  mpMessageBoxAbout.setTextFormat(Qt::RichText);
  mpMessageBoxAbout.setFont(QFont("Courier"));
  mpMessageBoxAbout.setWindowTitle("LEARN - About");
  mpMessageBoxAbout.setText(generateAboutMessage(message));
  mpMessageBoxAbout.setStandardButtons(QMessageBox::Save | QMessageBox::Ok);
  mpMessageBoxAbout.setDefaultButton(QMessageBox::Ok);

  int buttonClicked = mpMessageBoxAbout.exec();
  if (buttonClicked == QMessageBox::Save) {
    QString message = generateAboutMessage(mMessageBoxMsg, 1);
    FILE * ptr = fopen("./About.txt", "w");
    if (ptr != NULL) {
      fprintf(ptr, "%s", message.toStdString().c_str());
      fclose(ptr);
    }
  }
}

/**
 * @brief generateAboutMessage - Generate About message.
 * @param message              - The QStringList message to be generated into a QString message.
 * @param type                 - The type of message to be generated.
 *                               0 -> QString message for QMessageBox.
 *                               1 -> QString message for file.
 * @return                     - The generated message.
 */
QString learnappsselection::generateAboutMessage(QStringList message, unsigned char type) {
  QString msg;
  if (type > 1)
    type = 0;

  QString space   = type == 0 ? "&nbsp;" : " ";
  QString newline = type == 0 ? "<br>"   : "\n";

  for (int i = 0; i < message.length(); i++) {
    if (message.at(i) == "----------------------------------------------------") {
      msg.append(newline + message.at(i) + space + space + space + space + space + newline + newline);
    }
    else if (message.at(i) == "Main application libraries:") {
      msg.append(message.at(i) + newline + newline);
    }
    else if (message.at(i) == "Supporting libraries:") {
      msg.append(message.at(i) + newline + newline);
    }
    else {
      msg.append(message.at(i) + newline);
    }
  }

  return msg;
}

/**
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnappsselection::initAttributes(void ) {
  mAppsNames.append("Learn");
  mAppsNames.append("Filling");
  mAppsNames.append("Jumbling");
  mAppsNames.append("Recognizing");
  mAppsNames.append("Spelling");

  mAppsLibrariesNames.append("learnappsselection");
  mAppsLibrariesNames.append("learnappfilling");
  mAppsLibrariesNames.append("learnappjumbling");
  mAppsLibrariesNames.append("learnapprecognizing");
  mAppsLibrariesNames.append("learnappspelling");


  unsigned long major = 0;
  unsigned long minor = 0;
  unsigned long patch = 0;

  mMessageBoxMsg.append("Developer: Johnathon Leong");
  mMessageBoxMsg.append("Copyright: © 2021");
  mMessageBoxMsg.append("Downloads: github.com/JohnathonLeong/learn");
  mMessageBoxMsg.append("----------------------------------------------------");
  mMessageBoxMsg.append("Main application libraries:");
  learnappsselection_version(major, minor, patch);
  mMessageBoxMsg.append(mAppsNames.at(0) + " (" + mAppsLibrariesNames.at(0) + ".dll) : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnappfilling_version(major, minor, patch);
  mMessageBoxMsg.append(mAppsNames.at(1) + " (" + mAppsLibrariesNames.at(1) + ".dll) : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnappjumbling_version(major, minor, patch);
  mMessageBoxMsg.append(mAppsNames.at(2) + " (" + mAppsLibrariesNames.at(2) + ".dll) : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnapprecognizing_version(major, minor, patch);
  mMessageBoxMsg.append(mAppsNames.at(3) + " (" + mAppsLibrariesNames.at(3) + ".dll) : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnappspelling_version(major, minor, patch);
  mMessageBoxMsg.append(mAppsNames.at(4) + " (" + mAppsLibrariesNames.at(4) + ".dll) : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  mMessageBoxMsg.append("----------------------------------------------------");
  mMessageBoxMsg.append("Supporting libraries:");
  genericlibrarymaths_version(major, minor, patch);
  mMessageBoxMsg.append("genericlibrarymaths.dll : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnlibrarycustomwidgets_version(major, minor, patch);
  mMessageBoxMsg.append("learnlibrarycustomwidgets.dll : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
  learnlibraryquestiongenerator_version(major, minor, patch);
  mMessageBoxMsg.append("learnlibraryfunctions.dll : v" + QString::number(major) + "." + QString::number(minor) + "." + QString::number(patch));
}

/**
 * @brief initWidget - Initialization of the class widgets.
 */
void learnappsselection::initWidget(void ) {
  mpDisplayApps = new QWidget(this);
  mpDisplayApps->setGeometry(0, 0, 640, 480);

  int rowIndex =  0;
  int spacer   = 10;
  int xIndex   = 10;
  int yIndex   = 10;
  int width    = 75;
  int height   = 50;
  for (unsigned char i = 0; i < LEARNAPPSSELECTION_APPS_ROW_NUM; i++) {
    xIndex = 10;
    for (unsigned char j = 0; j < LEARNAPPSSELECTION_APPS_COL_NUM; j++) {
      mpApps[rowIndex + j] = new QPushButton(mpDisplayApps);
      mpApps[rowIndex + j]->setGeometry(xIndex, yIndex, width, height);
      mpApps[rowIndex + j]->hide();
      xIndex = xIndex + width + spacer;
    }
    yIndex = yIndex + height + spacer;
    rowIndex += LEARNAPPSSELECTION_APPS_COL_NUM;
  }

  for (unsigned char i = 0; i < LEARNAPPSSELECTION_APPS_AVAILABLE; i++) {
    mpApps[i]->setText(mAppsNames.at(i + 1));
    mpApps[i]->show();
  }

  mpApps[22]->setText("Read Me");
  mpApps[22]->show();
  mpApps[23]->setText("About");
  mpApps[23]->show();

  mpDisplayApps->resize(mpApps[LEARNAPPSSELECTION_APPS_TOTAL_NUM - 1]->x() + width + spacer, mpApps[LEARNAPPSSELECTION_APPS_TOTAL_NUM - 1]->y() + height + spacer);
  this->resize(mpDisplayApps->width(), mpDisplayApps->height());

  mpSelectedApp = nullptr;
}

/**
 * @brief readme - Generate content for Read Me
 */
void learnappsselection::readme(void ) {
  QMessageBox msgBox;
  msgBox.setFont(QFont("Courier"));
  msgBox.setWindowTitle("LEARN - Read Me");
  msgBox.setText("Please place \"jpg\" images into the \"pictures\" folder to be used as the questions in some of the applications in this program.\n\n"
                 "In order for the applications to work properly, please name the images used accordingly.");
  msgBox.exec();
}

/**
 * @brief slot_mpAppsSelect - Slot to handle when mpApps QPushButton is pressed.
 */
void learnappsselection::slot_mpAppsSelect() {
  QPushButton * pbSelect = (QPushButton *)sender();

  if (pbSelect->text() != "") {
    if (pbSelect->text() == "Read Me") {
      readme();
    }
    else if (pbSelect->text() == "About") {
      about();
    }
    else {
      if (pbSelect->text() == "Filling") {
        mpSelectedApp = new learnappfilling(this);
      }
      else if(pbSelect->text() == "Jumbling") {
        mpSelectedApp = new learnappjumbling(this);
      }
      else if(pbSelect->text() == "Recognizing") {
        mpSelectedApp = new learnapprecognizing(this);
      }
      else if(pbSelect->text() == "Spelling") {
        mpSelectedApp = new learnappspelling(this);
      }
      if (mpSelectedApp != NULL) {
        mpSelectedApp->show();
        mpDisplayApps->hide();
        connect(mpSelectedApp, SIGNAL(signal_Close()), this, SLOT(slot_mpSelectedAppClose()));
        this->resize(mpSelectedApp->width(), mpSelectedApp->height());
        emit signal_Resize(mpSelectedApp->width(), mpSelectedApp->height());
      }
    }
  }
}

/**
 * @brief slot_mpSelectedAppClose - Slot to handle when learn apps is being closed.
 */
void learnappsselection::slot_mpSelectedAppClose() {
  mpDisplayApps->show();
  this->resize(mpDisplayApps->width(), mpDisplayApps->height());
  emit signal_Resize(mpDisplayApps->width(), mpDisplayApps->height());

  delete mpSelectedApp;
  mpSelectedApp = nullptr;
}

/**
 * @brief learnappsselection_version - Check the version of this library
 * @param major                      - Major version number.
 * @param minor                      - Minor version number.
 * @param patch                      - Patch version number.
 */
void learnappsselection_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNAPPSSELECTION_VERSION_MAJOR;
  minor = LEARNAPPSSELECTION_VERSION_MINOR;
  patch = LEARNAPPSSELECTION_VERSION_PATCH;
}

