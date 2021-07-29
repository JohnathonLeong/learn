/*
 * Copyright:   2021 Johnathon Leong
 *
 * License:     License under LGPL-3.0-or-later.
 *              Please refer to https://www.gnu.org/licenses/lgpl-3.0.txt for more information on the
 *              terms of LGPL-3.0 or relavent website for a later version of the LGPL.
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
 * Change Log:  1. Implemented "shuffle()" functions for various data type arrays.
 *              2. Implemented "version()" function.
 */

#ifndef GENERICLIBRARYMATHS_H
#define GENERICLIBRARYMATHS_H

#include <QtCore/qglobal.h>

#if defined(GENERICLIBRARYMATHS_LIBRARY)
#define GENERICLIBRARYMATHS_EXPORT Q_DECL_EXPORT
#else
#define GENERICLIBRARYMATHS_EXPORT
#endif

/**
 * @brief shuffle   - Shuffle the numbers in a char data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(char * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in a double data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(double * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in a float data type  array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(float * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in a long data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(long * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in a long long data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(long long * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in a short data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(short * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in an unsigned char data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(unsigned char * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in an unsigned long data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(unsigned long * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in an unsigned long long data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(unsigned long long * array, unsigned long long arraySize);

/**
 * @brief shuffle   - Shuffle the numbers in an unsigned short data type array.
 * @param array     - Array that contains the numbers to be shuffled.
 * @param arraySize - Specify the array size.
 */
void GENERICLIBRARYMATHS_EXPORT shuffle(unsigned short * array, unsigned long long arraySize);

/**
 * @brief genericlibrarymaths_version - Check the version of this library
 * @param major                       - Major version number.
 * @param minor                       - Minor version number.
 * @param patch                       - Patch version number.
 */
void GENERICLIBRARYMATHS_EXPORT genericlibrarymaths_version(unsigned long & major, unsigned long & minor, unsigned long & patch);

#endif // GENERICLIBRARYMATHS_H
