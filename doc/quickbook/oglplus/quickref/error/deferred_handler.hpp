/*
 *  Copyright 2014-2019 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

//[oglplus_error_DeferredHandler

class DeferredHandler {
public:
    DeferredHandler(DeferredHandler&&);

    ~DeferredHandler(); /*<
    Invokes the error handler (which usually throws an exception)
    unless the handler already has been triggered or it was cancelled.
    >*/

    void trigger(); /*<
    If [^this] instance wraps an error handler, it is invoked
    >*/
    bool cancel()   /*<
      If [^this] instance wraps an error handler, this function
      cancels its invocation and returns [^true], otherwise returns [^false].
      >*/
      noexcept;

    explicit operator bool() const /*<
            Returns true if [^this] instance wraps an error handler.
            >*/
      noexcept;

    bool operator!() const /*<
  Returns true if [^this] instance does not wrap an error handler.
  >*/
      noexcept;
};

//]
