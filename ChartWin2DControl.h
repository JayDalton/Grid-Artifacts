#pragma once

#include "winrt/Microsoft.Graphics.Canvas.h"
#include "winrt/Microsoft.Graphics.Canvas.UI.Xaml.h"
#include "PixelValues.h"

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "ChartWin2DControl.g.h"

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Microsoft::Graphics::Canvas;
	using namespace winrt::Microsoft::Graphics::Canvas::UI::Xaml;

	using PixelVector = std::vector<PixelValues>;

	struct RenderingOptions
	{
		double MinValue{ std::numeric_limits<double>::max() };
		double MaxValue{ std::numeric_limits<double>::lowest() };
		double MinValueBuffered;
		double MaxValueBuffered;
	};

    struct ChartWin2DControl : ChartWin2DControlT<ChartWin2DControl>
    {
        ChartWin2DControl();

        int32_t MyProperty();
        void MyProperty(int32_t value);

		//Background color for the graph (Do remember set the same value in XAML to avoid flickering)
		const Windows::UI::Color BACKGROUND_COLOR = Windows::UI::Colors::LightBlue();

		RenderingOptions CreateRenderingOptions(const PixelVector& vector);

		void ChartWin2DCanvas_Draw(CanvasControl const& sender, CanvasDrawEventArgs const& args);
		void chartGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);

		//off screen canvas for the background, lines & value texts
		CanvasRenderTarget _offscreenBackGround{ nullptr };
		//off screen canvas for the graph
		CanvasRenderTarget _offscreenChartImage{ nullptr };

		void DrawChart();
		void DrawBackGround(Microsoft::Graphics::Canvas::CanvasDevice device, RenderingOptions options);
		void DrawCharData(CanvasDevice device, RenderingOptions options, const PixelVector& data);

		void DrawGraphValueLines(CanvasDrawingSession ds, float width, float height);
		void DrawYAxisTexts(CanvasDrawingSession ds, float height, RenderingOptions options);

	private:
		PixelVector m_data;
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct ChartWin2DControl : ChartWin2DControlT<ChartWin2DControl, implementation::ChartWin2DControl>
    {
    };
}
