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

#ifndef LEARNAPPSPELLING_H
#define LEARNAPPSPELLING_H

#include <QtCore/qglobal.h>

#if defined(LEARNAPPSPELLING_LIBRARY)
#  define LEARNAPPSPELLING_EXPORT Q_DECL_EXPORT
#else
#  define LEARNAPPSPELLING_EXPORT
#endif

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "learnlibraryfunctions.h"

class LEARNAPPSPELLING_EXPORT learnappspelling : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief learnappspelling - Overloaded constructor.
   * @param parent           - QWidget parent pointer.
   */
  learnappspelling(QWidget * parent);

  /**
   * @brief learnappspelling - Default destructor.
   */
  ~learnappspelling();

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
   * @brief mQnsGenerator - Question generator.
   */
  learnlibraryquestiongenerator mQnsGenerator;

  /**
   * @brief mpAnswer - QLabel widget to display the correct answer.
   */
  QLabel * mpAnswer;

  /**
   * @brief mpCheckAnswer - QPushButton widget for starting the library and checking the answer.
   */
  QPushButton * mpCheckAnswer;

  /**
   * @brief mpClose - QPushButton widget to close the library.
   */
  QPushButton * mpClose;

  /**
   * @brief mpEntered - QLineEdit widget for entering the answer.
   */
  QLineEdit *   mpEntered;

  /**
   * @brief mpImage - QLabel widget to display the image of the question.
   */
  QLabel *      mpImage;

private slots:
  /**
   * @brief slot_mpCheckAnswer - Slot to handle when mpCheckAnswer QPushButton is pressed.
   */
  void slot_mpCheckAnswer(void );

  /**
   * @brief slot_mpClose - Slot to handle when mpClose QPushButton is pressed.
   */
  void slot_mpClose(void );

};

/**
 * @brief learnappspelling_version - Check the version of this library
 * @param major                    - Major version number.
 * @param minor                    - Minor version number.
 * @param patch                    - Patch version number.
 */
void LEARNAPPSPELLING_EXPORT learnappspelling_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // LEARNAPPSPELLING_H
