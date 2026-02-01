//
// Created by chris on 01.03.25.

#ifndef TESTTYPES_HPP
#define TESTTYPES_HPP

#include <cassert>
#include <cstdio>
#include <source_location>

inline void print_function_name(const std::source_location source_loc = {})
{
	std::puts(source_loc.function_name());
}

/**
 * Type which always prints any called special member function
 */
struct Noisy
{
	Noisy() { print_function_name(); }
	Noisy(const Noisy&) { print_function_name(); }
	Noisy(Noisy&&) noexcept { print_function_name(); }
	Noisy& operator=(const Noisy&)
	{
		print_function_name();
		return *this;
	}
	Noisy& operator=(Noisy&&) noexcept
	{
		print_function_name();
		return *this;
	}
	~Noisy() { print_function_name(); }
};

struct Counter
{
	static inline std::size_t constructions{};
	static inline std::size_t default_constructions{};
	static inline std::size_t copy_constructions{};
	static inline std::size_t copy_assignments{};
	static inline std::size_t copies{};
	static inline std::size_t move_constructions{};
	static inline std::size_t move_assignments{};
	static inline std::size_t moves{};
	static inline std::size_t destructions{};

	Counter()
	{
		++constructions;
		++default_constructions;
	}
	Counter(const Counter&)
	{
		++constructions;
		++copies;
		++copy_constructions;
	}
	Counter& operator=(const Counter&)
	{
		++copies;
		++copy_assignments;
		return *this;
	}

	Counter(Counter&&) noexcept
	{
		++constructions;
		++moves;
		++move_constructions;
	}
	Counter& operator=(Counter&&) noexcept
	{
		++moves;
		++move_assignments;
		return *this;
	}
	~Counter() { ++destructions; }
};

struct MoveOnly
{
	MoveOnly() = default;

	MoveOnly(const MoveOnly&)			 = delete;
	MoveOnly& operator=(const MoveOnly&) = delete;

	MoveOnly(MoveOnly&&) noexcept			 = default;
	MoveOnly& operator=(MoveOnly&&) noexcept = default;

	~MoveOnly() = default;
};

struct CopyOnly
{
	CopyOnly() = default;

	CopyOnly(const CopyOnly&)			 = default;
	CopyOnly& operator=(const CopyOnly&) = default;

	CopyOnly(CopyOnly&&) noexcept			 = delete;
	CopyOnly& operator=(CopyOnly&&) noexcept = delete;

	~CopyOnly() = default;
};

/**
 * A type that can be neither copied nor moved
 */
struct Fixed
{
	Fixed() = default;

	Fixed(const Fixed&)			   = delete;
	Fixed& operator=(const Fixed&) = delete;

	Fixed(Fixed&&) noexcept			   = delete;
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
	SelfPointing()
		: self(this)
	{
	}
	SelfPointing(const SelfPointing&)
		: SelfPointing()
	{
	}
	SelfPointing& operator=(const SelfPointing& other)
	{
		if (&other == this)
		{
		}
		self = this;
		return *this;
	}

	SelfPointing(SelfPointing&&) noexcept
		: SelfPointing()
	{
	}
	SelfPointing& operator=(SelfPointing&& other) noexcept
	{
		if (&other == this)
		{
		}
		self = this;
		return *this;
	}

	~SelfPointing() { assert(this == self); }
};

/**
 *
 * @tparam Alignment alignment of the type
 * This type has special alignment requirements and checks if they are maintained over the
 * lifetime of the types objects
 */
template <std::size_t Alignment>
struct alignas(Alignment) Aligned
{
	Aligned() { assert(reinterpret_cast<std::uintptr_t>(this) % Alignment == 0); }

	Aligned(const Aligned&)			   = default;
	Aligned& operator=(const Aligned&) = default;

	Aligned(Aligned&&) noexcept			   = default;
	Aligned& operator=(Aligned&&) noexcept = default;

	~Aligned() { assert(reinterpret_cast<std::uintptr_t>(this) % Alignment == 0); }
};

#endif // TESTTYPES_HPP
