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

#ifndef LEARNAPPSSELECTION_H
#define LEARNAPPSSELECTION_H

#include <QtCore/qglobal.h>

#if defined(LEARNAPPSSELECTION_LIBRARY)
#  define LEARNAPPSSELECTION_EXPORT Q_DECL_EXPORT
#else
#  define LEARNAPPSSELECTION_EXPORT
#endif

#include <QWidget>
#include <QPushButton>

#define LEARNAPPSSELECTION_APPS_ROW_NUM 4
#define LEARNAPPSSELECTION_APPS_COL_NUM 6
#define LEARNAPPSSELECTION_APPS_TOTAL_NUM LEARNAPPSSELECTION_APPS_ROW_NUM * LEARNAPPSSELECTION_APPS_COL_NUM
#define LEARNAPPSSELECTION_APPS_AVAILABLE 4

class LEARNAPPSSELECTION_EXPORT learnappsselection : public QWidget {
  Q_OBJECT
public:
  /**
   * @brief learnappsselection - Overloaded constructor.
   * @param parent           - QWidget parent pointer.
   */
  learnappsselection(QWidget * parent);

  /**
   * @brief learnappsselection - Default destructor.
   */
  ~learnappsselection();

signals:
  /**
   * @brief signal_Resize - Signal generated when widget resize occurs.
   */
  void signal_Resize(int width, int height);

private:
  void about(void );

  /**
   * @brief initAttributes - Initialization of the class attributes.
   */
  void initAttributes(void );

  /**
   * @brief initWidget - Initialization of the class widgets.
   */
  void initWidget(void );

  void readme(void );

  QStringList mAppsNames;

  /**
   * @brief mpApps - QPushButton widget for learn apps selection.
   */
  QPushButton * mpApps[LEARNAPPSSELECTION_APPS_TOTAL_NUM];

  /**
   * @brief mpDisplayApps - QWidget widget to display selected learn apps.
   */
  QWidget * mpDisplayApps;

  /**
   * @brief mpSelectedApp - QWidget widget to display apps available for selection.
   */
  QWidget * mpSelectedApp;

private slots:
  /**
   * @brief slot_mpAppsSelect - Slot to handle when mpApps QPushButton is pressed.
   */
  void slot_mpAppsSelect();

  /**
   * @brief slot_mpSelectedAppClose - Slot to handle when learn apps is being closed.
   */
  void slot_mpSelectedAppClose();
};

/**
 * @brief learnappsselection_version - Check the version of this library
 * @param major                      - Major version number.
 * @param minor                      - Minor version number.
 * @param patch                      - Patch version number.
 */
void LEARNAPPSSELECTION_EXPORT learnappsselection_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // LEARNAPPSSELECTION_H
