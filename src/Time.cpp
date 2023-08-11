#pragma once

#include "Time.hpp"

float Time::s_delta = 0;

TimeUntil::TimeUntil( float time ) : m_tick( Time::Ticks() + uint32_t( time * 1000.f ) )
{
}

void TimeUntil::operator=( float time )
{
	m_tick = Time::Ticks() + uint32_t( time * 1000.f );
}

void TimeUntil::operator+=( float time )
{
	m_tick += uint32_t( time * 1000.f );
}

TimeUntil::operator bool() const
{
	return Time::Ticks() > m_tick;
}