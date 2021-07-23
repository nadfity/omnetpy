#include <pybind11/pybind11.h>

#include <omnetpp.h>
#include <omnetpp/cenvir.h>

class PycEnvir : public omnetpp::cEnvir {
public:
    /* Constructor */
    using omnetpp::cEnvir::cEnvir;

    void addLifecycleListener(omnetpp::cISimulationLifecycleListener *listener) override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cEnvir,
            addLifecycleListener,
            listener
        );
    }

    void removeLifecycleListener(omnetpp::cISimulationLifecycleListener *listener) override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cEnvir,
            removeLifecycleListener,
            listener
        );
    }

    void notifyLifecycleListeners(omnetpp::SimulationLifecycleEventType eventType, omnetpp::cObject *details=nullptr) override {
        PYBIND11_OVERLOAD_PURE(
            void,
            omnetpp::cEnvir,
            notifyLifecycleListeners,
            eventType,
            details
        );
    }
};


void bind_cEnvir(pybind11::module &m)
{
    // private destructor
    pybind11::class_<
        omnetpp::cEnvir,
        PycEnvir,
        std::unique_ptr<omnetpp::cEnvir, pybind11::nodelete>
    > py_cEnvir(
        m,
        "cEnvir",
        R"docstring(
        cEnvir represents the "environment" or user interface of the simulation.

        The active cEnvir object can be accessed via cSimulation::getActiveEnvir()
        or the getEnvir() global function.

        Methods useful for simulation models include isGUI() and isExpressMode().
        Most other cEnvir methods are used in the communication between
        the simulation kernel and the environment.

        The default implementation of cEnvir can be extended by subclassing
        the classes declared in the envirext.h header (e.g. cConfiguration,
        cRNG, cIOutputVectorManager, cIOutputScalarManager), and selecting the
        new classes in <tt>omnetpp.ini</tt>.
        )docstring"
    );

    py_cEnvir.def(
        "addLifecycleListener",
        &omnetpp::cEnvir::addLifecycleListener,
        R"docstring(
        Add event listener.
        )docstring"
    );

    py_cEnvir.def(
        "removeLifecycleListener",
        &omnetpp::cEnvir::removeLifecycleListener,
        R"docstring(
        Remove event listener.
        )docstring"
    );

    py_cEnvir.def(
        "notifyLifecycleListeners",
        &omnetpp::cEnvir::notifyLifecycleListeners,
        R"docstring(
        Call event listener.
        )docstring"
    );
}
