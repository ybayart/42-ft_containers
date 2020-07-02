#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"

namespace ft
{
	template
	<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<pair<const Key, T> >
	>
	class map
	{
		public:
			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const Key, T>							value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			
			class value_compare
			: public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c)
					: comp(c)
					{}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			typedef _bin_tree<Key, T, value_type, Compare, Alloc>	_tree_type;

			_tree_type	_M_t;

		public:
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename _tree_type::iterator				iterator;
			typedef typename _tree_type::const_iterator			const_iterator;
			typedef typename _tree_type::reverse_iterator		reverse_iterator;
			typedef typename _tree_type::reverse_iterator		const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type())
			: _M_t(comp, alloc)
			{}
	
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: _M_t(comp, alloc)
			{
				_M_t._M_insert_unique(first, last);
			}

			map (const map& x)
			: _M_t(x._M_t)
			{}

			~map (void)
			{}

			map& operator=	(const map& x)
			{
				_M_t = x._M_t;
				return (*this);
			}

			iterator begin (void)
			{
				return (_M_t.begin());
			}
			const_iterator begin (void) const
			{
				return (_M_t.begin());
			}

			iterator end (void)
			{
				return (_M_t.end());
			}
			const_iterator end (void) const
			{
				return (_M_t.end());
			}

			reverse_iterator rbegin (void)
			{
				return (_M_t.rbegin());
			}
			const_reverse_iterator rbegin (void) const
			{
				return (_M_t.rbegin());
			}

			reverse_iterator rend (void)
			{
				return (_M_t.rend());
			}
			const_reverse_iterator rend (void) const
			{
				return (_M_t.rend());
			}

			bool empty (void) const
			{
				return (_M_t.empty());
			}

			size_type size (void) const
			{
				return (_M_t.size());
			}

			size_type max_size (void) const
			{
				return (_M_t.max_size());
			}

			mapped_type& operator[]	(const key_type& k)
			{
				iterator	it = lower_bound(k);
				if (it == end() || key_comp()(k, (*it).first))
					it = insert(it, value_type(k, mapped_type()));
				return ((*it).second);
			}

			pair<iterator,bool> insert (const value_type& val)
			{
				return (_M_t._M_insert_unique(val));
			}
			iterator insert (iterator position, const value_type& val)
			{
				return (_M_t._M_insert_unique_(position, val));
			}
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				_M_t._M_insert_unique(first, last);
			}

			void erase (iterator position)
			{
				return (_M_t.erase(position));
			}
			size_type erase (const key_type& k)
			{
				return (_M_t.erase(k));
			}
			void erase (iterator first, iterator last)
			{
				return (_M_t.erase(first, last));
			}

			void swap (map& x)
			{
				_M_t.swap(x._M_t);
			}

			void clear (void)
			{
				_M_t.clear();
			}

			key_compare key_comp (void) const
			{
				return (_M_t.key_comp());
			}

			value_compare value_comp (void) const
			{
				return (value_compare(_M_t.key_comp()));
			}

			iterator find (const key_type& k)
			{
				return (_M_t.find(k));
			}
			const_iterator find (const key_type& k) const
			{
				return (_M_t.find(k));
			}

			size_type count (const key_type& k) const
			{
				return (_M_t.find(k) == _M_t.end() ? 0 : 1);
			}

			iterator lower_bound (const key_type& k)
			{
				return (_M_t.lower_bound(k));
			}
			const_iterator lower_bound (const key_type& k) const
			{
				return (_M_t.lower_bound(k));
			}

			iterator upper_bound (const key_type& k)
			{
				return (_M_t.upper_bound(k));
			}
			const_iterator upper_bound (const key_type& k) const
			{
				return (_M_t.upper_bound(k));
			}

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (_M_t.equal_range(k));
			}
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (_M_t.equal_range(k));
			}
	};

}

#endif
