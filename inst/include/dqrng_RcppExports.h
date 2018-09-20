// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#ifndef RCPP_dqrng_RCPPEXPORTS_H_GEN_
#define RCPP_dqrng_RCPPEXPORTS_H_GEN_

#include <Rcpp.h>

namespace dqrng {

    using namespace Rcpp;

    namespace {
        void validateSignature(const char* sig) {
            Rcpp::Function require = Rcpp::Environment::base_env()["require"];
            require("dqrng", Rcpp::Named("quietly") = true);
            typedef int(*Ptr_validate)(const char*);
            static Ptr_validate p_validate = (Ptr_validate)
                R_GetCCallable("dqrng", "_dqrng_RcppExport_validate");
            if (!p_validate(sig)) {
                throw Rcpp::function_not_exported(
                    "C++ function with signature '" + std::string(sig) + "' not found in dqrng");
            }
        }
    }

    inline void dqset_seed(Rcpp::IntegerVector seed, Rcpp::Nullable<Rcpp::IntegerVector> stream = R_NilValue) {
        typedef SEXP(*Ptr_dqset_seed)(SEXP,SEXP);
        static Ptr_dqset_seed p_dqset_seed = NULL;
        if (p_dqset_seed == NULL) {
            validateSignature("void(*dqset_seed)(Rcpp::IntegerVector,Rcpp::Nullable<Rcpp::IntegerVector>)");
            p_dqset_seed = (Ptr_dqset_seed)R_GetCCallable("dqrng", "_dqrng_dqset_seed");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqset_seed(Shield<SEXP>(Rcpp::wrap(seed)), Shield<SEXP>(Rcpp::wrap(stream)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

    inline void dqRNGkind(std::string kind, const std::string& normal_kind = "ignored") {
        typedef SEXP(*Ptr_dqRNGkind)(SEXP,SEXP);
        static Ptr_dqRNGkind p_dqRNGkind = NULL;
        if (p_dqRNGkind == NULL) {
            validateSignature("void(*dqRNGkind)(std::string,const std::string&)");
            p_dqRNGkind = (Ptr_dqRNGkind)R_GetCCallable("dqrng", "_dqrng_dqRNGkind");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqRNGkind(Shield<SEXP>(Rcpp::wrap(kind)), Shield<SEXP>(Rcpp::wrap(normal_kind)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
    }

    inline Rcpp::NumericVector dqrunif(size_t n, double min = 0.0, double max = 1.0) {
        typedef SEXP(*Ptr_dqrunif)(SEXP,SEXP,SEXP);
        static Ptr_dqrunif p_dqrunif = NULL;
        if (p_dqrunif == NULL) {
            validateSignature("Rcpp::NumericVector(*dqrunif)(size_t,double,double)");
            p_dqrunif = (Ptr_dqrunif)R_GetCCallable("dqrng", "_dqrng_dqrunif");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqrunif(Shield<SEXP>(Rcpp::wrap(n)), Shield<SEXP>(Rcpp::wrap(min)), Shield<SEXP>(Rcpp::wrap(max)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<Rcpp::NumericVector >(rcpp_result_gen);
    }

    inline Rcpp::NumericVector dqrnorm(size_t n, double mean = 0.0, double sd = 1.0) {
        typedef SEXP(*Ptr_dqrnorm)(SEXP,SEXP,SEXP);
        static Ptr_dqrnorm p_dqrnorm = NULL;
        if (p_dqrnorm == NULL) {
            validateSignature("Rcpp::NumericVector(*dqrnorm)(size_t,double,double)");
            p_dqrnorm = (Ptr_dqrnorm)R_GetCCallable("dqrng", "_dqrng_dqrnorm");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqrnorm(Shield<SEXP>(Rcpp::wrap(n)), Shield<SEXP>(Rcpp::wrap(mean)), Shield<SEXP>(Rcpp::wrap(sd)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<Rcpp::NumericVector >(rcpp_result_gen);
    }

    inline Rcpp::NumericVector dqrexp(size_t n, double rate = 1.0) {
        typedef SEXP(*Ptr_dqrexp)(SEXP,SEXP);
        static Ptr_dqrexp p_dqrexp = NULL;
        if (p_dqrexp == NULL) {
            validateSignature("Rcpp::NumericVector(*dqrexp)(size_t,double)");
            p_dqrexp = (Ptr_dqrexp)R_GetCCallable("dqrng", "_dqrng_dqrexp");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqrexp(Shield<SEXP>(Rcpp::wrap(n)), Shield<SEXP>(Rcpp::wrap(rate)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<Rcpp::NumericVector >(rcpp_result_gen);
    }

    inline Rcpp::IntegerVector dqsample_int(int m, size_t n, bool replace = false, Rcpp::Nullable<Rcpp::NumericVector> probs = R_NilValue) {
        typedef SEXP(*Ptr_dqsample_int)(SEXP,SEXP,SEXP,SEXP);
        static Ptr_dqsample_int p_dqsample_int = NULL;
        if (p_dqsample_int == NULL) {
            validateSignature("Rcpp::IntegerVector(*dqsample_int)(int,size_t,bool,Rcpp::Nullable<Rcpp::NumericVector>)");
            p_dqsample_int = (Ptr_dqsample_int)R_GetCCallable("dqrng", "_dqrng_dqsample_int");
        }
        RObject rcpp_result_gen;
        {
            rcpp_result_gen = p_dqsample_int(Shield<SEXP>(Rcpp::wrap(m)), Shield<SEXP>(Rcpp::wrap(n)), Shield<SEXP>(Rcpp::wrap(replace)), Shield<SEXP>(Rcpp::wrap(probs)));
        }
        if (rcpp_result_gen.inherits("interrupted-error"))
            throw Rcpp::internal::InterruptedException();
        if (Rcpp::internal::isLongjumpSentinel(rcpp_result_gen))
            throw Rcpp::LongjumpException(rcpp_result_gen);
        if (rcpp_result_gen.inherits("try-error"))
            throw Rcpp::exception(Rcpp::as<std::string>(rcpp_result_gen).c_str());
        return Rcpp::as<Rcpp::IntegerVector >(rcpp_result_gen);
    }

}

#endif // RCPP_dqrng_RCPPEXPORTS_H_GEN_
