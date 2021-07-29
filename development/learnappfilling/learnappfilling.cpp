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
 * Change Log:  1. First release of learnappfilling.
 *              2. Implemented learnappfilling class.
 */

#include "learnappfilling.h"
#include <QDir>
#include <QImageReader>
#include "genericlibrarymaths.h"

#define LEARNAPPFILLING_VERSION_MAJOR 1
#define LEARNAPPFILLING_VERSION_MINOR 0
#define LEARNAPPFILLING_VERSION_PATCH 0

/**
 * @brief learnappfilling - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
learnappfilling::learnappfilling(QWidget * parent) : QWidget(parent) {
  initWidget();
  initAttributes();
  connect(mpCheckAnswer, SIGNAL(released()), this, SLOT(slot_mpCheckAnswer()));
  connect(mpClose, SIGNAL(released()), this, SLOT(slot_mpClose()));
  for (unsigned char i = 0; i < LEARNAPPFILLING_LETTERS_MAX; i++) {
    connect(mpEntered[i], SIGNAL(signal_keyBackspace()), this, SLOT(slot_mpEnteredKeyBackspace()));
    connect(mpEntered[i], SIGNAL(signal_keyLeft()), this, SLOT(slot_mpEnteredKeyLeft()));
    connect(mpEntered[i], SIGNAL(signal_keyRight()), this, SLOT(slot_mpEnteredKeyRight()));
    connect(mpEntered[i], SIGNAL(textEdited(QString)), this, SLOT(slot_mpEntered(QString)));
  }
}

/**
 * @brief learnappfilling - Default destructor.
 */
learnappfilling::~learnappfilling() {
  delete mpCheckAnswer;
  delete mpClose;
  delete mpImage;

  for (unsigned char i = 0; i < LEARNAPPFILLING_LETTERS_MAX; i++) {
    delete mpAnswer[i];
    delete mpEntered[i];
  }
}

/**
 * @brief initAttributes - Initialization of the class attributes.
 */
void learnappfilling::initAttributes(void ) {
  mFlagQuestionAvail = mQnsGenerator.setImagePath("./pictures");
}

/**
 * @brief initWidget - Initialization of the class widgets.
 */
void learnappfilling::initWidget(void ) {
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

  for (unsigned char i = 0; i < LEARNAPPFILLING_LETTERS_MAX; i++) {
    mpAnswer[i] = new QLabel(this);
    mpAnswer[i]->setGeometry(mpImage->x() + (boxSize * i), mpImage->y() + mpImage->height() + 10, boxSize, boxSize);
    mpAnswer[i]->setStyleSheet("border: 1px solid black");
    mpAnswer[i]->setFont(font);
    mpAnswer[i]->hide();
    mpAnswer[i]->setAlignment(Qt::AlignCenter);

    mpEntered[i] = new QtCustomLineEdit(this);
    mpEntered[i]->setGeometry(mpAnswer[i]->x(), mpAnswer[i]->y() + mpAnswer[i]->height() + 10, boxSize, boxSize);
    mpEntered[i]->setFont(font);
    mpEntered[i]->hide();
    mpEntered[i]->setAlignment(Qt::AlignCenter);
    mpEntered[i]->setMaxLength(1);
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
void learnappfilling::lineEditJumpLeft(unsigned short index ) {
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
void learnappfilling::lineEditJumpRight(unsigned short index ) {
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
void learnappfilling::slot_mpCheckAnswer(void ) {
  if ((mpCheckAnswer->text() == "Next") || (mpCheckAnswer->text() == "Start")) {
    if (mFlagQuestionAvail) {
      for (unsigned char i = 0; i < LEARNAPPFILLING_LETTERS_MAX; i++) {
        mpAnswer[i]->clear();
        mpAnswer[i]->hide();
        mpEntered[i]->clear();
        mpEntered[i]->hide();
        mpEntered[i]->setEnabled(true);
        mpEntered[i]->setStyleSheet("QLineEdit {color: black;}");
      }

      mQnsGenerator.getQuestions_ONE(mAnswer, mAnswerImage);
      mpImage->setPixmap(QPixmap::fromImage(mAnswerImage.scaled(mpImage->size(), Qt::KeepAspectRatio)));
      mpCheckAnswer->setText("Check");

      unsigned short index[mAnswer.length()];
      for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
        index[i] = i;
      }
      shuffle(index, mAnswer.length());

      unsigned short len = mAnswer.length() / 2;
      if (mAnswer.length() == 4) {
        len = 1;
      }
      else if (mAnswer.length() < 4) {
        len = 0;
      }

      for (unsigned short i = 0; i < len; i++) {
         mpEntered[index[i]]->setText(mAnswer.at(index[i]));
         mpEntered[index[i]]->setEnabled(false);
      }

      unsigned char flagIsFocused = 0;
      for (unsigned short i = 0; i < (unsigned short)(mAnswer.length()); i++) {
        mpAnswer[i]->show();
        mpEntered[i]->show();
        if ((flagIsFocused == 0) && (mpEntered[i]->isEnabled() == true)) {
          mpEntered[i]->setFocus();
          mIndexFirstEnabledEntered = i;
          flagIsFocused = 1;
        }
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
          mpEntered[i]->setStyleSheet("QLineEdit {color: green;}");
        else {
          mpEntered[i]->setStyleSheet("QLineEdit {color: red;}");
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
void learnappfilling::slot_mpClose(void ) {
  emit signal_Close();
}

/**
 * @brief slot_mpEntered - Slot to handle when keys are pressed in mpEntered QtCustomLineEdit.
 * @param text           - The text entered.
 */
void learnappfilling::slot_mpEntered(const QString &text) {
  QtCustomLineEdit * mpLineEdit = (QtCustomLineEdit *)sender();
  unsigned short index = mpLineEdit->objectName().toUShort();

  mpLineEdit->setText(text.toUpper());
  if (mpLineEdit->text().length() > 0) {
    for (unsigned short i = index + 1; i < mAnswer.length(); i++) {
      if (mpEntered[i]->isEnabled() == true) {
        mpEntered[i]->setFocus();
        break;
      }
    }
  }
//  mFlagTextChanged = 1;
}

/**
 * @brief slot_mpEnteredKeyLeft - Slot to handle when left key is pressed in mpEntered
 *                                QtCustomLineEdit.
 */
void learnappfilling::slot_mpEnteredKeyLeft(void ) {
  QtCustomLineEdit * mpLineEdit = (QtCustomLineEdit *)sender();
  if (mpLineEdit->cursorPosition() == 0) {
    unsigned short index = mpLineEdit->objectName().toUShort();
    lineEditJumpLeft(index);
  }
}

/**
 * @brief slot_mpEnteredKeyRight - Slot to handle when right key is pressed in mpEntered
 *                                 QtCustomLineEdit.
 */
void learnappfilling::slot_mpEnteredKeyRight(void ) {
  QtCustomLineEdit * mpLineEdit = (QtCustomLineEdit *)sender();
  if ((mpLineEdit->cursorPosition() == 1) || ((mpLineEdit->cursorPosition() == 0) && (mpLineEdit->text().length() == 0))) {
    unsigned short index = mpLineEdit->objectName().toUShort();
    lineEditJumpRight(index);
  }
}

/**
 * @brief slot_mpEnteredKeyBackspace - Slot to handle when backspace key is pressed in mpEntered
 *                                     QtCustomLineEdit.
 */
void learnappfilling::slot_mpEnteredKeyBackspace(void ) {
  QtCustomLineEdit * mpLineEdit = (QtCustomLineEdit *)sender();
  if (mpLineEdit->text().length() == 0) {
    unsigned short index = mpLineEdit->objectName().toUShort();
    lineEditJumpLeft(index);
  }
}

/**
 * @brief learnappfilling_version - Check the version of this library
 * @param major                   - Major version number.
 * @param minor                   - Minor version number.
 * @param patch                   - Patch version number.
 */
void learnappfilling_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNAPPFILLING_VERSION_MAJOR;
  minor = LEARNAPPFILLING_VERSION_MINOR;
  patch = LEARNAPPFILLING_VERSION_PATCH;
}


