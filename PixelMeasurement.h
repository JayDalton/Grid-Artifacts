#pragma once

#include "PixelMeasurement.g.h"

namespace winrt::GridArtifacts::implementation
{
    struct PixelMeasurement : PixelMeasurementT<PixelMeasurement>
    {
        PixelMeasurement() = default;

	private:
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct PixelMeasurement : PixelMeasurementT<PixelMeasurement, implementation::PixelMeasurement>
    {
    };
}
