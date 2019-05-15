#pragma once

#include "PixelMeasurement.h"
#include "DicomImage.h"

#include "ShowFileData.g.h"

namespace winrt::GridArtifacts::implementation
{
	using namespace winrt::Windows::Storage;

    struct ShowFileData : ShowFileDataT<ShowFileData>
    {
        ShowFileData();

		StorageFile File() const
		{
			return m_file;
		}

		void File(const StorageFile& value)
		{
			m_file = value;
		}

        int32_t MyProperty();
        void MyProperty(int32_t value);

		// Event handler for navigation to DetailPage view.
		Windows::Foundation::IAsyncAction OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs e);

        //void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    
	private:
		StorageFile m_file{ nullptr };
	};
}

namespace winrt::GridArtifacts::factory_implementation
{
    struct ShowFileData : ShowFileDataT<ShowFileData, implementation::ShowFileData>
    {
    };
}
