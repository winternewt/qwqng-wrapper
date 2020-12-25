/*
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

extern "C" {
    QWQNG* GetQwqngInstance()
    {
        return new QWQNG();
    }

    int RandInt32(QWQNG *qwqng)
    {
        int x;
        qwqng->RandInt32((long*) &x);
        return x;
    }

    double RandUniform(QWQNG *qwqng)
    {
        double x;
        qwqng->RandUniform(&x);
        return x;
    }

    double RandNormal(QWQNG *qwqng)
    {
        double x;
        qwqng->RandNormal(&x);
        return x;
    }

    char* RandBytes(QWQNG *qwqng, int length)
    {
        char* bytes = new char[length];
        qwqng->RandBytes(bytes, length);
        return bytes;
    }

    char* DeviceID(QWQNG *qwqng)
    {
        char* SerialNumber;
        SerialNumber = qwqng->DeviceID();
        return SerialNumber;
    }

    void Clear(QWQNG *qwqng)
    {
        qwqng->Clear();
    }

    void Reset(QWQNG *qwqng)
    {
        qwqng->Reset();
    }
}
