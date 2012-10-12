//
//  SharedPtrEx.hpp
//  Phere Shared Ptr
//
//  Created by Rowan James on 12/10/12.
//  Copyright 2012 Rowan James. All rights reserved.
//

#ifndef PHERE_SMART_PTR_SHARED_PTR_HPP
#define PHERE_SMART_PTR_SHARED_PTR_HPP

#include <exception>
#include <boost/exception/exception.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace phere
{
	struct AnyNullPointerException
	: public virtual ::std::exception
	, public virtual ::boost::exception
	{};
	template <typename T>
	struct NullPointerException
	: virtual public ::phere::AnyNullPointerException
	{};
	
	template <typename T>
	class shared_ptr
	{
	public:
		typedef ::phere::shared_ptr<T> this_type;
		typedef ::phere::shared_ptr<const T> this_type_const;
		typedef boost::shared_ptr<T> boost_ptr_t;
		typedef boost::shared_ptr<const T> boost_const_ptr_t;
		typedef boost::weak_ptr<T> boost_weak_ptr_t;
		
		
		// deliberately no constructor from T*, use make_shared<T>
		shared_ptr(boost_ptr_t _ptr = boost_ptr_t())
		: m_ptr(_ptr)
		{}

		~shared_ptr();
		
		// "regular" accossors
		T* operator->() const
		{
			return getBoostPtrOrThrow().get();
		}
		T& operator*() const
		{
			return *getBoostPtrOrThrow();
		}

		operator bool() const
		{ return m_ptr; }
		
		// freely convertable to a boost shared_ptr
		operator boost_ptr_t() const
		{ return m_ptr; }
		// or a weak ptr
		operator boost_weak_ptr_t() const
		{ return m_ptr; }
		// or a shared_ptr<const T>
		operator this_type_const() const
		{
			boost_const_ptr_t ptr(getBoostPtrOrThrow());
			return ptr;
		}
		
		template <typename U>
		::phere::shared_ptr<U> dynamic_pointer_cast()
		{
			::phere::shared_ptr<U> result(boost::dynamic_pointer_cast<U>(m_ptr));
			return result;
		}
		
		std::size_t hash_value() const
		{
			return boost::hash<T const *>()(m_ptr.get());
		}
		
		template <typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & m_ptr;
		}
		
		bool pointsTo(T const& obj) const
		{
			boost_ptr_t ptr(m_ptr);
			if (!ptr)
			{
				return false;
			}
			return ptr.get() == &obj;
		}
		bool pointsToSameObject(this_type rhs /* pass by copy */) const
		{
			return m_ptr.get() == rhs.m_ptr.get();
		}
		
		
		// mutators
		void reset(this_type rhs = this_type())
		{
			*this = rhs;
		}
		
		this_type& operator=(this_type const& rhs)
		{
			m_ptr = rhs.m_ptr;
			return *this;
		}
		template <typename U>
		this_type& operator=(boost::shared_ptr<U> rhs)
		{
			m_ptr = rhs;
			return *this;
		}
		
	private:
		boost_ptr_t getBoostPtrOrThrow() const
		{
			boost_ptr_t result(m_ptr);
			if (!result)
			{
				BOOST_THROW_EXCEPTION(::phere::NullPointerException<T>());
				return result;
			}
		}
		boost_ptr_t m_ptr;
	};
	
	template< class T > std::size_t hash_value( ::phere::shared_ptr<T> const & p )
	{
		return p.hash_value();
	}
}
#endif
