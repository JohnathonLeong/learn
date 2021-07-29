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
 * Change Log:  1. First release of learnappspelling.
 *              2. Implemented learnappspelling class.
 */

#include "learnappspelling.h"

#define LEARNAPPFILLING_VERSION_MAJOR 1
#define LEARNAPPFILLING_VERSION_MINOR 0
#define LEARNAPPFILLING_VERSION_PATCH 0

/**
 * @brief learnappfilling - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnappspelling::learnappspelling(QWidget * parent) : QWidget(parent) {
  initWidget();
  initAttributes();
  connect(mpCheckAnswer, SIGNAL(released()), this, SLOT(slot_mpCheckAnswer()));
  connect(mpClose, SIGNAL(released()), this, SLOT(slot_mpClose()));
}

/**
 * @brief learnappfilling - Default destructor.
 */
learnappspelling::~learnappspelling() {
  delete mpAnswer;
  delete mpCheckAnswer;
  delete mpClose;
  delete mpEntered;
  delete mpImage;
}

/**
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnappspelling::initAttributes(void ) {
  mFlagQuestionAvail = mQnsGenerator.setImagePath("./pictures");
}

/**
 * @brief initWidget - Initialization of the class widgets.
 */
void learnappspelling::initWidget(void ) {
  QFont font;
  font.setPointSize(22);
  QFont fontClose;
  fontClose.setPointSize(10);

  mpImage = new QLabel(this);
  mpImage->setGeometry(10, 10, 640, 480);
  mpImage->setStyleSheet("border: 1px solid black");
  mpImage->setFont(font);
  mpImage->setAlignment(Qt::AlignCenter);

  mpClose = new QPushButton(this);
  mpClose->setGeometry(mpImage->x() + mpImage->width() + 10, mpImage->y(), 60, 60);
  mpClose->setFont(fontClose);
  mpClose->setText("BACK");

  mpCheckAnswer = new QPushButton(this);
  mpCheckAnswer->setGeometry(mpImage->x() + mpImage->width() + 10, mpImage->y() + mpImage->height() - 60, 240, 60);
  mpCheckAnswer->setFont(font);
  mpCheckAnswer->setText("Start");

  mpEntered = new QLineEdit(this);
  mpEntered->setGeometry(mpCheckAnswer->x(), mpCheckAnswer->y() - 60 - 10, 240, 60);
  mpEntered->setStyleSheet("border: 1px solid black");
  mpEntered->setFont(font);
  mpEntered->setAlignment(Qt::AlignCenter);
  mpEntered->setEnabled(false);

  mpAnswer = new QLabel(this);
  mpAnswer->setGeometry(mpCheckAnswer->x(), mpEntered->y() - 60 - 10, 240, 60);
  mpAnswer->setStyleSheet("border: 1px solid black");
  mpAnswer->setFont(font);
  mpAnswer->setAlignment(Qt::AlignCenter);

  QSize size(mpCheckAnswer->x() + mpCheckAnswer->width() + 10, mpImage->y() + mpImage->height() + 10);
  this->setMinimumSize(size);
  this->setMaximumSize(size);
}

/**
 * @brief slot_mpCheckAnswer - Slot to handle when mpCheckAnswer QPushButton is pressed.
 */
void learnappspelling::slot_mpCheckAnswer(void ) {
  if ((mpCheckAnswer->text() == "Next") || (mpCheckAnswer->text() == "Start")) {
    if (mFlagQuestionAvail) {
      mpAnswer->clear();
      mpAnswer->setStyleSheet("QLabel {border: 1px solid black;}"
                              "QLabel {background-color:rgb(240,240,240);}");
      mpEntered->clear();
      mpEntered->setEnabled(true);
      mpEntered->setFocus();

      mQnsGenerator.getQuestions_ONE(mAnswer, mAnswerImage);
      mpImage->setPixmap(QPixmap::fromImage(mAnswerImage.scaled(mpImage->size(), Qt::KeepAspectRatio)));
      mpCheckAnswer->setText("Check");
    }
    else {
      mpImage->setText("No Pictures Found!!!");
    }
  }
  else if (mpCheckAnswer->text() == "Check") {
    mpEntered->setEnabled(false);

    QString style = (mpEntered->text().toUpper() == mAnswer.toUpper()) ? "{background-color:rgb(165,219,148);}" : "{background-color:rgb(236,180,158);}";
    mpAnswer->setStyleSheet("QLabel {border: 1px solid black;}"
                            "QLabel " + style);
    mpAnswer->setText(mAnswer);
    mpCheckAnswer->setText("Next");
  }
}

/**
 * @brief slot_mpClose - Slot to handle when mpClose QPushButton is pressed.
 */
void learnappspelling::slot_mpClose(void ) {
  emit signal_Close();
}

/**
 * @brief learnappspelling_version - Check the version of this library
 * @param major                    - Major version number.
 * @param minor                    - Minor version number.
 * @param patch                    - Patch version number.
 */
void learnappspelling_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNAPPFILLING_VERSION_MAJOR;
  minor = LEARNAPPFILLING_VERSION_MINOR;
  patch = LEARNAPPFILLING_VERSION_PATCH;
}


