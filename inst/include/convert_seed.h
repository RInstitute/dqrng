#ifndef DQRNG_CONVERT_SEED_H_INCLUDED
#define DQRNG_CONVERT_SEED_H_INCLUDED

#include <Rcpp.h>
#include <stdexcept>
#include <type_traits>
#include <limits>

/* This is an internal function - not to be called by users. 
 * It converts a seed vector ('seeds') into a single unsigned
 * integer of specified type 'OUT' with all bits set according
 * to the combined bit pattern of the individual seed elements.
 * This is achieved by bit shifting, with the first element
 * of 'seeds' contributing the most significant bits in the output
 * and the last element contributing the least significant bits.
 *
 * Each element of 'seeds' is cast from 'IN' to the corresponding
 * unsigned type. 'IN' should have no more than last 'SHIFT' bits 
 * set. Compile- or run-time errors will be raised for seeds
 * that exceed the size of the maximum integer storable in 'OUT'.
 */

template<typename OUT, typename IN, int SHIFT>
OUT convert_seed_internal(const IN* seeds, size_t N) {
    static_assert(std::is_unsigned<OUT>::value, "output integer type should be unsigned");
    constexpr OUT upper=-1;

    // Check to avoid UB from right-shifting by the length of OUT in bits.
    constexpr int OUT_size=std::numeric_limits<OUT>::digits;
    constexpr bool shiftable=OUT_size > SHIFT;
    constexpr OUT left_upper=(shiftable ? upper >> SHIFT: 0);

    typedef typename std::make_unsigned<IN>::type UIN;
    constexpr int UIN_size=std::numeric_limits<UIN>::digits;

    OUT sum=0;
    for (size_t i=0; i<N; ++i) {
        UIN unsigned_seed=seeds[i];
        if (UIN_size > OUT_size) { // Checking that the UIN value fits inside OUT.
            if (unsigned_seed > upper) {
                throw std::out_of_range("seed element out of range for possible integers");
            }
        }

        OUT current=unsigned_seed;
        if (UIN_size > SHIFT && shiftable) { // Checking that the seed value contains no more than SHIFT set bits.
            if (current >> SHIFT != 0) { // using 'current' to avoid shift warnings from GCC on common 32-bit 'int' platforms.
                throw std::runtime_error("seed element out of range for possible integers");
            }
        }

        if (left_upper < sum) { // Avoid overflow upon right shift.
            throw std::out_of_range("vector implies an out-of-range seed");
        }
        if (shiftable) { // Avoid UB from left-shifting by the length of OUT in bits.
            sum <<= SHIFT;
        }

        if (upper - current < sum) { // Subtract first, to avoid overflow during check.
            throw std::out_of_range("vector implies an out-of-range seed");
        }
        sum |= current;
    }

    return sum;
}

/* Re-start of user-visible functions here. 'convert_seed'
 * is overloaded for direct use of input uint32_t's generated
 * by, e.g., std::random_device; to use int's from some other
 * source; or to use int's passed in from R.
 */

template<typename T>
T convert_seed(const uint32_t* seeds, size_t N) {
    return convert_seed_internal<T, uint32_t, 32>(seeds, N);
}

template<typename T>
T convert_seed(const int* seeds, size_t N) {
    return convert_seed_internal<T, int, 32>(seeds, N); 
}

template<typename T>
T convert_seed(Rcpp::IntegerVector seeds) {
    return convert_seed<T>(seeds.begin(), seeds.size());
}

#endif
