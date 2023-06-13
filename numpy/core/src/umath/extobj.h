#ifndef _NPY_PRIVATE__EXTOBJ_H_
#define _NPY_PRIVATE__EXTOBJ_H_

#include <numpy/ndarraytypes.h>  /* for NPY_NO_EXPORT */


/*
 * Represent the current ufunc error (and buffer) state.  we are using a
 * capsule for now to store this, but it could make sense to refactor it into
 * a proper (immutable) object.
 * NOTE: Part of this information should be integrated into the public API
 *       probably.  We expect extending it e.g. with a "fast" flag.
 *       (although the public only needs to know *if* errors are checked, not
 *       what we do with them, like warn, raise, ...).
 */
typedef struct {
    int errmask;
    npy_intp bufsize;
    PyObject *pyfunc;
} npy_extobj;


static inline void
npy_extobj_clear(npy_extobj *extobj)
{
    Py_XDECREF(extobj->pyfunc);
}

NPY_NO_EXPORT int
_check_ufunc_fperr(int errmask, const char *ufunc_name);

NPY_NO_EXPORT int
_get_bufsize_errmask(const char *ufunc_name, int *buffersize, int *errormask);


/*
 * Private Python exposure of the extobj.
 */
NPY_NO_EXPORT PyObject *
extobj_seterrobj(PyObject *NPY_UNUSED(mod),
        PyObject *const *args, Py_ssize_t len_args, PyObject *kwnames);

NPY_NO_EXPORT PyObject *
extobj_geterrobj(PyObject *NPY_UNUSED(mod), PyObject *NPY_UNUSED(noarg));


#endif
