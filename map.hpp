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
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			// typedef x										iterator;
			// typedef const_x									const_iterator;
			// typedef ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef ft::reverse_iterator<const_iterator>		iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
			
			explicit map (const key_compare& comp = key_compare(),
						const allocator_type& alloc = allocator_type());
			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
			map (const map& x);

			~map (void);

			map& operator=	(const map& x);

			iterator begin (void);
			const_iterator begin (void) const;

			iterator end (void);
			const_iterator end (void) const;

			reverse_iterator rbegin (void);
			const_reverse_iterator rbegin (void) const;

			reverse_iterator rend (void);
			const_reverse_iterator rend (void) const;

			bool empty (void) const;

			size_type size (void) const;

			size_type max_size (void) const;

			mapped_type& operator[]	(const key_type& k);

			pair<iterator,bool> insert (const value_type& val);
			iterator insert (iterator position, const value_type& val);
			template <class InputIterator>
				void insert (InputIterator first, InputIterator last);

			void erase (iterator position);
			size_type erase (const key_type& k);
			void erase (iterator first, iterator last);

			void swap (map& x);

			void clear (void);

			key_compare key_comp (void) const;

			value_compare value_comp (void) const;

			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;

			size_type count (const key_type& k) const;

			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;

			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;

			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			pair<iterator,iterator> equal_range (const key_type& k);
	}
}
