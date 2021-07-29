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
 * Change Log:  1. First release of learnlibrarycustomwidgets
 *              2. Implemented QtCustomLineEdit class.
 */

#ifndef LEARNLIBRARYCUSTOMWIDGETS_H
#define LEARNLIBRARYCUSTOMWIDGETS_H

#include <QtCore/qglobal.h>

#if defined(LEARNLIBRARYCUSTOMWIDGETS_LIBRARY)
#  define LEARNLIBRARYCUSTOMWIDGETS_EXPORT Q_DECL_EXPORT
#else
#  define LEARNLIBRARYCUSTOMWIDGETS_EXPORT
#endif

#include <QKeyEvent>
#include <QLineEdit>

class LEARNLIBRARYCUSTOMWIDGETS_EXPORT QtCustomLineEdit : public QLineEdit
{
  Q_OBJECT

public:
  /**
   * @brief QtCustomLineEdit - Overloaded constructor.
   * @param parent           - QWidget parent pointer.
   */
  QtCustomLineEdit(QWidget * parent);

  /**
   * @brief QtCustomLineEdit - Default destructor.
   */
  ~QtCustomLineEdit();

protected:
  /**
   * @brief keyPressEvent - Overloaded key press event function.
   * @param event         - Event pointer.
   */
  void keyPressEvent(QKeyEvent * event);

signals:
  /**
   * @brief signal_keyBackspace - Signal generated when backspace key is pressed.
   */
  void signal_keyBackspace(void);

  /**
   * @brief signal_keyDelete - Signal generated when delete key is pressed.
   */
  void signal_keyDelete(void);

  /**
   * @brief signal_keyDown - Signal generated when down key is pressed.
   */
  void signal_keyDown(void);

  /**
   * @brief signal_keyLeft - Signal generated when left key is pressed.
   */
  void signal_keyLeft(void);

  /**
   * @brief signal_keyRight - Signal generated when right key is pressed.
   */
  void signal_keyRight(void);

  /**
   * @brief signal_keyUp - Signal generated when up key is pressed.
   */
  void signal_keyUp(void);
};

/**
 * @brief learnlibrarycustomwidgets_version - Check the version of this library
 * @param major                             - Major version number.
 * @param minor                             - Minor version number.
 * @param patch                             - Patch version number.
 */
void LEARNLIBRARYCUSTOMWIDGETS_EXPORT learnlibrarycustomwidgets_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // LEARNLIBRARYCUSTOMWIDGETS_H

