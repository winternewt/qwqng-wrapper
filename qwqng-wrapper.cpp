/*
 * Copyright (c) 2020 Newton Winter
 * Copyright (c) 2020 Andika Wasisto
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <qwqng.hpp>
#include <stdint.h>
#include <pthread.h>

//global
char* __buffer; 
char* __buffer_long; 
pthread_mutex_t __lock;


static void __attribute__((constructor)) con() {
  //init
  __buffer = new char[FTDIDEVICE_MAX_ARRAY_SIZE_];
  __buffer_long = NULL;
  pthread_mutex_init(&__lock, NULL);
}
static void __attribute__((destructor)) des() {
  pthread_mutex_destroy(&__lock);
  delete[] __buffer;
  __buffer_long && (delete[] __buffer_long, __buffer_long = NULL);
}


extern "C" {
    QWQNG* GetQwqngInstance() // create class instance
    {
        return new QWQNG();
    }
    
	/* Get random 32 bit integer as long */
    int32_t RandInt32(QWQNG *qwqng)
    {
        int32_t x;
        pthread_mutex_lock(&__lock);
		qwqng->RandInt32((long*)&x);
		pthread_mutex_unlock(&__lock);
        return x;
    }

	/* Get random uniform number [0,1) as double */
    double RandUniform(QWQNG *qwqng)
    {
        double x;
		pthread_mutex_lock(&__lock);
        qwqng->RandUniform(&x);
		pthread_mutex_unlock(&__lock);
        return x;
    }
	
	/* Get random normal number with mean zero and SD one as double */
    double RandNormal(QWQNG *qwqng)
    {
        double x;
        pthread_mutex_lock(&__lock);
		qwqng->RandNormal(&x);
		pthread_mutex_unlock(&__lock);
        return x;
    }
	
	/* Get unlimited random bytes */
    char* RandBytes(QWQNG *qwqng, int32_t length)
    {
        int32_t blocks;
		int32_t rem;
		blocks = length / FTDIDEVICE_MAX_ARRAY_SIZE_;
		pthread_mutex_lock(&__lock);
		__buffer_long && (delete[] __buffer_long, __buffer_long = NULL);
		__buffer_long = new char[length];
		for ( rem = 0; rem < blocks; rem++) {
			qwqng->RandBytes(__buffer, FTDIDEVICE_MAX_ARRAY_SIZE_);	
			memcpy ( __buffer_long+FTDIDEVICE_MAX_ARRAY_SIZE_*rem, __buffer, FTDIDEVICE_MAX_ARRAY_SIZE_ );
		}
		rem = length % FTDIDEVICE_MAX_ARRAY_SIZE_;		
		memcpy ( __buffer_long+FTDIDEVICE_MAX_ARRAY_SIZE_*blocks, __buffer, rem );
		pthread_mutex_unlock(&__lock);
		return __buffer_long;
    }
    
	/* Print open device serial number */
    char* DeviceID(QWQNG *qwqng)
    {
		char* SerialNumber;
        SerialNumber = qwqng->DeviceID();
        return SerialNumber;
    }
    
	/* Print open device serial number */
	char* StatusString(QWQNG *qwqng)
    {
		char* statusString; 
		statusString = qwqng->StatusString();
        return statusString;
    }
 
	/* Clear internal buffers */
    void Clear(QWQNG *qwqng)
    {    
		pthread_mutex_lock(&__lock);
		if ( qwqng->Clear() != S_OK ) 
			qwqng->Reset();
		pthread_mutex_unlock(&__lock);
    }
	
	/* Reset Device */
    void Reset(QWQNG *qwqng)
    {
        pthread_mutex_lock(&__lock);
		qwqng->Reset();
		pthread_mutex_unlock(&__lock);
    }
}
