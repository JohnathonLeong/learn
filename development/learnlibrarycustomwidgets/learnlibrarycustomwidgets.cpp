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

#include "learnlibrarycustomwidgets.h"

#define LEARNLIBRARYCUSTOMWIDGETS_VERSION_MAJOR 1
#define LEARNLIBRARYCUSTOMWIDGETS_VERSION_MINOR 0
#define LEARNLIBRARYCUSTOMWIDGETS_VERSION_PATCH 0
/**
 * @brief QtCustomLineEdit - Overloaded constructor.
 * @param parent           - QWidget parent pointer.
 */
QtCustomLineEdit::QtCustomLineEdit(QWidget * parent) :
  QLineEdit(parent)
{

}

/**
 * @brief QtCustomLineEdit - Default destructor.
 */
QtCustomLineEdit::~QtCustomLineEdit() {

}

/**
 * @brief keyPressEvent - Overloaded key press event function.
 * @param event         - Event pointer.
 */
void QtCustomLineEdit::keyPressEvent(QKeyEvent * event) {
  switch (event->key()) {
  case Qt::Key_Backspace:
    emit signal_keyBackspace();
    break;

  case Qt::Key_Delete:
    emit signal_keyDelete();
    break;

  case Qt::Key_Down:
    emit signal_keyDown();
    break;

  case Qt::Key_Left:
    emit signal_keyLeft();
    break;

  case Qt::Key_Right:
    emit signal_keyRight();
    break;

  case Qt::Key_Up:
    emit signal_keyUp();
    break;

  default:
    break;
  }

  QLineEdit::keyPressEvent(event);
}

/**
 * @brief learnlibrarycustomwidgets_version - Check the version of this library
 * @param major                             - Major version number.
 * @param minor                             - Minor version number.
 * @param patch                             - Patch version number.
 */
void learnlibrarycustomwidgets_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNLIBRARYCUSTOMWIDGETS_VERSION_MAJOR;
  minor = LEARNLIBRARYCUSTOMWIDGETS_VERSION_MINOR;
  patch = LEARNLIBRARYCUSTOMWIDGETS_VERSION_PATCH;
}
