#include "art/Framework/Core/SharedProducer.h"
#include "art/Framework/Principal/Event.h"
#include "fhiclcpp/ParameterSet.h"

namespace art::test {
  class Plus101 : public SharedProducer {
    ProductToken<int> token_;

  public:
    Plus101(fhicl::ParameterSet const& pset, ProcessingFrame const&)
      : SharedProducer{pset}
      , token_{consumes<int>(pset.get<std::string>("inputLabel"))}
    {
      produces<int>("c");
      async<InEvent>();
    }

  private:
    void
    produce(Event& e, ProcessingFrame const&) override
    {
      e.put(std::make_unique<int>(e.getProduct(token_) + 101), "c");
    }
  };
} // namespace art::test

DEFINE_ART_MODULE(art::test::Plus101)
