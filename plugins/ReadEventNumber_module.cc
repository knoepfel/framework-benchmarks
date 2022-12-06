#include "art/Framework/Core/SharedAnalyzer.h"
#include "art/Framework/Principal/Event.h"

#include <cassert>

namespace art::test {
  class ReadEventNumber : public SharedAnalyzer {
  public:
    struct Config {
    };

    using Parameters = Table<Config>;
    ReadEventNumber(Parameters const& pset, ProcessingFrame const&)
      : SharedAnalyzer{pset}
    {
      async<InEvent>();
    }

  private:
    void
    analyze(Event const& e, ProcessingFrame const&) override
    {
      assert(e.event() > 0u);
    }
  };
}

DEFINE_ART_MODULE(art::test::ReadEventNumber)
