#ifndef GENERATION_HH
#define GENERATION_HH

namespace generation {

  template <typename PRNG, typename OutputIterator>
  void
  create_numbers (PRNG & rng, unsigned count, OutputIterator first) 
  {
    for (unsigned i = 0; i < count; ++i) 
      {
        *first++ = rng ();
      }
  }

}
#endif /* GENERATION_HH */
