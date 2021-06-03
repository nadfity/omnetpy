#include <pybind11/pybind11.h>

#include <omnetpp.h>
#include <omnetpp/ccontextswitcher.h>

void bind_cContextSwitcher(pybind11::module &m)
{
    pybind11::class_<
        omnetpp::cContextSwitcher
    > py_cContextSwitcher(
        m,
        "_cContextSwitcher",
        R"docstring(
        The constructor switches the context to the given component, and the destructor restores the original context.
        )docstring"
    );

    pybind11::class_<
        omnetpp::cMethodCallContextSwitcher,
        omnetpp::cContextSwitcher
    > py_cMethodCallContextSwitcher(
        m,
        "_cMethodCallContextSwitcher",
        R"docstring(
        The constructor switches the context to the given component, and the destructor restores the original context.
        )docstring"
    );

    py_cMethodCallContextSwitcher.def(
        pybind11::init<omnetpp::cComponent *>(),
        R"docstring(
        Switches context to the given module
        )docstring"
    );

    py_cMethodCallContextSwitcher.def(
        "methodCall",
        [](omnetpp::cMethodCallContextSwitcher &self, const char *methodFmt) {
            return self.methodCall(methodFmt);
        },
        // &omnetpp::cMethodCallContextSwitcher::methodCall,
        R"docstring(
        Various ways to tell the user interface about the method call so that the call can be animated, recorded into the event log, etc.
        )docstring"
    );
}
