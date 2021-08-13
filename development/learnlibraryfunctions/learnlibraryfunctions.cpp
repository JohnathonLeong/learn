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

#include "learnlibraryfunctions.h"
#include "genericlibrarymaths.h"
#include <QDir>
#include <time.h>

#define LEARNLIBRARYFUNCTIONS_VERSION_MAJOR 1
#define LEARNLIBRARYFUNCTIONS_VERSION_MINOR 0
#define LEARNLIBRARYFUNCTIONS_VERSION_PATCH 1

/**
 * @brief learnlibraryquestiongenerator - Default constructor.
 */
learnlibraryquestiongenerator::learnlibraryquestiongenerator() {
  mPath.clear();
}

/**
 * @brief learnlibraryquestiongenerator - Overloaded constructor.
 * @param path                      - The path to the stored images to be used for questions.
 */
learnlibraryquestiongenerator::learnlibraryquestiongenerator(QString path) {
  setImagePath(path);
}

/**
 * @brief learnlibraryquestiongenerator - Default destructor.
 */
learnlibraryquestiongenerator::~learnlibraryquestiongenerator() {
}

/**
 * @brief getQuestions_MULTIPLE - Generate multiplie option questions for Learn software. Number
 *                                of questions generated depends on the input argument.
 * @param answer                - The answer.
 * @param image                 - The image of the answer.
 * @param options               - The list of randomized options.
 * @param answerIndex           - The index number of the answer in the list of randomized options.
 * @param size                  - The number of options to be generated.
 * @return                      - The status of fucntion.
 */
unsigned char learnlibraryquestiongenerator::getQuestions_MULTIPLE(QString & answer, QImage & image, QStringList & options, unsigned long & answerIndex, unsigned long size) {
  unsigned char status = 0;
  options.clear();

  if (mPath.length() > 0) {                                         // check if path has been initialized
    unsigned long qnsLength = (unsigned long)(mQuestions.length()); // retrieve questions size
    if (qnsLength > size) {                                         // check if required size is larger than question size
      QStringList qstrlist;

      unsigned long qnsArray[qnsLength];                            // instantiate qnsArray
      unsigned long optArray[size];

      for (unsigned long i = 0; i < qnsLength; i++)                 // loop through qnsArray
        qnsArray[i] = i;                                            //   assign index number to qnsArray
      shuffle(qnsArray, qnsLength);                                 // shuffle the index numbers

      qstrlist = mQuestions.at(qnsArray[0]).split('.');
      answer = qstrlist.first();
      QImageReader imageReader(mPath + "/" + answer);
      image = imageReader.read();

      for (unsigned long i = 0; i < size; i++)
        optArray[i] = qnsArray[i];
      shuffle(optArray, size);
      for (unsigned long i = 0; i < size; i++) {
        qstrlist = mQuestions.at(optArray[i]).split('.');
        options.append(qstrlist.first());
        if (qstrlist.first() == answer)
          answerIndex = i;
      }

      status = 1;
    }
    else {
      status = 2;
    }
  }

  return status;
}

/**
 * @brief getQuestions_ONE - Generate a question for Learn software.
 * @param answer           - The answer.
 * @param image            - The image of the answer.
 * @return                 - The status of fucntion.
 */
unsigned char learnlibraryquestiongenerator::getQuestions_ONE(QString & answer, QImage & image) {
  unsigned char status = 0;

  if (mPath.length() > 0) {
    unsigned long index = (mQuestions.length() > 0) ? rand() % mQuestions.length() : 0;
    QStringList answerList = mQuestions.at(index).split('.');
    answer = answerList.first();
    QImageReader imageReader(mPath + "/" + answer);
    image = imageReader.read();
    status = 1;
  }

  return status;
}

/**
 * @brief setImagePath - To set the path to the stored images to be used for questions.
 * @param path         - The path.
 * @return             - The status of fucntion.
 */
unsigned char learnlibraryquestiongenerator::setImagePath(QString path) {
  unsigned char status = 0;

  srand(time(NULL));
  mPath = path;
  srand(rand());
  QDir directory = QString(mPath);
  srand(rand());
  mQuestions = directory.entryList(QStringList() << "*.jpg" << "*.JPG", QDir::Files);
  srand(rand());
  if (mQuestions.length() > 0)
    status = 1;
  srand(rand());

  return status;
}

/**
 * @brief learnlibraryfunctions_version - Check the version of this library
 * @param major                         - Major version number.
 * @param minor                         - Minor version number.
 * @param patch                         - Patch version number.
 */
void learnlibraryfunctions_version(unsigned long & major, unsigned long & minor, unsigned long & patch) {
  major = LEARNLIBRARYFUNCTIONS_VERSION_MAJOR;
  minor = LEARNLIBRARYFUNCTIONS_VERSION_MINOR;
  patch = LEARNLIBRARYFUNCTIONS_VERSION_PATCH;
}
