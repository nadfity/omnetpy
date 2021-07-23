#include <pybind11/pybind11.h>

#include <omnetpp.h>
#include <omnetpp/clifecyclelistener.h>

class PycISimulationLifecycleListener : public omnetpp::cISimulationLifecycleListener {
public:
    /* Constructor */
    using omnetpp::cISimulationLifecycleListener::cISimulationLifecycleListener;

    void lifecycleEvent(omnetpp::SimulationLifecycleEventType eventType, omnetpp::cObject *details) override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cISimulationLifecycleListener,
            lifecycleEvent,
            eventType,
            details
        );
    }

    void listenerAdded() override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cISimulationLifecycleListener,
            listenerAdded
        );
    }

    void listenerRemoved() override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cISimulationLifecycleListener,
            listenerRemoved
        );
    }
};


void bind_cISimulationLifecycleListener(pybind11::module &m)
{
    pybind11::enum_<omnetpp::SimulationLifecycleEventType>(m, "SimulationLifecycleEventType")
        .value("LF_ON_STARTUP", omnetpp::SimulationLifecycleEventType::LF_ON_STARTUP)
        .value("LF_PRE_NETWORK_SETUP", omnetpp::SimulationLifecycleEventType::LF_PRE_NETWORK_SETUP)
        .value("LF_POST_NETWORK_SETUP", omnetpp::SimulationLifecycleEventType::LF_POST_NETWORK_SETUP)
        .value("LF_PRE_NETWORK_INITIALIZE", omnetpp::SimulationLifecycleEventType::LF_PRE_NETWORK_INITIALIZE)
        .value("LF_POST_NETWORK_INITIALIZE", omnetpp::SimulationLifecycleEventType::LF_POST_NETWORK_INITIALIZE)
        .value("LF_ON_SIMULATION_START", omnetpp::SimulationLifecycleEventType::LF_ON_SIMULATION_START)
        .value("LF_ON_SIMULATION_PAUSE", omnetpp::SimulationLifecycleEventType::LF_ON_SIMULATION_PAUSE)
        .value("LF_ON_SIMULATION_RESUME", omnetpp::SimulationLifecycleEventType::LF_ON_SIMULATION_RESUME)
        .value("LF_ON_SIMULATION_SUCCESS", omnetpp::SimulationLifecycleEventType::LF_ON_SIMULATION_SUCCESS)
        .value("LF_ON_SIMULATION_ERROR", omnetpp::SimulationLifecycleEventType::LF_ON_SIMULATION_ERROR)
        .value("LF_PRE_NETWORK_FINISH", omnetpp::SimulationLifecycleEventType::LF_PRE_NETWORK_FINISH)
        .value("LF_POST_NETWORK_FINISH", omnetpp::SimulationLifecycleEventType::LF_POST_NETWORK_FINISH)
        .value("LF_ON_RUN_END", omnetpp::SimulationLifecycleEventType::LF_ON_RUN_END)
        .value("LF_PRE_NETWORK_DELETE", omnetpp::SimulationLifecycleEventType::LF_PRE_NETWORK_DELETE)
        .value("LF_POST_NETWORK_DELETE", omnetpp::SimulationLifecycleEventType::LF_POST_NETWORK_DELETE)
        .value("LF_ON_SHUTDOWN ", omnetpp::SimulationLifecycleEventType::LF_ON_SHUTDOWN )
        .export_values();

    // must use pybind11::nodelete since the destructor of cPar is private
    pybind11::class_<omnetpp::cISimulationLifecycleListener, PycISimulationLifecycleListener> py_cISimulationLifecycleListener(
        m,
        "_cISimulationLifecycleListener",
        R"docstring(
        A callback interface for receiving notifications at various stages
        simulations, including setting up, running, and tearing down..

        Listeners can be added to cEnvir with its addLifecycleListener() method,
        and removed with removeLifecycleListener().

        Simulation lifecycle listeners are mainly intended for use by plug-in
        classes that extend the simulator's functionality: schedulers, output
        vector/scalar managers, parallel simulation algorithms and so on. The
        lifecycle of a such plug-in class is managed by \opp, so one can use
        their constructor to add the listener to cEnvir, and the destructor
        to remove it. (The latter is done automatically.)

        Notifications always refer to the active simulation (see
        cSimulation::getActiveSimulation()).

        For standalone listeners that have no other way to be invoked, one can
        use the <tt>EXECUTE_ON_STARTUP(code)</tt> macro to automatically add a
        listener when the program starts:

        <pre>
        EXECUTE_ON_STARTUP(getEnvir()->addLifecycleListener(new MyListener()));
        </pre>

        Note that listeners will not be deleted automatically when the program
        exits. To delete a listener on shutdown, add <tt>delete this;</tt>
        into the listenerRemoved() method.
        )docstring"
    );


    py_cISimulationLifecycleListener
    .def(pybind11::init<>());


    py_cISimulationLifecycleListener.def(
        "lifecycleEvent",
        &omnetpp::cISimulationLifecycleListener::lifecycleEvent,
        R"docstring(
        The main listener method, called on simulation lifecycle events.

        Override this method to invoke code on event.
        )docstring"
    );

    py_cISimulationLifecycleListener.def(
        "listenerAdded",
        &omnetpp::cISimulationLifecycleListener::listenerAdded,
        R"docstring(
        Fired after this listener was added to cEnvir, via addLifecycleListener().

        Override this method to invoke code on event.
        )docstring"
    );

    py_cISimulationLifecycleListener.def(
        "listenerRemoved",
        &omnetpp::cISimulationLifecycleListener::listenerRemoved,
        R"docstring(
        Fired after this listener was removed from cEnvir, via removeLifecycleListener().
        It is OK for the listener to delete itself in the body of this method
        (<tt>delete this</tt>).

        Override this method to invoke code on event.
        )docstring"
    );

}
