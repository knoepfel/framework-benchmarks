#include "art/Framework/Core/SharedProducer.h"
#include "art/Framework/Principal/Event.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/fwd.h"

namespace art::test {
  class PlusOne : public SharedProducer {
    InputTag tag_;

  public:
    PlusOne(fhicl::ParameterSet const& pset, ProcessingFrame const&)
      : SharedProducer{pset}, tag_{pset.get<std::string>("inputLabel")}
    {
      consumes<int>(tag_);
      produces<int>("b");
      async<InEvent>();
    }

  private:
    void
    produce(Event& e, ProcessingFrame const&)
    {
      e.put(std::make_unique<int>(e.getProduct<int>(tag_) + 1), "b");
    }
  };
}

DEFINE_ART_MODULE(art::test::PlusOne)
