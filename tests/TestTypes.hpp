//
// Created by chris on 01.03.25.

#ifndef TESTTYPES_HPP
#define TESTTYPES_HPP

#include <cstdio>
#include <cassert>

#define PRINT_FUNCTION() std::puts(__PRETTY_FUNCTION__);

/**
 *
 * @tparam T Type to be printed
 * Outputs [T = typename]
 */
template<class T>
void print_type()
{
	std::puts(__PRETTY_FUNCTION__+18);
}

/**
 * Type which always prints any called special member function
 */
struct Noisy
{
	Noisy()
	{
		PRINT_FUNCTION();
	}
	Noisy(const Noisy&)
	{
		PRINT_FUNCTION();
	}
	Noisy(Noisy&&) noexcept
	{
		PRINT_FUNCTION();
	}
	Noisy& operator=(const Noisy&)
	{
		PRINT_FUNCTION();
		return *this;
	}
	Noisy& operator=(Noisy&&) noexcept
	{
		PRINT_FUNCTION();
		return *this;
	}
	~Noisy()
	{
		PRINT_FUNCTION();
	}
};

namespace detail
{
	template<auto = []{}>
	struct Counter
	{
		static inline std::size_t Constructions{};
		static inline std::size_t DefaultConstructions{};
		static inline std::size_t CopyConstructions{};
		static inline std::size_t CopyAssignments{};
		static inline std::size_t Copies{};
		static inline std::size_t MoveConstructions{};
		static inline std::size_t MoveAssignments{};
		static inline std::size_t Moves{};
		static inline std::size_t Destructions{};

		Counter()
		{
			++Constructions;
			++DefaultConstructions;
		}
		Counter(const Counter&)
		{
			++Constructions;
			++Copies;
			++CopyConstructions;
		}
		Counter& operator=(const Counter&)
		{
			++Copies;
			++CopyAssignments;
			return *this;
		}

		Counter(Counter&&) noexcept
		{
			++Constructions;
			++Moves;
			++MoveConstructions;
		}
		Counter& operator=(Counter&&) noexcept
		{
			++Moves;
			++MoveAssignments;
			return *this;
		}
		~Counter()
		{
			++Destructions;
		}
	};
} // namespace detail

	/**
	 *
	 * @param name
	 * Creates a unique counter type which doesn't share any state with other counter types
	 */
#define MAKE_UNIQUE_COUNTER_TYPE(name) using name = detail::Counter;



struct MoveOnly
{
	MoveOnly() = default;

	MoveOnly(const MoveOnly&) = delete;
	MoveOnly& operator=(const MoveOnly&) = delete;

	MoveOnly(MoveOnly&&) noexcept = default;
	MoveOnly& operator=(MoveOnly&&) noexcept = default;

	~MoveOnly() = default;
};

struct CopyOnly
{
	CopyOnly() = default;

	CopyOnly(const CopyOnly&) = default;
	CopyOnly& operator=(const CopyOnly&) = default;

	CopyOnly(CopyOnly&&) noexcept = delete;
	CopyOnly& operator=(CopyOnly&&) noexcept = delete;

	~CopyOnly() = default;
};

/**
 * A type that can be neither copied nor moved
 */
struct Fixed
{
	Fixed() = default;

	Fixed(const Fixed&) = delete;
	Fixed& operator=(const Fixed&) = delete;

	Fixed(Fixed&&) noexcept = delete;
	Fixed& operator=(Fixed&&) noexcept = delete;

	~Fixed() = default;
};

/**
 * A type that checks if the invariant of always pointing to itself is maintained.
 * This is useful to make sure that raw memory isn't copied without calling the appropriate special member functions
 */
struct SelfPointing
{
	SelfPointing* self;
	SelfPointing() : self(this) {}
	SelfPointing(const SelfPointing&) : SelfPointing()
	{}
	SelfPointing& operator=(const SelfPointing& other)
	{
		if (&other == this) {}
		return *this;
	}

	SelfPointing(SelfPointing&&) noexcept : SelfPointing() {}
	SelfPointing& operator=(SelfPointing&& other) noexcept
	{
		if (&other == this) {}
		return *this;
	}

	~SelfPointing()
	{
		assert(this == self);
	}
};


/**
 *
 * @tparam Alignment alignment of the type
 * This type has special alignment requirements and checks if they are maintained over the
 * lifetime of the types objects
 */
template<std::size_t Alignment>
struct alignas(Alignment) Aligned
{
	Aligned()
	{
		assert(reinterpret_cast<std::uintptr_t>(this) % Alignment == 0);
	}

	Aligned(const Aligned&) = default;
	Aligned& operator=(const Aligned&) = default;

	Aligned(Aligned&&) noexcept = default;
	Aligned& operator=(Aligned&&) noexcept = default;

	~Aligned()
	{
		assert(reinterpret_cast<std::uintptr_t>(this) % Alignment == 0);
	}
};

#endif //TESTTYPES_HPP
