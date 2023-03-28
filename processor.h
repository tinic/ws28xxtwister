#ifndef _PROCESSOR_H_
#define _PROCESSOR_H_

#include <stdint.h>
#include <stdlib.h>

#include <type_traits>
#include <utility>

class Processor {
public:
    Processor() : next(nullptr) {}
    virtual ~Processor() {};

    void setNext(Processor &_next) { next = &_next; }

    virtual void process(uint32_t input) = 0;

protected:
    Processor *next;

private:
    Processor(const Processor &_next) : next(0) {}
    Processor &operator=(const Processor&) { return *this; }
};

class NullProcessor : public Processor {
public:
    virtual void process(uint32_t input) { next->process(input); };
};

class OutProcessor : public Processor {
public:
    virtual void process(uint32_t input) {  };
};

class SkipperProcessor : public Processor {
public:
    SkipperProcessor() : Processor(), countN(0), skipN(0) {};

    void setSkipN(size_t N) { skipN = N; }

    void process(uint32_t input) {
        if (input > 0xFF) {
            countN = 0;
            next->process(input);
            return;
        }
        if (countN < skipN) {
            return;
        }
        next->process(input);
    }

private:
    size_t skipN = 0;
    size_t countN = 0;
};

template<class T, T... inds, class F>
constexpr void loop(std::integer_sequence<T, inds...>, F&& f) {
    (f(std::integral_constant<T, inds>{}), ...);
}

template<class T, T count, class F>
constexpr void loop(F&& f) {
    loop(std::make_integer_sequence<T, count>{}, std::forward<F>(f));
}

template <size_t N> class SwizzleProcessor : public Processor {
public:
    static_assert(N <= 8);
    SwizzleProcessor() : Processor(), swizzle(0) {};

    void setSwizzle(uint32_t _swizzle) { swizzle = _swizzle; }

    void process(uint32_t input) {
        loop<size_t, N>([=] (auto i) {
            bufOut[i] = bufIn[(swizzle >> (i*4)) & 0x7];
        });
        next->process(input);
    }

private:
    uint32_t swizzle;
    uint32_t bufIn[N] = {};
    uint32_t bufOut[N] = {};
};

#endif //  #ifndef _PROCESSOR_H_
