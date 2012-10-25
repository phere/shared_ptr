phere.shared_ptr
================

A C++ smart pointer based on [boost::shared_ptr](http://www.boost.org/doc/libs/release/libs/smart_ptr/shared_ptr.htm), with some changes for better build-time and runtime checking.

No construction or assignment from raw pointers
----------------------------------------------

The only valid way to initialise a `phere::shared_ptr<T>` is with `boost::make_shared<T>()` or a similar mechanism that returns an already-managed pointer.

This pattern prevents the class of runtime bugs that results when a `shared_ptr A` is constructed with a pointer obtained from an already-reference-counted or otherwise unmanaged object; resulting in a premature `delete` and subsequent likely access to garbage memory.  Not fun to track down.


Exception on dereference or indirection through empty shared_ptr
----------------------------------------------------------------

[libc++](http://libcxx.llvm.org/)'s `std::shared_ptr<T>` has no run-time check for NULL in the dereference or indirection operators.  You access an empty `shared_ptr`, the best you can hope for is a segmentation fault.

`boost::shared_ptr<T> empty; empty->method();` fires a `BOOST_ASSERT(px != NULL)`.  While this is slightly more programmer-friendly than libc++, the behaviour of `BOOST_ASSERT` is nonrecoverable; and worse, overridable.  While the default behaviour will at least trap into the debugger, one large project in particular returns from the `boost_assertion_handler` routine; and thus happily segfaults anyway.

The exception thrown is a `phere::NullPointerException<T>`, which may be caught as a `phere::AnyNullPointerException`, `boost::exception` or `std::exception`.
