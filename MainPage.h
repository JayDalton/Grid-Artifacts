#pragma once

#include "MainPage.g.h"

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Windows::Foundation;
	using namespace winrt::Windows::UI::Xaml;
	using namespace winrt::Windows::Storage;

    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

		// Retreives collection of Photo objects for thumbnail view.
		Collections::IVector<IInspectable> Images() const
		{
			return m_images;
		}

		IAsyncAction OpenBeatFile_Click(IInspectable const& sender, RoutedEventArgs const& e);
		void RefreshDeviceList_Click(IInspectable const& sender, RoutedEventArgs const& e);

	private:
		// Functions for image loading and animation.
		IAsyncAction GetItemsAsync();
		IAsyncOperation<GridArtifacts::DicomImage> LoadImageInfoAsync(Windows::Storage::StorageFile file);

		// Backing field for Photo collection.
		Collections::IVector<IInspectable> m_images{ nullptr };

		// Field to store selected Photo for later back navigation.
		GridArtifacts::DicomImage m_persistedItem{ nullptr };
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
