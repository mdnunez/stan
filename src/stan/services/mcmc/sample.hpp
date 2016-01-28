#ifndef STAN_SERVICES_MCMC_SAMPLE_HPP
#define STAN_SERVICES_MCMC_SAMPLE_HPP

#include <stan/interface_callbacks/writer/base_writer.hpp>
#include <stan/mcmc/base_mcmc.hpp>
#include <stan/services/sample/mcmc_writer.hpp>
#include <stan/services/sample/generate_transitions.hpp>
#include <string>

namespace stan {
  namespace services {
    namespace mcmc {

      template <class Model, class rng_t, class StartTransitionCallback,
                class SampleRecorder, class DiagnosticRecorder,
                class MessageRecorder>
      void sample(stan::mcmc::base_mcmc* sampler,
                  int num_warmup,
                  int num_samples,
                  int num_thin,
                  int refresh,
                  bool save,
                  stan::services::sample::mcmc_writer<
                  Model, SampleRecorder, DiagnosticRecorder, MessageRecorder>&
                  mcmc_writer,
                  stan::mcmc::sample& init_s,
                  Model& model,
                  rng_t& base_rng,
                  StartTransitionCallback& callback,
                  interface_callbacks::writer::base_writer& writer) {
        stan::services::sample::generate_transitions<Model, rng_t,
                                                     StartTransitionCallback,
                                                     SampleRecorder,
                                                     DiagnosticRecorder,
                                                     MessageRecorder>
          (sampler, num_samples, num_warmup, num_warmup + num_samples, num_thin,
           refresh, save, false,
           mcmc_writer,
           init_s, model, base_rng,
           callback, writer);
      }

    }
  }
}

#endif
