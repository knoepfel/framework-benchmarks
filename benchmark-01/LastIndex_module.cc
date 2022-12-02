#include "art/Framework/Core/SharedProducer.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/fwd.h"

namespace art::test {
  class LastIndex : public SharedProducer {
  public:
    LastIndex(fhicl::ParameterSet const& pset, ProcessingFrame const&) : SharedProducer{pset}
    {
      produces<int>("a");
      async<InEvent>();
    }

  private:
    void
    produce(Event& e, ProcessingFrame const&) override
    {
      e.put(std::make_unique<int>(e.event()), "a");
    }
  };
}

DEFINE_ART_MODULE(art::test::LastIndex)
