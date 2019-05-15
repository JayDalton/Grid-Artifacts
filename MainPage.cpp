#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

// Windows::Storage::Pickers
#include "winrt/Windows.ApplicationModel.Store.h"


using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GridArtifacts::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    //void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    //{
    //    myButton().Content(box_value(L"Clicked"));
    //}

	IAsyncAction MainPage::OpenBeatFile_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		using namespace Windows::Storage;

		Pickers::FileOpenPicker openPicker;
		openPicker.ViewMode(Pickers::PickerViewMode::Thumbnail);
		openPicker.SuggestedStartLocation(Pickers::PickerLocationId::DocumentsLibrary);
		openPicker.FileTypeFilter().Append(L".pgm");

		auto file = co_await openPicker.PickSingleFileAsync();
		if (file.IsAvailable())
		{
			// Application now has read/write access to the picked file
			//System.Diagnostics.Debug.WriteLine("Picked file: " + file.Name);
			//Frame().Navigate(typeof(ShowFileData), file);
			Frame().Navigate(xaml_typename<ChartWin2DControl>(), file);
		}
		else
		{
			//System.Diagnostics.Debug.WriteLine("Operation cancelled.");
		}
	}

	void MainPage::RefreshDeviceList_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{

	}
}




