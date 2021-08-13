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
 * Date:        2021/08/13 (YYYY/MM/DD)
 * Change Log:  1. Rename the function
 *                   learnlibraryquestiongenerator_version
 *                 to
 *                    learnlibraryfunctions_version
 *
 * Version:     1.0.0
 * Date:        2021/07/29 (YYYY/MM/DD)
 * Change Log:  1. First release of learnlibraryfunctions.
 *              2. Implemented learnlibraryquestiongenerator class.
 */

#ifndef LEARNLIBRARYFUNCTIONS_H
#define LEARNLIBRARYFUNCTIONS_H

#include <QString>
#include <QStringList>
#include <QImageReader>

#include <QtCore/qglobal.h>

#if defined(LEARNLIBRARYFUNCTIONS_LIBRARY)
#  define LEARNLIBRARYFUNCTIONS_EXPORT Q_DECL_EXPORT
#else
#  define LEARNLIBRARYFUNCTIONS_EXPORT
#endif

class LEARNLIBRARYFUNCTIONS_EXPORT learnlibraryquestiongenerator
{
public:
  /**
   * @brief learnlibraryquestiongenerator - Default constructor.
   */
  learnlibraryquestiongenerator();

  /**
   * @brief learnlibraryquestiongenerator - Overloaded constructor.
   * @param path                          - The path to the stored images to be used for questions.
   */
  learnlibraryquestiongenerator(QString path);

  /**
   * @brief ~learnlibraryquestiongenerator - Default destructor.
   */
  ~learnlibraryquestiongenerator();

  /**
   * @brief getQuestions_MULTIPLE - Generate multiplie option questions for Learn software. Number
   *                                of questions generated depends on the input argument.
   * @param answer                - The answer.
   * @param image                 - The image of the answer.
   * @param options               - The list of randomized options.
   * @param answerIndex           - The index number of the answer in the list of randomized options.
   * @param size                  - The number of options to be generated.
   * @return
   */
  unsigned char getQuestions_MULTIPLE(QString & answer, QImage & image, QStringList & options, unsigned long & answerIndex, unsigned long size);

  /**
   * @brief getQuestions_ONE - Generate a question for Learn software.
   * @param answer           - The answer.
   * @param image            - The image of the answer.
   * @return                 - The status of fucntion.
   */
  unsigned char getQuestions_ONE(QString & answer, QImage & image);

  /**
   * @brief setImagePath - To set the path to the stored images to be used for questions.
   * @param path         - The path.
   * @return             - The status of fucntion.
   */
  unsigned char setImagePath(QString path);

private:
  /**
   * @brief mPath - Store the path to the folder of the questions.
   */
  QString     mPath;

  /**
   * @brief mQuestions - Store the list of the available questions in the folder.
   */
  QStringList mQuestions;
};

/**
 * @brief learnlibraryfunctions_version - Check the version of this library
 * @param major                         - Major version number.
 * @param minor                         - Minor version number.
 * @param patch                         - Patch version number.
 */
void LEARNLIBRARYFUNCTIONS_EXPORT learnlibraryfunctions_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // LEARNLIBRARYFUNCTIONS_H

