//
// Created by timecat on 11/22/16.
//

#ifndef GL_TEST_POINTBUFFER_HPP
#define GL_TEST_POINTBUFFER_HPP

#include <cstddef>
#include <cstring>
#include <functional>

class pointBuffer {
private:
    struct point {
        float x;
        float y;
        point(float x, float y) : x(x), y(y) { };
    };
    size_t size;
    point* points;
    pointBuffer(size_t size) : size(size) { }

    void setXs(float *xs);
    void calculateYs(std::function<float(float)> f);

    static float* genPoints(float a, float b, size_t size);

public:

    const point *getPoints() const;
    const size_t getSize() const;

    static pointBuffer* calculatePoints(float a, float b,
                                        std::function<float(float)> f,
                                        size_t size);
    static pointBuffer* calculatePoints(float* xs,
                                        std::function<float(float)> f,
                                        size_t size);

};


#endif //GL_TEST_POINTBUFFER_HPP
