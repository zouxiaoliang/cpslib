import psutil
from pycpslib import lib as P 
from pycpslib import ffi

def test_virtual_memory(almost_equal):
    pslib_vmem = ffi.new("VmemInfo *")
    P.virtual_memory(pslib_vmem)
    psutil_vmem = psutil.virtual_memory()

    assert almost_equal(pslib_vmem.total, psutil_vmem.total)
    assert almost_equal(pslib_vmem.available, psutil_vmem.available)
    assert almost_equal(pslib_vmem.used, psutil_vmem.used)
    assert almost_equal(pslib_vmem.free, psutil_vmem.free)
    assert almost_equal(pslib_vmem.active, psutil_vmem.active)
    assert almost_equal(pslib_vmem.inactive, psutil_vmem.inactive)
    assert almost_equal(pslib_vmem.buffers, psutil_vmem.buffers)
    assert almost_equal(pslib_vmem.cached, psutil_vmem.cached)
    assert almost_equal(pslib_vmem.percent, psutil_vmem.percent)