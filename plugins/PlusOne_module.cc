#include "art/Framework/Core/SharedProducer.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/ParameterSet.h"

namespace art::test {
  class PlusOne : public SharedProducer {
    ProductToken<int> token_;

  public:
    PlusOne(fhicl::ParameterSet const& pset, ProcessingFrame const&)
      : SharedProducer{pset}
      , token_{consumes<int>(pset.get<std::string>("inputLabel"))}
    {
      produces<int>("b");
      async<InEvent>();
    }

  private:
    void
    produce(Event& e, ProcessingFrame const&)
    {
      e.put(std::make_unique<int>(e.getProduct(token_) + 1), "b");
    }
  };
}

DEFINE_ART_MODULE(art::test::PlusOne)
