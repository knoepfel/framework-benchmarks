#include "art/Framework/Core/SharedAnalyzer.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/types/Atom.h"

#include <cassert>

namespace art::test {
  class VerifyDifference : public SharedAnalyzer {
    ProductToken<int> tokenA_;
    ProductToken<int> tokenB_;

  public:
    struct Config {
      fhicl::Atom<std::string> inputLabelA{fhicl::Name{"inputLabelA"}};
      fhicl::Atom<std::string> inputLabelB{fhicl::Name{"inputLabelB"}};
    };

    using Parameters = Table<Config>;
    VerifyDifference(Parameters const& pset, ProcessingFrame const&)
      : SharedAnalyzer{pset}
      , tokenA_{consumes<int>(pset().inputLabelA())}
      , tokenB_{consumes<int>(pset().inputLabelB())}
    {
      async<InEvent>();
    }

  private:
    void
    analyze(Event const& e, ProcessingFrame const&) override
    {
      assert(e.getProduct(tokenB_) - e.getProduct(tokenA_) == 100);
    }
  };
}

DEFINE_ART_MODULE(art::test::VerifyDifference)
