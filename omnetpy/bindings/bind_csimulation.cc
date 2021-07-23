#include <pybind11/pybind11.h>

#include <omnetpp.h>
#include <omnetpp/csimulation.h>

void bind_cSimulation(pybind11::module &m)
{
    pybind11::class_<
        omnetpp::cSimulation
        > py_cSimulation(
        m,
        "_cSimulation",
        R"docstring(
        Simulation manager class.

        cSimulation is the central class in \opp. It stores the active simulation
        model, and provides methods for setting up, running and finalizing simulations.

        Most cSimulation methods are not of interest for simulation model code,
        they are used internally (e.g. by the user interface libraries (Envir,
        Cmdenv, Tkenv) to set up and run simulations).

        Some methods which can be of interest when programming simple modules:
        getUniqueNumber(), getModuleByPath(), getModule(), snapshot().
        )docstring"
    );

    py_cSimulation.def(
        "getSystemModule",
        &omnetpp::cSimulation::getSystemModule,
        R"docstring(
        Get system module.
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "setContext",
        &omnetpp::cSimulation::setContext,
        R"docstring(
        Sets the component (module or channel) in context. Used internally.
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "getContext",
        &omnetpp::cSimulation::setContext,
        R"docstring(
        Returns the component (module or channel) currently in context.
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "getContextModule",
        &omnetpp::cSimulation::getContextModule,
        R"docstring(
        If the current context is a module, returns its pointer, otherwise returns nullptr.
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "getContextSimpleModule",
        &omnetpp::cSimulation::getContextSimpleModule,
        R"docstring(
        Returns the module currently in context as a simple module. If the module in context is not a simple module, returns nullptr. This is a convenience function which simply calls getContextModule().         )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "getModule",
        &omnetpp::cSimulation::getModule,
        R"docstring(
        Looks up a module by ID. If the ID does not identify a module (e.g. invalid ID,
        module already deleted, or object is not a module), it returns nullptr.
        )docstring",
        pybind11::return_value_policy::reference,
        pybind11::arg("id")
    );

    py_cSimulation.def(
        "getSimTime",
        &omnetpp::cSimulation::getSimTime,
        R"docstring(
        Returns the current simulation time. (It is also available via the global simTime() function.) Between events it returns the time of the last executed event.

        Referenced by cMessage::setTimestamp(), and omnetpp::simTime().
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "registerComponent",
        &omnetpp::cSimulation::registerComponent,
        R"docstring(
        Register component instance that created using `pyopp.createScheduleInit()`
        or other means.
        )docstring",
        pybind11::return_value_policy::reference
    );

    py_cSimulation.def(
        "getEnvir",
        &omnetpp::cSimulation::getEnvir,
        R"docstring(
        Returns the environment object associated with this simulation object.
        )docstring",
        pybind11::return_value_policy::reference
    );
}
