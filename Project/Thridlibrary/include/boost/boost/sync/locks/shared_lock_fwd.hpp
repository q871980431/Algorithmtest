/*
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 *
 * (C) Copyright 2007 Anthony Williams
 * (C) Copyright 2011-2012 Vicente J. Botet Escriba
 * (C) Copyright 2013 Andrey Semashev
 */
/*!
 * \file   locks/shared_lock_fwd.hpp
 *
 * \brief  This header declares a shared lock guard.
 */

#ifndef BOOST_SYNC_LOCKS_SHARED_LOCK_FWD_HPP_INCLUDED_
#define BOOST_SYNC_LOCKS_SHARED_LOCK_FWD_HPP_INCLUDED_

#include <boost/sync/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#include <boost/sync/detail/header.hpp>

namespace boost {

namespace sync {

/*!
 * \brief A unique lock scope guard
 */
template< typename Mutex >
class shared_lock;

} // namespace sync

} // namespace boost

#include <boost/sync/detail/footer.hpp>

#endif // BOOST_SYNC_LOCKS_SHARED_LOCK_FWD_HPP_INCLUDED_
