#include "pch.h"
#include "PixelValues.h"

struct PixelValues::Impl
{

};

PixelValues::PixelValues()
	: m(std::make_unique<Impl>())
{
}


PixelValues::~PixelValues() = default;

short PixelValues::GetValue() const
{
	return 123;
}
