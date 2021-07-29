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
 * Version:     1.0.0
 * Date:        2021/07/29 (YYYY/MM/DD)
 * Change Log:  1. First release of learnappsselection.
 *              2. Implemented learnappsselection class.
 */

#include "learnappsselection.h"

#include <QDir>
#include <QMessageBox>

#include "learnappfilling.h"
#include "learnapprecognizing.h"
#include "learnappspelling.h"

#define LEARNAPPSSELECTION_VERSION_MAJOR 1
#define LEARNAPPSSELECTION_VERSION_MINOR 0
#define LEARNAPPSSELECTION_VERSION_PATCH 0

/**
 * @brief learnappsselection - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnappsselection::learnappsselection(QWidget * parent) : QWidget(parent) {
  initWidget();
  initAttributes();

  if (QDir("./pictures").exists() == false) {
    QDir().mkdir("./pictures");
    QMessageBox msgBox;
    msgBox.setText("Please places \"jpg\" images into the \"pictures\" folder to use this program.\n"
                   "In order for this program to work properly, please name the images used accordingly.");
    msgBox.exec();
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
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnappsselection::initAttributes(void ) {
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
  mpApps[0]->setText("Spelling");
  mpApps[1]->setText("Recognizing");
  mpApps[2]->setText("Filling");
  for (unsigned char i = 0; i < LEARNAPPSSELECTION_APPS_AVAILABLE; i++)
    mpApps[i]->show();

  mpDisplayApps->resize(mpApps[LEARNAPPSSELECTION_APPS_TOTAL_NUM - 1]->x() + width + spacer, mpApps[LEARNAPPSSELECTION_APPS_TOTAL_NUM - 1]->y() + height + spacer);
  this->resize(mpDisplayApps->width(), mpDisplayApps->height());

  mpSelectedApp = nullptr;
}

/**
 * @brief slot_mpAppsSelect - Slot to handle when mpApps QPushButton is pressed.
 */
void learnappsselection::slot_mpAppsSelect() {
  QPushButton * pbSelect = (QPushButton *)sender();

  if (pbSelect->text() != "") {
    mpDisplayApps->hide();
    if (pbSelect->text() == "Recognizing") {
      mpSelectedApp = new learnapprecognizing(this);
    }
    else if(pbSelect->text() == "Spelling") {
      mpSelectedApp = new learnappspelling(this);
    }
    else if(pbSelect->text() == "Filling") {
      mpSelectedApp = new learnappfilling(this);
    }
    mpSelectedApp->show();
    connect(mpSelectedApp, SIGNAL(signal_Close()), this, SLOT(slot_mpSelectedAppClose()));
    this->resize(mpSelectedApp->width(), mpSelectedApp->height());
    emit signal_Resize(mpSelectedApp->width(), mpSelectedApp->height());
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

