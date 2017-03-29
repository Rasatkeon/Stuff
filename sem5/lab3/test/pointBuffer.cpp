//
// Created by timecat on 11/22/16.
//

#include "pointBuffer.hpp"

void pointBuffer::setXs(float *xs) {
    for (int i = 0; i < size; ++i) {
        points[i].x = xs[i];
    }
}

const size_t pointBuffer::getSize() const {
    return size;
}

const pointBuffer::point *pointBuffer::getPoints() const {
    return points;
}

void pointBuffer::calculateYs(std::function<float(float)> f) {
    for (int i = 0; i < size; ++i) {
        points[i].y = f(points[i].x);
    }
}

float *pointBuffer::genPoints(float a, float b, size_t size) {
    float* res = new float[size];
    float step = (b - a)/size;

    for (int i = 0; i < size; ++i) {
        res[i] = a + step*i;
    }

    return res;
}

pointBuffer *pointBuffer::calculatePoints(float *xs,
                                          std::function<float(float)> f,
                                          size_t size) {
    pointBuffer* res = new pointBuffer(size);
    res->setXs(xs);
    res->calculateYs(f);
    return res;
}

pointBuffer *pointBuffer::calculatePoints(float a, float b,
                                          std::function<float(float)> f,
                                          size_t size) {
    float* temp = genPoints(a, b, size);
    pointBuffer* res = calculatePoints(temp, f, size);
    delete[](temp);
    return res;
}
