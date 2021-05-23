"""Bindings related to cSimpleModule."""
import weakref

from . import _pybind
from ._refstore import _RefStore
from ._utils import no_binding_for_method

class cSimpleModule(_pybind._cSimpleModule):

    def getModuleByPath(self, path):
        return _pybind._cSimpleModule.getModuleByPath(self, path)

    @classmethod
    def cast(cls, to_be_casted_obj):
        """
        Cast an object into this class.

        Be careful to use this, because it may not work or crash as segfault
        (if the underlying class is C++). Call this from the target class.

        .. codeblock

           class TargetClass(Parent):
               pass

           instance = TargetClass.cast(object)
        """
        casted_obj = cls()
        casted_obj.__dict__ = to_be_casted_obj.__dict__
        return casted_obj

    @no_binding_for_method
    def scheduleStart(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def halt(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def getStackSize(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def getStacUsage(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def hasStackOverflow(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def error(self, *args, **kwargs):
        pass

    @no_binding_for_method
    def scheduleStart(self, *args, **kwargs):
        pass

    def delete(self, thing):
        """Remove extra python reference to msg."""
        _RefStore.delete(thing)  # removes reference from cMessage static set
        try:
            thing.deleteModule()
        except AttributeError:
            pass

    def cancelAndDelete(self, msg):
        """
        Invokes cancelEvent() on the message (in case it is scheduled), then
        deletes it. nullptr is also accepted, then the method does nothing.
        This method is especially useful in simple module destructors, to dispose
        of self-messages that the module has allocated.
        """
        if msg:
            self.cancelEvent(msg)
            self.delete(msg)

    def __del__(self):
        print('__del__', self.getFullPath())


cSimpleModule.__doc__ = _pybind._cSimpleModule.__doc__
