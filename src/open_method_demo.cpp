  // =============================================================================
  // Domain classes.

  class Animal {
    public:
      virtual ~Animal() {
      }
  };

  class Dog : public Animal {};
  class Bulldog : public Dog {};
  class Cat : public Animal {};
  class Dolphin : public Animal {};

  // =============================================================================
  // Add behavior to existing classes, without modifying them.

  #include <boost/openmethod.hpp>
  #include <boost/openmethod/compiler.hpp>

  // Classes must be registered:
  BOOST_OPENMETHOD_CLASSES(Animal, Dog, Cat, Dolphin);

  // ...but it does not have to be in one call to 'BOOST_OPENMETHOD_CLASSES', as long as
  // inheritance relationships can be deduced. This allows *adding* classes to an
  // existing collection of classes.
  BOOST_OPENMETHOD_CLASSES(Dog, Bulldog);

  // Define a uni-method, i.e. a method with a single virtual argument. This is in
  // essence a virtual function implemented as a free function.
  BOOST_OPENMETHOD(poke, (virtual_ptr<Animal>, std::ostream&), void);

  // Implement 'poke' for dogs.
  BOOST_OPENMETHOD_OVERRIDE(poke, (virtual_ptr<Dog> dog, std::ostream& os), void) {
      os << "bark";
  }

  // Implement 'poke' for bulldogs. They behave like Dogs, but, in addition, they
  // fight back.
  BOOST_OPENMETHOD_OVERRIDE(poke, (virtual_ptr<Bulldog> dog, std::ostream& os), void) {
      next(dog, os); // calls "base" method, i.e. definition for Dog
      os << " and bite";
  }

  // A multi-method with two virtual arguments...
  BOOST_OPENMETHOD(meet, (virtual_ptr<Animal>, virtual_ptr<Animal>, std::ostream&), void);

  // 'meet' catch-all implementation.
  BOOST_OPENMETHOD_OVERRIDE(meet, (virtual_ptr<Animal>, virtual_ptr<Animal>, std::ostream& os), void) {
      os << "ignore";
  }

  // Add definitions for specific pairs of animals.
  BOOST_OPENMETHOD_OVERRIDE(meet, (virtual_ptr<Dog> dog1, virtual_ptr<Dog> dog2, std::ostream& os), void) {
      os << "wag tail";
  }

  BOOST_OPENMETHOD_OVERRIDE(meet, (virtual_ptr<Dog> dog, virtual_ptr<Cat> cat, std::ostream& os), void) {
      os << "chase";
  }

  BOOST_OPENMETHOD_OVERRIDE(meet, (virtual_ptr<Cat> cat, virtual_ptr<Dog> dog, std::ostream& os), void) {
      os << "run";
  }

  // =============================================================================
  // main

  #include <iostream>
  #include <memory>
  #include <string>

  auto main() -> int {
      // Initialize the dispatch tables.
      boost::openmethod::initialize();

      // Create a few objects.
      // Note that the actual classes are type-erased to base class Animal!
      std::unique_ptr<Animal>
          hector = std::make_unique<Bulldog>(),
          snoopy = std::make_unique<Dog>(),
          sylvester = std::make_unique<Cat>(),
          flipper = std::make_unique<Dolphin>();

      // Call 'poke'.
      std::cout << "poke snoopy: ";
      poke(*snoopy, std::cout); // bark
      std::cout << "\n";

      std::cout << "poke hector: ";
      poke(*hector, std::cout); // bark and bite
      std::cout << "\n";

      // Call 'meet'.
      std::cout << "hector meets sylvester: ";
      meet(*hector, *sylvester, std::cout); // chase
      std::cout << "\n";

      std::cout << "sylvester meets hector: ";
      meet(*sylvester, *hector, std::cout); // run
      std::cout << "\n";

      std::cout << "hector meets snoopy: ";
      meet(*hector, *snoopy, std::cout); // wag tail
      std::cout << "\n";

      std::cout << "hector meets flipper: ";
      meet(*hector, *flipper, std::cout); // ignore
      std::cout << "\n";

      return 0;
  }
