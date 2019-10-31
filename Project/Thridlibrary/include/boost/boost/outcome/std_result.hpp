/* A very simple result type
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (8 commits)
File Created: June 2017


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_STD_RESULT_HPP
#define BOOST_OUTCOME_STD_RESULT_HPP

#include "basic_result.hpp"
#include "detail/trait_std_error_code.hpp"
#include "detail/trait_std_exception.hpp"

#include "policy/fail_to_compile_observers.hpp"
#include "policy/result_error_code_throw_as_system_error.hpp"
#include "policy/result_exception_ptr_rethrow.hpp"
#include "policy/throw_bad_result_access.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

/*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
namespace policy
{
  /*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
  template <class T, class EC, class E>
  using default_policy = std::conditional_t<  //
  std::is_void<EC>::value && std::is_void<E>::value,
  terminate,                                                                                                                     //
  std::conditional_t<                                                                                                            //
  trait::is_error_code_available<EC>::value, error_code_throw_as_system_error<T, EC, E>,                                         //
  std::conditional_t<                                                                                                            //
  trait::is_exception_ptr_available<EC>::value || trait::is_exception_ptr_available<E>::value, exception_ptr_rethrow<T, EC, E>,  //
  fail_to_compile_observers                                                                                                      //
  >>>;
}  // namespace policy

/*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
template <class R, class S = std::error_code, class NoValuePolicy = policy::default_policy<R, S, void>>  //
using std_result = basic_result<R, S, NoValuePolicy>;

/*! AWAITING HUGO JSON CONVERSION TOOL 
type alias template <class R, class S = std::error_code> std_unchecked. Potential doc page: `std_unchecked<T, E = std::error_code>`
*/
template <class R, class S = std::error_code> using std_unchecked = std_result<R, S, policy::all_narrow>;

/*! AWAITING HUGO JSON CONVERSION TOOL 
type alias template <class R, class S = std::error_code> std_checked. Potential doc page: `std_checked<T, E = std::error_code>`
*/
template <class R, class S = std::error_code> using std_checked = std_result<R, S, policy::throw_bad_result_access<S, void>>;

BOOST_OUTCOME_V2_NAMESPACE_END

#endif
