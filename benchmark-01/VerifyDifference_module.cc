#include "art/Framework/Core/SharedAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/fwd.h"

#include <cassert>

namespace art::test {
  class VerifyDifference : public SharedAnalyzer {
    InputTag tagA_;
    InputTag tagB_;

  public:
    struct Config {
      fhicl::Atom<std::string> inputLabelA{fhicl::Name{"inputLabelA"}};
      fhicl::Atom<std::string> inputLabelB{fhicl::Name{"inputLabelB"}};
    };

    using Parameters = Table<Config>;
    VerifyDifference(Parameters const& pset, ProcessingFrame const&)
      : SharedAnalyzer{pset}
      , tagA_{pset().inputLabelA()}
      , tagB_{pset().inputLabelB()}
    {
      consumes<int>(tagA_);
      consumes<int>(tagB_);
      async<InEvent>();
    }

  private:
    void
    analyze(Event const& e, ProcessingFrame const&) override
    {
      assert(e.getProduct<int>(tagB_) - e.getProduct<int>(tagA_) == 100);
    }
  };
}

DEFINE_ART_MODULE(art::test::VerifyDifference)
