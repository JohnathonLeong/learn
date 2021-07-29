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
 * Change Log:  1. First release of learnapprecognizing.
 *              2. Implemented learnapprecognizing class.
 */

#include "learnapprecognizing.h"

#define LEARNAPPRECONGIZING_VERSION_MAJOR 1
#define LEARNAPPRECONGIZING_VERSION_MINOR 0
#define LEARNAPPRECONGIZING_VERSION_PATCH 0

/**
 * @brief learnapprecognizing - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnapprecognizing::learnapprecognizing(QWidget * parent) : QWidget(parent) {
  initWidget();
  initAttributes();
  for (unsigned char i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++)
    connect(mpChoice[i], SIGNAL(released()), this, SLOT(slot_mpChoice()));
  connect(mpCheckAnswer, SIGNAL(released()), this, SLOT(slot_mpCheckAnswer()));
  connect(mpClose, SIGNAL(released()), this, SLOT(slot_mpClose()));
}

/**
 * @brief learnapprecognizing - Default destructor.
 */
learnapprecognizing::~learnapprecognizing() {
  for (unsigned char i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++)
    delete mpChoice[i];
  delete mpCheckAnswer;
  delete mpClose;
  delete mpImage;
}

/**
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnapprecognizing::initAttributes(void ) {
  mFlagQuestionAvail = mQnsGenerator.setImagePath("./pictures");
}

/**
 * @brief initWidget - Initialization of the class widgets.
 */
void learnapprecognizing::initWidget(void ) {
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

  int x = mpCheckAnswer->x();
  int y = mpCheckAnswer->y() - (70 * LEARNAPPRECONGIZING_CHOICE_SIZE);
  for (unsigned char i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
    mpChoice[i] = new QPushButton(this);
    mpChoice[i]->setGeometry(x, y, 240, 60);
    mpChoice[i]->setFont(font);
    mpChoice[i]->setEnabled(false);
    mpChoice[i]->setCheckable(true);
    y += 70;
  }

  QSize size(mpCheckAnswer->x() + mpCheckAnswer->width() + 10, mpImage->y() + mpImage->height() + 10);
  this->setMinimumSize(size);
  this->setMaximumSize(size);
}

/**
 * @brief slot_mpCheckAnswer - Slot to handle when mpCheckAnswer QPushButton is pressed.
 */
void learnapprecognizing::slot_mpCheckAnswer(void ) {
  if ((mpCheckAnswer->text() == "Next") || (mpCheckAnswer->text() == "Start")) {
    if (mFlagQuestionAvail) {
      mpCheckAnswer->setEnabled(false);
      for (unsigned long i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
        mpChoice[i]->setStyleSheet("QPushButton {color: black;}"
                                   "QPushButton::checked {background:rgb(138,176,226);}"
                                   "QPushButton {background:rgb(240,255,255);}");
        mpChoice[i]->setChecked(false);
        mpChoice[i]->setEnabled(true);
      }

      mQnsGenerator.getQuestions_MULTIPLE(mAnswer, mAnswerImage, mOptions, mAnswerIndex, LEARNAPPRECONGIZING_CHOICE_SIZE);
      for (unsigned long i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
        mpChoice[i]->setEnabled(true);
        mpChoice[i]->setText(mOptions.at(i));
      }
      mpImage->setPixmap(QPixmap::fromImage(mAnswerImage.scaled(mpImage->size(), Qt::KeepAspectRatio)));
      mpCheckAnswer->setText("Check");
    }
    else {
      mpImage->setText("No Pictures Found!!!");
    }
  }
  else if (mpCheckAnswer->text() == "Check") {
    for (unsigned long i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
      mpChoice[i]->setEnabled(false);
    }

    if (mChoiceIndex != mAnswerIndex) {
      mpChoice[mChoiceIndex]->setStyleSheet("QPushButton {color: black;}"
                                            "QPushButton {background-color:rgb(236,180,158);}");
    }
    mpChoice[mAnswerIndex]->setStyleSheet("QPushButton {color: black;}"
                                          "QPushButton {background-color:rgb(165,219,148);}");

    mpCheckAnswer->setText("Next");
  }
}

/**
 * @brief slot_mpChoice - Slot to handle when mpChoice QPushButton is pressed.
 */
void learnapprecognizing::slot_mpChoice(void ) {
  QPushButton * mpButton = (QPushButton *)sender();
  for (unsigned char i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
    mpChoice[i]->setChecked(false);
  }
  mpButton->setChecked(true);
  for (unsigned char i = 0; i < LEARNAPPRECONGIZING_CHOICE_SIZE; i++) {
    if (mpChoice[i]->isChecked()) {
      mChoiceIndex = i;
      break;
    }
  }
  mpCheckAnswer->setEnabled(true);
}

/**
 * @brief slot_mpClose - Slot to handle when mpClose QPushButton is pressed.
 */
void learnapprecognizing::slot_mpClose(void ) {
  emit signal_Close();
}

/**
 * @brief learnapprecognizing_version - Check the version of this library
 * @param major                       - Major version number.
 * @param minor                       - Minor version number.
 * @param patch                       - Patch version number.
 */
void learnapprecognizing_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNAPPRECONGIZING_VERSION_MAJOR;
  minor = LEARNAPPRECONGIZING_VERSION_MINOR;
  patch = LEARNAPPRECONGIZING_VERSION_PATCH;
}


