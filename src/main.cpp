#include <iostream>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/event.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sc = boost::statechart;

struct EvCount : sc::event<EvCount> {};

struct Active;

struct Counter : sc::state_machine< Counter, Active > {};

struct notFive;
struct isFive;

struct Active : sc::simple_state< Active, Counter, notFive > {
    public:
        Active(): value(0) { std::cout << "Enters active\n"; };
        ~Active() { std::cout << "exit Active\n"; }

        int getValue() const { return value; }
        int &getValue() { return value; }
    private:
        int value;
};

struct notFive: sc::simple_state<notFive, Active> {
    public:
        typedef sc::custom_reaction< EvCount > reactions;
        notFive() { std::cout << "I'm not five!\n"; }
        ~notFive() { context< Active >().getValue() += 1; }

        sc::result react( const EvCount& ) { 
            if(context< Active >().getValue() == 5)
                return transit< isFive >(); 
            else 
                return transit< notFive >();
        }
};

struct isFive: sc::simple_state< isFive, Active > {
    public:
        typedef sc::custom_reaction< EvCount > reactions;
        isFive() { std::cout << "I'm five :)\n"; }
        ~isFive() {  }

        sc::result react( const EvCount& ) { return transit< isFive >(); }
};



int main() {

    Counter machine;
    machine.initiate();
    machine.process_event( EvCount() );
    machine.process_event( EvCount() );
    machine.process_event( EvCount() );
    machine.process_event( EvCount() );
    machine.process_event( EvCount() );
    machine.process_event( EvCount() );
    return 0;
}
