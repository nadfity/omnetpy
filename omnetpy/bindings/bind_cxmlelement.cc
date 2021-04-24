#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // needed as some functions take vector as arguments


#include <omnetpp.h>

void bind_cXMLElement(pybind11::module &m)
{
    pybind11::class_<
        omnetpp::cXMLElement,
        omnetpp::cObject
    > py_cXMLElement(
        m,
        "_cXMLElement",
        R"docstring(
        Represents an XML element in an XML configuration file.

        XML-typed NED parameters are accessible as cXMLElement via the cPar::xmlValue() method.

        cXMLElement provides readonly access to XML documents via a DOM-like API.
        (A full-featured DOM implementation would have been too bloated for the purpose of accessing readonly configuration files).

        Features: readonly access (getter methods) only; represents only elements, attributes and text content (i.e. entities, processing instructions, comments are ignored); attributes are presented as part of an element node (not as separate attribute nodes as in DOM); mixed content model is not supported (element body cannot mix text with further elements); text is represented as a property of its enclosing element (and not as separate node as in DOM); CDATA sections are also represented as text (with the above restrictions); strings are presented in UTF-8 format (which is normal ASCII string if only characters 0x01-0x7F are used; encoding of the XML file itself may use arbitrary encoding provided it's supported by the underlying XML parser); no namespace support.

        @ingroup SimulationSupport
        )docstring"
    );

    py_cXMLElement.def(
        "getXML",
        &omnetpp::cXMLElement::getXML,
        R"docstring(
        Returns the string of XML file.
        )docstring"
    );

    py_cXMLElement.def(
        "getSourceFileName",
        &omnetpp::cXMLElement::getSourceFileName,
        R"docstring(
        Returns the XML file path.
        )docstring"
    );

}
