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

#ifndef LEARNAPPFILLING_H
#define LEARNAPPFILLING_H

#include <QtCore/qglobal.h>

#if defined(LEARNAPPFILLING_LIBRARY)
#  define LEARNAPPFILLING_EXPORT Q_DECL_EXPORT
#else
#  define LEARNAPPFILLING_EXPORT
#endif

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QKeyEvent>
#include "learnlibrarycustomwidgets.h"
#include "learnlibraryfunctions.h"

#define LEARNAPPFILLING_LETTERS_MAX 24

class LEARNAPPFILLING_EXPORT learnappfilling : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief learnappfilling - Overloaded constructor.
   * @param parent           - QWidget parent pointer.
   */
  learnappfilling(QWidget * parent);

  /**
   * @brief learnappfilling - Default destructor.
   */
  ~learnappfilling();

signals:
  /**
   * @brief signal_Close - Signal generated when close QPushButton is pressed.
   */
  void signal_Close();

private:
  /**
   * @brief initAttributes - Initialization of the class attributes.
   */
  void initAttributes(void );

  /**
   * @brief initWidget - Initialization of the class widgets.
   */
  void initWidget(void );

  /**
   * @brief lineEditJumpLeft - Handle the cursor focusing when jump leftward of QtCustomLineEdit.
   * @param index            - Index of the QtCustomLineEdit array which the cursor is in.
   */
  void lineEditJumpLeft(unsigned short index);

  /**
   * @brief lineEditJumpRight - Handle the cursor focusing when jump leftward of QtCustomLineEdit.
   * @param index             - Index of the QtCustomLineEdit array which the cursor is in.
   */
  void lineEditJumpRight(unsigned short index);

  /**
   * @brief mAnswer - To store the answer to the question.
   */
  QString mAnswer;

  /**
   * @brief mAnswerImage - To store the answer image to the question.
   */
  QImage mAnswerImage;

  /**
   * @brief mFlagQuestionAvail - Flag to store if questions are available.
   */
  unsigned char mFlagQuestionAvail;

  /**
   * @brief mIndexFirstEnabledEntered - To store the index of first enabled QtCustomLineEdit widget.
   */
  unsigned char mIndexFirstEnabledEntered;

  /**
   * @brief mQnsGenerator - Question generator.
   */
  learnlibraryquestiongenerator mQnsGenerator;

  /**
   * @brief mpAnswer - QLabel widget to display the correct answer.
   */
  QLabel * mpAnswer[LEARNAPPFILLING_LETTERS_MAX];

  /**
   * @brief mpCheckAnswer - QPushButton widget for starting the library and checking the answer.
   */
  QPushButton * mpCheckAnswer;

  /**
   * @brief mpClose - QPushButton widget to close the library.
   */
  QPushButton * mpClose;

  /**
   * @brief mpImage - QLabel widget to display the image of the question.
   */
  QLabel * mpImage;

  /**
   * @brief mpEntered - QtCustomLineEdit widget for entering the answer.
   */
  QtCustomLineEdit * mpEntered[LEARNAPPFILLING_LETTERS_MAX];

private slots:
  /**
   * @brief slot_mpCheckAnswer - Slot to handle when mpCheckAnswer QPushButton is pressed.
   */
  void slot_mpCheckAnswer(void );

  /**
   * @brief slot_mpClose - Slot to handle when mpClose QPushButton is pressed.
   */
  void slot_mpClose(void );

  /**
   * @brief slot_mpEntered - Slot to handle when keys are pressed in mpEntered QtCustomLineEdit.
   * @param text           - The text entered.
   */
  void slot_mpEntered(const QString &text);

  /**
   * @brief slot_mpEnteredKeyLeft - Slot to handle when left key is pressed in mpEntered
   *                                QtCustomLineEdit.
   */
  void slot_mpEnteredKeyLeft(void );

  /**
   * @brief slot_mpEnteredKeyRight - Slot to handle when right key is pressed in mpEntered
   *                                 QtCustomLineEdit.
   */
  void slot_mpEnteredKeyRight(void );

  /**
   * @brief slot_mpEnteredKeyBackspace - Slot to handle when backspace key is pressed in mpEntered
   *                                     QtCustomLineEdit.
   */
  void slot_mpEnteredKeyBackspace(void );

};

/**
 * @brief learnappfilling_version - Check the version of this library
 * @param major                   - Major version number.
 * @param minor                   - Minor version number.
 * @param patch                   - Patch version number.
 */
void LEARNAPPFILLING_EXPORT learnappfilling_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // LEARNAPPFILLING_H

