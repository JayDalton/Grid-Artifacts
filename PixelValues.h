#pragma once

class PixelValues
{
public:
	PixelValues();
	~PixelValues();

	short GetValue() const;

private:
	struct Impl;
	std::unique_ptr<Impl> m;
};

