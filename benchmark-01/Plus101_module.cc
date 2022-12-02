#include "art/Framework/Core/SharedProducer.h"
#include "art/Framework/Principal/Event.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/fwd.h"

namespace art::test {
  class Plus101 : public SharedProducer {
    InputTag tag_;

  public:
    Plus101(fhicl::ParameterSet const& pset, ProcessingFrame const&)
      : SharedProducer{pset}, tag_{pset.get<std::string>("inputLabel")}
    {
      consumes<int>(tag_);
      produces<int>("c");
      async<InEvent>();
    }

  private:
    void
    produce(Event& e, ProcessingFrame const&) override
    {
      e.put(std::make_unique<int>(e.getProduct<int>(tag_) + 101), "c");
    }
  };
}

DEFINE_ART_MODULE(art::test::Plus101)
