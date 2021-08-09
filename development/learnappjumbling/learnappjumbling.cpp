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
 * Date:        2021/08/09 (YYYY/MM/DD)
 * Change Log:  1. First release of learnappjumbling.
 *              2. Implemented learnappjumbling class.
 */

#include "learnappjumbling.h"
#include <QDir>
#include <QImageReader>
#include "genericlibrarymaths.h"

#define LEARNAPPJUMBLING_VERSION_MAJOR 1
#define LEARNAPPJUMBLING_VERSION_MINOR 0
#define LEARNAPPJUMBLING_VERSION_PATCH 0

/**
 * @brief learnappjumbling - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnappjumbling::learnappjumbling(QWidget * parent) : QWidget(parent) {
  initWidget();
  initAttributes();
  connect(mpCheckAnswer, SIGNAL(released()), this, SLOT(slot_mpCheckAnswer()));
  connect(mpClose, SIGNAL(released()), this, SLOT(slot_mpClose()));
  for (unsigned char i = 0; i < LEARNAPPJUMBLING_LETTERS_MAX; i++) {
    connect(mpJumbles[i], SIGNAL(released()), this, SLOT(slot_mpJumbles()));
    connect(mpEntered[i], SIGNAL(released()), this, SLOT(slot_mpEntered()));
  }
}

/**
 * @brief learnappjumbling - Default destructor.
 */
learnappjumbling::~learnappjumbling() {
  delete mpCheckAnswer;
  delete mpClose;
  delete mpImage;

  for (unsigned char i = 0; i < LEARNAPPJUMBLING_LETTERS_MAX; i++) {
    delete mpAnswer[i];
    delete mpEntered[i];
  }
}

/**
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnappjumbling::initAttributes(void ) {
  mFlagQuestionAvail = mQnsGenerator.setImagePath("./pictures");
}

/**
 * @brief initWidget - Initialization of the class widgets.
 */
void learnappjumbling::initWidget(void ) {
  QFont font;
  font.setPointSize(22);
  QFont fontClose;
  fontClose.setPointSize(10);
  int boxSize = 36;

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

  for (unsigned char i = 0; i < LEARNAPPJUMBLING_LETTERS_MAX; i++) {
    mpAnswer[i] = new QLabel(this);
    mpAnswer[i]->setGeometry(mpImage->x() + (boxSize * i), mpImage->y() + mpImage->height() + 10, boxSize, boxSize);
    mpAnswer[i]->setStyleSheet("border: 1px solid black");
    mpAnswer[i]->setFont(font);
    mpAnswer[i]->hide();
    mpAnswer[i]->setAlignment(Qt::AlignCenter);

    mpJumbles[i] = new QPushButton(this);
    mpJumbles[i]->setGeometry(mpAnswer[i]->x(), mpAnswer[i]->y() + mpAnswer[i]->height() + 10, boxSize, boxSize);
    mpJumbles[i]->setFont(font);
    mpJumbles[i]->hide();

    mpEntered[i] = new QPushButton(this);
    mpEntered[i]->setGeometry(mpJumbles[i]->x(), mpJumbles[i]->y() + mpJumbles[i]->height() + 10, boxSize, boxSize);
    mpEntered[i]->setFont(font);
    mpEntered[i]->hide();
    mpEntered[i]->setObjectName(QString::number(i));
  }

  QSize size(mpCheckAnswer->x() + mpCheckAnswer->width() + 10, mpEntered[0]->y() + mpEntered[0]->height() + 10);
  this->setMinimumSize(size);
  this->setMaximumSize(size);
}

/**
 * @brief lineEditJumpLeft - Handle the cursor focusing when jump leftward of QtCustomLineEdit.
 * @param index            - Index of the QtCustomLineEdit array which the cursor is in.
 */
void learnappjumbling::lineEditJumpLeft(unsigned short index ) {
  for (char i = index - 1; i >= mIndexFirstEnabledEntered ; i--) {
    unsigned char j = (unsigned char)(i);
    if (mpEntered[j]->isEnabled() == true) {
      mpEntered[j]->setFocus();
      break;
    }
  }
}

/**
 * @brief lineEditJumpRight - Handle the cursor focusing when jump leftward of QtCustomLineEdit.
 * @param index             - Index of the QtCustomLineEdit array which the cursor is in.
 */
void learnappjumbling::lineEditJumpRight(unsigned short index ) {
  for (char i = index + 1; i < mAnswer.length(); i++) {
    unsigned char j = (unsigned char)(i);
    if (mpEntered[j]->isEnabled() == true) {
      mpEntered[j]->setFocus();
      break;
    }
  }
}

/**
 * @brief slot_mpCheckAnswer - Slot to handle when mpCheckAnswer QPushButton is pressed.
 */
void learnappjumbling::slot_mpCheckAnswer(void ) {
  if ((mpCheckAnswer->text() == "Next") || (mpCheckAnswer->text() == "Start")) {
    if (mFlagQuestionAvail) {
      for (unsigned char i = 0; i < LEARNAPPJUMBLING_LETTERS_MAX; i++) {
        mpAnswer[i]->clear();
        mpAnswer[i]->hide();
        mpJumbles[i]->setText("");
        mpJumbles[i]->hide();
        mpEntered[i]->setText("");
        mpEntered[i]->hide();
        mpEntered[i]->setStyleSheet("QPushButton {color: black;}");
      }
      mJumbles.clear();

      mQnsGenerator.getQuestions_ONE(mAnswer, mAnswerImage);
      mpImage->setPixmap(QPixmap::fromImage(mAnswerImage.scaled(mpImage->size(), Qt::KeepAspectRatio)));
      mpCheckAnswer->setText("Check");

      unsigned short index[mAnswer.length()];
      for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
        index[i] = i;
      }
      shuffle(index, mAnswer.length());

      for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
        mJumbles.append(mAnswer.at(index[i]));
        mpJumbles[i]->setText(mAnswer.at(index[i]));
      }

      for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
        mpAnswer[i]->show();
        mpJumbles[i]->show();
        mpEntered[i]->show();
      }
    }
    else {
      mpImage->setText("No Pictures Found!!!");
    }
  }
  else if (mpCheckAnswer->text() == "Check") {
    for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
      mpAnswer[i]->setText(mAnswer.at(i));
      if (mpEntered[i]->isEnabled() == true) {
        if (mpEntered[i]->text() == mAnswer.at(i))
          mpEntered[i]->setStyleSheet("QPushButton {color: green;}");
        else {
          mpEntered[i]->setStyleSheet("QPushButton {color: red;}");
          if (mpEntered[i]->text().length() == 0)
            mpEntered[i]->setText(mAnswer.at(i));
        }
      }
    }
    mpCheckAnswer->setText("Next");
  }
}

/**
 * @brief slot_mpClose - Slot to handle when mpClose QPushButton is pressed.
 */
void learnappjumbling::slot_mpClose(void ) {
  emit signal_Close();
}

/**
 * @brief slot_mpEntered - Slot to handle when mpEntered QPushButton is pressed.
 */
void learnappjumbling::slot_mpEntered(void ) {
  QPushButton * mpPushButton = (QPushButton *)sender();
  QString buttonText = mpPushButton->text();
  if (buttonText.length() > 0) {
    mpPushButton->setText("");

    for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
      if ((buttonText == mJumbles.at(i)) && (mpJumbles[i]->text().length() == 0)) {
        mpJumbles[i]->setText(buttonText);
        break;
      }
    }
  }
}

/**
 * @brief slot_mpEntered - Slot to handle when mpJumbles QPushButton is pressed.
 */
void learnappjumbling::slot_mpJumbles(void ) {
  QPushButton * mpPushButton = (QPushButton *)sender();
  QString buttonText = mpPushButton->text();
  mpPushButton->setText("");

  for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
    if (mpEntered[i]->text().length() == 0) {
      mpEntered[i]->setText(buttonText);
      break;
    }
  }
}

/**
 * @brief learnappjumbling_version - Check the version of this library
 * @param major                   - Major version number.
 * @param minor                   - Minor version number.
 * @param patch                   - Patch version number.
 */
void learnappjumbling_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNAPPJUMBLING_VERSION_MAJOR;
  minor = LEARNAPPJUMBLING_VERSION_MINOR;
  patch = LEARNAPPJUMBLING_VERSION_PATCH;
}


