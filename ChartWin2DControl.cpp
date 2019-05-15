#include "pch.h"
#include "ChartWin2DControl.h"
#if __has_include("ChartWin2DControl.g.cpp")
#include "ChartWin2DControl.g.cpp"
#endif

#include <limits>
#include <vector>
#include <numeric>
#include <functional>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Microsoft::Graphics::Canvas::UI::Xaml;

    ChartWin2DControl::ChartWin2DControl()
    {
        InitializeComponent();
    }

    int32_t ChartWin2DControl::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void ChartWin2DControl::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

	void ChartWin2DControl::ChartWin2DCanvas_Draw(CanvasControl const& sender, CanvasDrawEventArgs const& args)
	{
		// in the start we don't have data, so we'll just draw the background rect with background color
		//args.DrawingSession.DrawRectangle(0, 0, (float)ChartWin2DCanvas.Size.Width, (float)ChartWin2DCanvas.Size.Height, BACKGROUND_COLOR);
		args.DrawingSession().DrawRectangle(0, 0, 
			ChartWin2DCanvas().Size().Width, 
			ChartWin2DCanvas().Size().Height, 
			BACKGROUND_COLOR
		);
	}

	void ChartWin2DControl::chartGrid_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e)
	{
		//re-calculate & draw the graph when orientation changes
		DrawChart();
	}

	void ChartWin2DControl::DrawChart()
	{
		if (m_data.empty() || m_data.size() <= 0)
		{
			return;
		}

		using namespace Microsoft::Graphics::Canvas;
		auto device = CanvasDevice::GetSharedDevice();

		//rendering options are calculating min & max values & value texts
		RenderingOptions renderingOptions = CreateRenderingOptions(m_data);

		////_offscreenBackGround is created in here
		DrawBackGround(device, renderingOptions);
		////_offscreenChartImage is created in here
		//DrawCharData(device, renderingOptions, _data);

		//forces re-draw
		ChartWin2DCanvas().Invalidate();
	}

	RenderingOptions ChartWin2DControl::CreateRenderingOptions(const PixelVector& vector)
	{
		RenderingOptions renderingOptions;
		if (!vector.empty())
		{

			const auto [min, max] = std::minmax_element(
				vector.cbegin(), vector.cend(), 
				[](const auto& lhs, const auto& rhs) {
					return lhs.GetValue() < rhs.GetValue();
				}
			);
			renderingOptions.MinValue = (*min).GetValue();
			renderingOptions.MaxValue = (*max).GetValue();

			//find if we have bigger or smaller than what we have with current values
			//for (int i = 0; i < dataSet.Length; i++)
			//{
			//	renderingOptions.MinValue = Math.Min(dataSet[i].HeartbeatValue, renderingOptions.MinValue);
			//	renderingOptions.MaxValue = Math.Max(dataSet[i].HeartbeatValue, renderingOptions.MaxValue);
			//}

			//and see if default values are more suitable
			//if (renderingOptions.MinValue > MIN_VALUE_DEFAULT)
			//{
			//	renderingOptions.MinValue = MIN_VALUE_DEFAULT;
			//}

			//if (renderingOptions.MaxValue < MAX_VALUE_DEFAULT)
			//{
			//	renderingOptions.MaxValue = MAX_VALUE_DEFAULT;
			//}

			auto valueDiff = renderingOptions.MaxValue - renderingOptions.MinValue;
			auto diffBuffer = (valueDiff > 0) ? (valueDiff * 0.1) : 2;
			//values used with value texts
			renderingOptions.MaxValueBuffered = renderingOptions.MaxValue + diffBuffer;
			renderingOptions.MinValueBuffered = renderingOptions.MinValue - diffBuffer;
			renderingOptions.MinValueBuffered = (renderingOptions.MinValueBuffered > 0) ? renderingOptions.MinValueBuffered : 0;
		}

		return renderingOptions;
	}

	void ChartWin2DControl::DrawBackGround(CanvasDevice device, RenderingOptions options)
	{
		float useHeight = (float)ChartWin2DCanvas().Size().Height;
		float useWidth = (float)ChartWin2DCanvas().Size().Width;

		//this is always drawn in the size of control, so all texts drawn in it are sharp
		_offscreenBackGround = CanvasRenderTarget(device, useWidth, useHeight, 96);

		if (CanvasDrawingSession ds = _offscreenBackGround.CreateDrawingSession())
		{
			ds.Clear(BACKGROUND_COLOR);
			//draw lines
			DrawGraphValueLines(ds, useWidth, useHeight);
			//draw value texts
			DrawYAxisTexts(ds, useHeight, options);
		}
	}

	//Drawn the background horizontal lines
	void ChartWin2DControl::DrawGraphValueLines(CanvasDrawingSession ds, float width, float height)
	{
		//var tickOffsetY = height / DEFAULT_GRADIENTS;
		//float currentOffsetY = 0;

		//for (int i = 0; i < (DEFAULT_GRADIENTS + 1); i++)
		//{
		//	float x0 = 0;
		//	float y0 = currentOffsetY;
		//	float x1 = width;
		//	float y1 = currentOffsetY;

		//	ds.DrawLine(x0, y0, x1, y1, LINES_COLOR); // add CanvasStrokeStyle
		//	currentOffsetY += tickOffsetY;
		//}
	}

	//draws the value texts
	void ChartWin2DControl::DrawYAxisTexts(CanvasDrawingSession ds, float height, RenderingOptions options)
	{
		//// if needed do add CanvasTextFormat 
		//ds.DrawText(options.MaxValueBuffered.ToString("#.#"), new Vector2(RIGHT_TEXT_MARGIN, 0), VALUESTEXT_COLOR);
		//var percent = (options.MaxValueBuffered - options.MinValueBuffered) * (1.0 / (DEFAULT_GRADIENTS));

		//for (int i = 1; i < DEFAULT_GRADIENTS; i++)
		//{
		//	var percentVal = options.MaxValueBuffered - (percent * i);
		//	// do add CanvasTextFormat 
		//	ds.DrawText(percentVal.ToString("#.#"), new Vector2(RIGHT_TEXT_MARGIN, (i * (height / DEFAULT_GRADIENTS))), VALUESTEXT_COLOR);
		//}

		//// do add CanvasTextFormat 
		//ds.DrawText(options.MinValueBuffered.ToString("#.#"), new Vector2(RIGHT_TEXT_MARGIN, (height - BOTTOM_TEXT_MARGIN)), VALUESTEXT_COLOR);
	}
}


