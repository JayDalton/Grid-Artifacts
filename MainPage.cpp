#include "pch.h"
#include "MainPage.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

#include "DicomImage.h"

//#include "winrt/Windows.ApplicationModel.Store.h"


using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GridArtifacts::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

	IAsyncAction MainPage::OpenBeatFile_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		using namespace winrt::Windows::Storage;

		Pickers::FileOpenPicker openPicker;
		openPicker.ViewMode(Pickers::PickerViewMode::Thumbnail);
		openPicker.SuggestedStartLocation(Pickers::PickerLocationId::DocumentsLibrary);
		openPicker.FileTypeFilter().Append(L".pgm");

		if (auto file = co_await openPicker.PickSingleFileAsync())
		{
			// Application now has read/write access to the picked file
			//System.Diagnostics.Debug.WriteLine("Picked file: " + file.Name);
			//Frame().Navigate(typeof(ShowFileData), file);
			Frame().Navigate(xaml_typename<ShowFileData>(), file);
		}
		else
		{
			//System.Diagnostics.Debug.WriteLine("Operation cancelled.");
		}
	}

	void MainPage::RefreshDeviceList_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{

	}
	
	IAsyncAction MainPage::GetItemsAsync()
	{
		//// Show the loading progress bar.
		//LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Visible);
		//NoPicsText().Visibility(Windows::UI::Xaml::Visibility::Collapsed);

		// File type filter.
		Search::QueryOptions options{};
		options.FolderDepth(Search::FolderDepth::Deep);
		options.FileTypeFilter().Append(L".jpg");
		options.FileTypeFilter().Append(L".png");
		options.FileTypeFilter().Append(L".gif");

		// Get the Pictures library.
		StorageFolder picturesFolder = KnownFolders::PicturesLibrary();
		auto result = picturesFolder.CreateFileQueryWithOptions(options);
		auto imageFiles = co_await result.GetFilesAsync();
		//auto unsupportedFilesFound = false;

		//// Populate Photos collection.
		//for (auto&& file : imageFiles)
		//{
		//	// Only files on the local computer are supported. 
		//	// Files on OneDrive or a network location are excluded.
		//	if (file.Provider().Id() == L"computer")
		//	{
		//		auto image = co_await LoadImageInfoAsync(file);
		//		Images().Append(image);
		//	}
		//	else
		//	{
		//		unsupportedFilesFound = true;
		//	}
		//}

		//if (Images().Size() == 0)
		//{
		//	// No pictures were found in the library, so show message.
		//	NoPicsText().Visibility(Windows::UI::Xaml::Visibility::Visible);
		//}

		//// Hide the loading progress bar.
		//LoadProgressIndicator().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
	}
	
	IAsyncOperation<GridArtifacts::DicomImage> MainPage::LoadImageInfoAsync(Windows::Storage::StorageFile file)
	{
		auto properties = co_await file.Properties().GetImagePropertiesAsync();
		auto info = winrt::make<DicomImage>(properties, file, file.DisplayName(), file.DisplayType());
		co_return info;
	}
}




