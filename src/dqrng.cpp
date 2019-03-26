// Copyright 2018 Ralf Stubner (daqana GmbH)
//
// This file is part of dqrng.
//
// dqrng is free software: you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// dqrng is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with dqrng.  If not, see <http://www.gnu.org/licenses/>.

#include <boost/unordered_set.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <Rcpp.h>
#include <dqrng_generator.h>
#include <dqrng_distribution.h>
#include <xoshiro.h>
#include <pcg_random.hpp>
#include <threefry.h>
#include <convert_seed.h>
#include <R_randgen.h>

namespace {
dqrng::rng64_t init() {
  Rcpp::IntegerVector seed(2, dqrng::R_random_int);
  return dqrng::generator(dqrng::convert_seed<uint64_t>(seed));
}
dqrng::rng64_t rng = init();
}

// [[Rcpp::interfaces(r, cpp)]]

// [[Rcpp::export(rng = false)]]
void dqset_seed(Rcpp::IntegerVector seed, Rcpp::Nullable<Rcpp::IntegerVector> stream = R_NilValue) {
  uint64_t _seed = dqrng::convert_seed<uint64_t>(seed);
  if (stream.isNotNull()) {
      uint64_t _stream = dqrng::convert_seed<uint64_t>(stream.as());
    rng->seed(_seed, _stream);
  } else {
    rng->seed(_seed);
  }
}

//' @rdname dqrng-functions
//' @export
// [[Rcpp::export(rng = false)]]
void dqRNGkind(std::string kind, const std::string& normal_kind = "ignored") {
  for (auto & c: kind)
    c = std::tolower(c);
  uint64_t seed = rng->operator()();
  if (kind == "default") {
    rng =  dqrng::generator(seed);
  } else if (kind == "xoroshiro128+") {
    rng =  dqrng::generator<dqrng::xoroshiro128plus>(seed);
  } else if (kind == "xoshiro256+") {
    rng =  dqrng::generator<dqrng::xoshiro256plus>(seed);
  } else if (kind == "pcg64") {
    rng =  dqrng::generator<pcg64>(seed);
  } else if (kind == "threefry") {
    rng =  dqrng::generator<sitmo::threefry_20_64>(seed);
  } else {
    Rcpp::stop("Unknown random generator kind: %s", kind);
  }
}

//' @rdname dqrng-functions
//' @export
// [[Rcpp::export(rng = false)]]
Rcpp::NumericVector dqrunif(size_t n, double min = 0.0, double max = 1.0) {
  if(max / 2. - min / 2. > (std::numeric_limits<double>::max)() / 2.)
     return 2. * dqrunif(n, min/2., max/2.);

  dqrng::uniform_distribution dist(min, max);
  return dqrng::generate<dqrng::uniform_distribution, Rcpp::NumericVector>(n, rng, dist);
}

//' @rdname dqrng-functions
//' @export
// [[Rcpp::export(rng = false)]]
Rcpp::NumericVector dqrnorm(size_t n, double mean = 0.0, double sd = 1.0) {
  dqrng::normal_distribution dist(mean, sd);
  return dqrng::generate<dqrng::normal_distribution, Rcpp::NumericVector>(n, rng, dist);
}

//' @rdname dqrng-functions
//' @export
// [[Rcpp::export(rng = false)]]
Rcpp::NumericVector dqrexp(size_t n, double rate = 1.0) {
  dqrng::exponential_distribution dist(rate);
  return dqrng::generate<dqrng::exponential_distribution, Rcpp::NumericVector>(n, rng, dist);
}

// [[Rcpp::export(rng = false)]]
Rcpp::IntegerVector dqsample_int(int m,
                                 size_t n,
                                 bool replace = false,
                                 Rcpp::Nullable<Rcpp::NumericVector> probs = R_NilValue) {
    Rcpp::IntegerVector result(Rcpp::no_init(n));
    if (replace) {
        std::generate(result.begin(), result.end(), [m] () {return dqrng::bounded_rand32(*rng, m);});
    } else {
        std::vector<int> tmp(boost::counting_iterator<int>(0),
                             boost::counting_iterator<int>(m));

        for (size_t i = 0; i < n; ++i) {
            int j = dqrng::bounded_rand32(*rng, m);
            result(i) = tmp[j] + 1;
            tmp[j] = tmp[--m];
        }
    }
    return result;
}

// [[Rcpp::export(rng = false)]]
Rcpp::NumericVector dqsample_num(double m,
                                 size_t n,
                                 bool replace = false,
                                 Rcpp::Nullable<Rcpp::NumericVector> probs = R_NilValue) {
#ifndef LONG_VECTOR_SUPPORT
    Rcpp::stop("Long vectors are not supported");
#else
  uint64_t _m(m);
  Rcpp::NumericVector result(Rcpp::no_init(n));
  if (replace) {
    std::generate(result.begin(), result.end(), [_m] () {return dqrng::bounded_rand64(*rng, _m);});
  } else {
    // https://stackoverflow.com/a/28287865/8416610
    boost::unordered_set<uint64_t> elems(1.5 * n);
    for (uint64_t r = _m - n; r < _m; ++r) {
      uint64_t v = dqrng::bounded_rand64(*rng, r);
      // there are two cases.
      // v is not in candidates ==> add it
      // v is in candidates ==> well, r is definitely not, because
      // this is the first iteration in the loop that we could've
      // picked something that big.

      if (!elems.insert(v).second) {
        elems.insert(r);
      }
    }
    // TODO: shuffle result
    std::copy(elems.begin(), elems.end(), result.begin());
  }
  return result;
#endif
}
